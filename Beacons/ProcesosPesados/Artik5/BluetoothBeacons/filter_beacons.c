/*

app.c 

Application of catch and treatment Beacons.
Created in 2017 by Sergio García García.
Universidad Politecnica de Madrid.

*/


/* Libraries or files used */
#include <stdio.h> 
#include <string.h> 
#include <stdlib.h> 
#include <unistd.h>
#include <sys/types.h>
#include <time.h>


// Variables globales
char info[200];

char *beacons[20][5];
int t_beacons[20][1];
int n_beacons = 0;
clock_t t_ini, t_fin;
FILE *archivo;
int caracter;
int a;

char *beacon_prop[5];



/* Main function  */
int main(){
  // Impresión de un mensaje inicial
	printf("\n-->Filtrado de Beacons\n");
  // Creamos procesos
  int pid;
  pid = fork();
  switch(pid){
    case -1: // Si pid es -1 quiere decir que ha habido un error
      perror("No se ha podido crear el proceso\n");
      break;
    case 0: // Cuando pid es cero quiere decir que es el proceso hijo
      // Realizamos la busqueda de beacon
      execl("./ibeacon_scan.sh", NULL);
      perror("fallo en exec");
      exit(EXIT_FAILURE);
      break;
    default: 
      // Cuando es distinto de cero es el padre
      // Bluce infinito para el tratamiento de los beacons
      // Cogemos el Beacon del archivo
     while(1){
        a = 0;
        archivo = fopen("evento.txt","r");
  
        if (archivo == NULL){
            printf("\nError de apertura del archivo. \n\n");
        }
        else{
          // Guardamos el beacon en una variable
          while((caracter = fgetc(archivo)) != EOF){
            info[a] = caracter;
            a = a+1;
          }
        }
        fclose(archivo);
        // Eliminamos el beacon del archivo
        archivo = fopen("evento.txt","w+");
        fclose(archivo);
//---------------------------------------------------------------------------------------------------------------        
        // Separamos las propiedades del beacon en un array
         char separador[] = " ";
         char *prop = NULL;
         int i;
         prop = strtok( info, separador);
         i = 0;
         while( prop != NULL ) {
          beacon_prop[i] = prop;
          i = i+1;
          prop = strtok( NULL, separador);
         }

//--------------------------------------------------------------------------------------------------------------- 
        // Trazas para el ver el funcionamiento del programa y salida de un beacon     
        if(n_beacons>0){
          // Comprobación de los beacons
          for (int l=0; l<n_beacons; l++){
            t_fin = clock();
            // Si ha pasado mucho tiempo de que no obtenemos respuesta del beacon le sacamos del array
            if (t_fin - t_beacons[l][0] > 7000){
              // AQUI SE DEBE MANDAR POR EL PIPE LA SALIDA DE UN BEACON
              printf("El beacon con major: %s minor: %s ha salido\n", beacons[l][1], beacons[l][2]);
              // Eliminamos ahora el contenido
              for(int m=0; m<5; m++){
                beacons[l][m] = NULL;
              }
              // Reorganizamos el array
              // Si es el ultimo no tenemos que hacer nada
              if(l==n_beacons-1){
                n_beacons=n_beacons-1;
              }else{
                n_beacons=n_beacons-1;
                // Colocamos el array
                for (l; l<n_beacons; l++){
                  for(int p=0; p<5; p++){
                    beacons[l][p] = beacons[l+1][p];
                   } 
                }
              }
            }
          } 
        }

//---------------------------------------------------------------------------------------------------------------
    //Comprabación de beacon e introducion de los mismos

        // Vemos en primer lugar el UUID, si es el de la organización pasamos
          if (strcmp(beacon_prop[0], "E2C56DB5-DFFB-48D2-B060-D0F5A71096E0") == 0){
        // Si no tenemos beacon, le introducimos directamente
            if(beacon_prop[1] != 0 && beacon_prop[2] != 0 && n_beacons == 0 && atoi(beacon_prop[4]) > -90){
              // AQUI SE DEBE MANDAR POR EL PIPE LA ENTRADA DE UN BEACON
              // Metemos los datos en nuestro array de beacons
              for(int s=0; s<5; s++){
                beacons[n_beacons][s] = beacon_prop[s];
              }
              printf("\nEl beacon con major: %s minor: %s ha entrado\n", beacons[n_beacons][1], beacons[n_beacons][2]);
              // Metemos el tiempo y ponemos a 1 el número de beacons
                t_beacons[n_beacons][0] = clock();
                n_beacons=n_beacons+1;
                beacon_prop[0] = 0;
        // Si tenemos ya beacons        
            }else {
              // Pasamos todos los que tenemos y comprobamos 
              for (int f=0; f<n_beacons; f++){
                // Si tiene distinto major
                if (beacon_prop[1] != 0 && (strcmp(beacons[f][1], beacon_prop[1]) != 0)){
                  // Si tiene distinto minor
                  if (beacon_prop[2] != 0 && (strcmp(beacons[f][2], beacon_prop[2]) != 0)){
                    // Si su RRSI es apropieda
                    if (beacon_prop[4] != 0 && atoi(beacon_prop[4]) > -90){
                      // AQUI SE DEBE MANDAR POR EL PIPE LA ENTRADA DE UN BEACON
                      // introducimos el beacon en nuestro array
                      for(int s=0; s<5; s++){
                        beacons[n_beacons][s] = beacon_prop[s];
                      }
                      printf("El beacon con major: %s minor: %s ha entrado\n", beacons[n_beacons][1], beacons[n_beacons][2]);
                      // Metemos el tiempo y ponemos a 1 el número de beacons
                      t_beacons[n_beacons][0] = clock();
                      n_beacons=n_beacons+1;
                      //Eliminamos el valor de beacom_prop
                      beacon_prop[0] = 0;
                    }
                  }
                  // En el caso del tener igua major, miramos si es igual el minor y si el RRSI es razonable
                } else if (beacon_prop[2] != 0 && strcmp(beacons[f][2], beacon_prop[2]) == 0 && atoi(beacon_prop[4]) > -90){
                  // Actualizamos el tiempo del beacon
                  t_beacons[f][0] =  clock();
                  beacon_prop[0] = 0;
                  beacon_prop[1] = 0;
                  beacon_prop[2] = 0;
                }
              }
            }
          }
          // Dejamos un tiempo para la computación de los beacons, si no tendriamos que establecer mayor tiempo
          sleep(1);
      }          
    break;
  }
	return 0;
}

