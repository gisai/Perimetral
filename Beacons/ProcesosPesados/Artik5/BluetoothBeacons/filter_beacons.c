/*

filter_beacons.c 

Application of catch and treatment Beacons.
Created in 2017 by Sergio García García.
Universidad Politecnica de Madrid.

*/


/* Librerias necesarias */
#include <stdio.h> 
#include <string.h> 
#include <stdlib.h> 
#include <unistd.h>
#include <sys/types.h>
#include <time.h>
#include <fcntl.h>
#include <sys/stat.h>

#define POTENCIA_LIMIT -90
#define TIEMPO_OFF 2


// Variables globales

// Array donde se almacenan los beacons que nos importan
int beacons[20][2];
// Array de tiempo de beacons
time_t t_beacons[20];
// Numero de beacons
int n_beacons = 0;
// Tiempo actual
time_t t_fin;
// Variable global para tratamiento de info
int a;
// Array variable donde se van almacenando los beacons capturados en el momento
char *beacon_prop[5];
// String para pintar la frase de entrada de un beacons
char string[512];



/* Funcion main */
int main(int argc, char** argv){
  // Impresión de un mensaje inicial
	printf("-->Filtrado de Beacons\n");
  // Recuperamos el pipe de escritura que enviamos por el exec
  int fd_1 = atoi(argv[1]);
  // Creamos procesos
  int pid;
  pid = fork();
  // Creacion de variables y pipe tipo fifo para comunicacion con intermedial.c
  char buf[60];
  FILE *mipipe;
  char buffer[128];
  // Creacion de la cola fifo
  mkfifo("/tmp/pipebeacons", S_IWUSR | S_IRUSR | S_IRGRP | S_IROTH );
  
  //Swicth para los procesos   
  switch(pid){
    case -1: // Si pid es -1 quiere decir que ha habido un error
      perror("No se ha podido crear el proceso\n");
      break;
    case 0: // Cuando pid es cero quiere decir que es el proceso hijo
      // Realizamos la busqueda de beacon
      // Pasamos el control a intermedial
      execlp("./intermedial","intermedial", "/tmp/pipebeacons", (char *) NULL);
      perror("fallo en exec");
      exit(EXIT_FAILURE);
      break;
    default: 
      // Cuando es distinto de cero es el padre
      // Bluce infinito para el tratamiento de los beacons
      // Cogemos el Beacon de la cola fifo
     while(1){
      mipipe=fopen("/tmp/pipebeacons", "r"); 
      /* Con esta línea leemos hasta que se cierre la tubería por el otro */
      while (!feof(mipipe)){
        fgets(buffer, 128, mipipe);
      }
      fclose(mipipe);
    
// Tratamiento de información del beacons
//--------------------------------------------------------------------------------------------------------------- 

        // Separamos las propiedades del beacon en un array, para poder realizar el tratamiento
         char separador[] = " ";
         char *prop;
         int i;
         prop = strtok( buffer, separador);
         i = 0;
         while( prop != NULL ) {
          beacon_prop[i] = prop;
          prop = 0;
          i = i+1;
          prop = strtok( NULL, separador);
         }
// Tratado de beacons
//--------------------------------------------------------------------------------------------------------------- 
        // Si tenemos beacons vemos si han salido     
        if(n_beacons>0){
          // Comprobación de los beacons
          for (int l=0; l<n_beacons; l++){
            t_fin = time(NULL); /* Tiempo actual segundos*/
            // Miramos el tiempo y si es superior a un determinado valor, sacamos el beacons
            if (t_fin - t_beacons[l] > TIEMPO_OFF){
              // Mandamos la salida del beacons al proceso superior
                system("echo -----");
                sprintf(string, "El beacon con major: %i minor: %i ha salido\n", beacons[l][0], beacons[l][1]);
                write(fd_1, string, (strlen(string))); 
              // Eliminamos ahora el contenido
              for(int m=0; m<2; m++){
                beacons[l][m] = 0;
              }
              // Reorganizamos el array
              // Si es el ultimo no tenemos que hacer nada
              if(l==n_beacons-1){
                n_beacons=n_beacons-1;
              }else{
                n_beacons=n_beacons-1;
                // Colocamos el array
                for (l; l<n_beacons; l++){
                  for(int p=0; p<2; p++){
                    beacons[l][p] = beacons[l+1][p];
                   } 
                }
              }
            }
          } 
        }

// Introdución de beacons 
//---------------------------------------------------------------------------------------------------------------
    //Comprabación de beacon e introducion de los mismos
        // Vemos en primer lugar el UUID, si es el de la organización pasamos
        // Si el beacons es el primero y posee el UUID de la organizacion 
        if(beacon_prop[0] != 0 && strcmp(beacon_prop[0], "E2C56DB5-DFFB-48D2-B060-D0F5A71096E0") == 0 && n_beacons == 0 && beacon_prop[1] != 0 && beacon_prop[2] != 0 && atoi(beacon_prop[4]) > POTENCIA_LIMIT){
          int e =1;
            for(int s=0; s<2; s++){
              // Introducimos el beacon al ser el primero
              beacons[n_beacons][s] = atoi(beacon_prop[e]);
              e = e +1;
            } 
            // Mandamos el beacons a los procesos superiores  
              system("echo -----");
              sprintf(string,"El beacon con major: %i minor: %i ha entrado\n", beacons[n_beacons][0], beacons[n_beacons][1]);
              write(fd_1, string, (strlen(string)));
              // Introducimos el tiempo actual
              t_beacons[n_beacons] = time(NULL);
              // Aumentamos el numero de beacons
              n_beacons=n_beacons+1;
              // Eliminamos las propiedades
              beacon_prop[0] = 0;
              beacon_prop[1] = 0;
              beacon_prop[2] = 0;
        }else{
          // Creación de una variable para encontrar si el beacon capturado es igual a uno de los que almacenamos en el array beacons
            int distintos = 0; 
            for (int i_beacons=0; i_beacons<n_beacons; i_beacons++){
              // Si es igual
              if(beacon_prop[0] != 0 && strcmp(beacon_prop[0], "E2C56DB5-DFFB-48D2-B060-D0F5A71096E0") == 0 && beacon_prop[1] != 0 && beacons[i_beacons][0] == atoi(beacon_prop[1]) && beacon_prop[2] != 0 && beacons[i_beacons][1] == atoi(beacon_prop[2]) && atoi(beacon_prop[4]) > POTENCIA_LIMIT){
                distintos = 1;
                // Actualizamos el tiempo
                t_beacons[i_beacons] =  time(NULL);
                beacon_prop[0] = 0;
                beacon_prop[1] = 0;
                beacon_prop[2] = 0;
              }     
            }
            // Si es distinto a todos, introducimos el nuevo beacons
            if(distintos == 0 && beacon_prop[1] != 0 && beacon_prop[2] != 0 && beacon_prop[0] != 0 && strcmp(beacon_prop[0], "E2C56DB5-DFFB-48D2-B060-D0F5A71096E0") == 0 && atoi(beacon_prop[4]) > POTENCIA_LIMIT ){
            // introducimos el beacon en nuestro array
              for(int p1=1; p1<3; p1++){
                beacons[n_beacons][p1-1] = atoi(beacon_prop[p1]);
              }
              // Mandamos el beacon al nivel superior
              system("echo -----");
              sprintf(string,"El beacon con major: %i minor: %i ha entrado\n", beacons[n_beacons][0], beacons[n_beacons][1]);
              write(fd_1, string, (strlen(string)));
              // Metemos el tiempo y ponemos a 1 el número de beacons
              t_beacons[n_beacons] = time(NULL);
              n_beacons=n_beacons+1;
              //Eliminamos el valor de beacom_prop
              beacon_prop[0] = 0;
              beacon_prop[1] = 0;
              beacon_prop[2] = 0;
            }
        }
      } 
      fclose(mipipe); 
    break;
  }
	return 0;
}

