
/*

show_beacons.c 

Application of catch and treatment Beacons.
Created in 2017 by Sergio García García.
Universidad Politecnica de Madrid.

*/

// Librerias necesarias

#include <stdio.h> 
#include <string.h> 
#include <stdlib.h> 
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>

#define SIZE 512
 
int main( int argc, char **argv )
{
  // Creación de pipe y fork junto con mensaje de inicio y variables de sistema
  pid_t pid;
  int  readbytes;
  char buffer[SIZE];
  printf("-->Arranque de programa de deteción de Beacons\n");
  int fd[2];
  pipe(fd);
  pid=fork();
  char str[2];
 
 // Switch para los procesos
  switch(pid){
    case -1: // Si pid es -1 quiere decir que ha habido un error
      perror("No se ha podido crear el proceso\n");
      break;
    case 0: // Cuando pid es cero quiere decir que es el proceso hijo
      close( fd[0] ); /* cerramos el lado de lectura del pipe */
      //close( fd[1] );
      sprintf(str, "%d", fd[1]);
      //close( fd[0] );
      execlp("./filter","filter",str, (char *) NULL);
      //waitpid( pid, NULL, 0 );
      break;
    default: // Cuando pid es distinto de cero quiere decir que es el proceso padre
      close( fd[1] ); /* cerramos el lado de escritura del pipe */
    // Creación de un bucle infinito para leer los mensajes que vengan de filtrado
      while(1){
        // Lectura del pipe, por aqui representamos los beacons
        while( (readbytes=read( fd[0], buffer, SIZE )) > 0){
          write( 1, buffer, readbytes );
        }  
      }
      close( fd[0] );
      break;
  }  
    exit( 0 );
}