    /*====================================================================================================*/
	/*Programa para detectar nodos inalámbricos en RFID*/
    /* ---------------------------------------------------------------------------------------------------*/
	/*PERIMETER SECURITY*/
	/*Borja Bordel*/
	/*====================================================================================================*/

	#include <stdio.h>
	#include <fcntl.h>   /* File Control Definitions           */
	#include <termios.h> /* POSIX Terminal Control Definitions */
	#include <unistd.h>  /* UNIX Standard Definitions 	   */ 
	#include <errno.h>   /* ERROR Number Definitions           */
	#include <signal.h>
	
	#include "RFID_RX211.h"
	#include "interpreter.c"
 
	/*File Descriptor*/
	int fd;		
    
    //Flag para depuración
	int debug = 0;
	
	//Longitud de respuesta vacía
	int size_emptyResponse = 7;
	
	//Longitud mensaje con Tag
	int size_fullResponse = 39;
	
	/*Función para poder cerar el proceso infinito*/
	void term(int signum)	{
		close(fd);
		if(debug) { printf("Closed"); }
	}
	
	/*
	* Procedimiento principal
	*/
	void main(int argc, char *argv[]) {
		
		//Miramos si estamos en modo depuración
		if (argc > 1) {
			debug = 1;
		}
        	
		// Elementos para capturar el final del bucle 
		//infinito
		struct sigaction action;
		memset(&action, 0, sizeof(struct sigaction));
		action.sa_handler = term;
		sigaction(SIGTERM, &action, NULL);
		
		if (debug) {
			printf("\n +----------------------------------+");
			printf("\n |        Serial Port Read          |");
			printf("\n +----------------------------------+");
		}

		/*------------------------------- Opening the Serial Port -------------------------------*/

		/* /dev/ttyUSB0 es el puerto físico donde está el lector */
		/* O_RDWR   - Read/Write access to serial port       */
		fd = open("/dev/ttyUSB0", O_RDWR);	
			
		if (debug) {
			if(fd == -1)						
				   printf("\n  Error! in Opening ttyUSB0  ");
			else
				   printf("\n  ttyUSB0 Opened Successfully ");
		}
	
		/*---------- Setting the Attributes of the serial port using termios structure --------- */
		
		struct termios SerialPortSettings;	/* Create the structure */

		if (tcgetattr(fd, &SerialPortSettings) < 0) {
			/* Get the current attributes of the Serial port */
			if(debug) {
				printf("\n  ERROR ! Handling");
				printf("Oh dear, something went wrong with read()! %s\n", strerror(errno));
			}
		}

		/* Setting the Baud rate */
		/* Set Read  Speed as 115200*/
		cfsetispeed(&SerialPortSettings,B115200); 
		cfsetospeed(&SerialPortSettings,B115200);

		/* 8N1 Mode */
		SerialPortSettings.c_cflag &= ~PARENB;   /* Disables the Parity Enable bit(PARENB),So No Parity   */
		SerialPortSettings.c_cflag &= ~CSTOPB;   /* CSTOPB = 2 Stop bits,here it is cleared so 1 Stop bit */
		SerialPortSettings.c_cflag &= ~CSIZE;	 /* Clears the mask for setting the data size             */
		SerialPortSettings.c_cflag |=  CS8;      /* Set the data bits = 8                                 */
		
		SerialPortSettings.c_cflag &= ~CRTSCTS;       /* No Hardware flow Control                         */
		SerialPortSettings.c_cflag |= CREAD | CLOCAL; /* Enable receiver,Ignore Modem Control lines       */ 
		
		
		SerialPortSettings.c_iflag &= ~(IXON | IXOFF | IXANY);          /* Disable XON/XOFF flow control both i/p and o/p */
		SerialPortSettings.c_lflag &= ~(ICANON | ECHO | ECHOE | ISIG);  /* Non Cannonical mode                            */

		SerialPortSettings.c_oflag &= ~OPOST;/*No Output Processing*/
		
		/* Setting Time outs */
		SerialPortSettings.c_cc[VMIN] = size_emptyResponse; /* Read at least 10 characters */
		SerialPortSettings.c_cc[VTIME] = 0; /* Wait indefinetly   */

		if((tcsetattr(fd,TCSANOW,&SerialPortSettings)) != 0) /* Set the attributes to the termios structure*/
		    if(debug) {printf("\n  ERROR ! in Setting attributes");}
		else
            if (debug) {printf("\n  BaudRate = 115200 \n  StopBits = 1 \n  Parity   = none \n");}
			
	    /*------------------------------- Read data from serial port -----------------------------*/

		tcflush(fd, TCIFLUSH);   /* Discards old data in the rx buffer            */

		char read_buffer[size_emptyResponse];   /* Buffer to store the data received              */
		int  bytes_read = 0;                    /* Number of bytes read by the read() system call */
		
		//Comando para hacer AutoPulling
		char write_buffer[] = "\xAA\x00\x00\x00\x01\x01\x00";	/* Buffer containing characters to write into port	     */	
		int  bytes_written  = 0;  	/* Value for storing the number of bytes written to the port */ 

		//Envío del comando de autopoll
		bytes_written = write(fd,write_buffer,sizeof(write_buffer)-1);/* use write() to send data to port                                            */
									     /* "fd"                   - file descriptor pointing to the opened serial port */
									     /*	"write_buffer"         - address of the buffer containing data	            */
									     /* "sizeof(write_buffer)" - No of bytes to write*/
		if(debug) {printf("Bytes send %d", bytes_written);}
		
		//Bucle principal
		while (1) {
			
			int byte_leido = 0;
			
			//Leer las respuestas al comando
			bytes_read = read(fd,&read_buffer,size_emptyResponse); /* Read the data*/
			
			if (read_buffer[1] != '\x00' && read_buffer[0] == '\x55') {
				/*Revisión de los datos*/
				if(debug) {
					for(int i=0;i<bytes_read;i++) {	 /*printing only the received characters*/
						//Eliminamos la cabecera
						if (read_buffer[i] != '\x55') {
							printf("%02x",read_buffer[i]);
						}  
					}		
					printf("\n");
				}
				
				//Composición del mensaje completo
				char read_fullBufferTag[size_fullResponse];				
				for(int i=0;i<bytes_read;i++) {	
					read_fullBufferTag[i+byte_leido] = read_buffer[i];
				}				
				byte_leido += bytes_read;
					
				//Lectura hasta el total de bytes	
				while (byte_leido < size_fullResponse) {			
					bytes_read = read(fd,&read_buffer,size_emptyResponse); /* Read the data*/
					for(int i=0;i<bytes_read;i++) {	
						read_fullBufferTag[i+byte_leido] = read_buffer[i];
					}				
					byte_leido += bytes_read;
				}
				
				packetProcessing(read_fullBufferTag);
				
				if(debug) {
					for(int i=0;i<size_fullResponse;i++) {	
						printf("%02x",read_fullBufferTag[i]); 
					}		
					printf("\n");
				}
			}
			
		}
	
		if(debug) {printf("\n +----------------------------------+\n\n\n");}

		close(fd); /* Close the serial port */

    }

