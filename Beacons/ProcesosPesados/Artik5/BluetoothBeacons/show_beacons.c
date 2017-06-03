
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


/* Main function  */
int main(){
  // Creamos los procesos
	printf("-->Arranque de programa de deteción de Beacons\n");
  int pid;
  pid = fork();
  int fd[2];
  pipe(fd);
  switch(pid){
    case -1: // Si pid es -1 quiere decir que ha habido un error
      perror("No se ha podido crear el proceso\n");
      break;
    case 0: // Cuando pid es cero quiere decir que es el proceso hijo
    // Filtramos los beacons
     execv("./filter", NULL);
     perror("fallo en exec");
     exit(EXIT_FAILURE);
      break;
    default: // Cuando es distinto de cero es el padre
    // Pintariamos los beacon
      break;
  }
	return 0;
}

