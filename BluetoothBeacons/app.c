
/*

app.c 

Application of catch and treatment Beacons.
Create in 2017 by Sergio García García.
Universidad Politecnica de Madrid.

*/


/* Libraries or files used */
#include <stdio.h> 
#include <string.h> 
#include <stdlib.h> 
/* Header files of different functions*/
#include "listaBeacons.h"
#include "devices.h"
#include "infoBeacons.h"


/* Error function */

void error(){
	printf("-->ERROR, no se encuentra la opción que ha solicitado\n");
	printf("-->Vuelva a ejecutar la función y seleccione una de las posibles funciones\n");
}

/* Help function */

void help(){
	printf("-->Acciones posibles: \n");
	printf("-->listaBeacons: función que devuelve los beacons que se encuentren en las cercanías\n");
}

/* Main function  */
int main(){
  /* Program execution management by entering text from console*/
	printf("-->Aplicación de detección y tratamiento de Beacons\n");
	char action [20];
  	printf ("-->Introduzca una acción de las siguientes: \nlistaBeacons \ndevices \ninfobeacons \nhelp \n");
  	fgets (action, 20, stdin);
  	printf ("-->La cadena leída es: %s \n", action);
    /* Selecting the correct function */
  	if (!strcmp(action,"listaBeacons\n")){
  		lista_beacons();
  	}
    else if (!strcmp(action,"devices\n")){
      devices();
    }
    else if (!strcmp(action,"infobeacons\n")){
      infoBeacons();
    }
  	else if (!strcmp(action,"help\n")){
  		help();
  	}
  	else{
  		error();
  	}	
	return 0;
}

