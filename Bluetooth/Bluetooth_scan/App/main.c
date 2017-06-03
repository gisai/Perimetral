/*

Created by Sergio García García

Programa main, prueba del correcto funcionamiento de las llamadas
a las librerías.

*/


// Librerías necesarías
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include </usr/include/artik/base/artik_module.h>
#include </usr/include/artik/base/artik_loop.h>
#include </usr/include/artik/bluetooth/artik_bluetooth.h>


#include "../Middleware/show_all.h"


#define MAX_BDADDR_LEN  17
#define CHECK_RET(x)    { if (x != S_OK) goto exit; }

 static artik_bluetooth_module *bt = NULL;

/*
------------------------------------------------------------------------------------------------------------------------------------
	Main de la aplicacion, para probar el correcto funcionamiento
------------------------------------------------------------------------------------------------------------------------------------
*/

int main(){
    int opt;
    artik_error ret = S_OK;
    char target_address[MAX_BDADDR_LEN+1] = "";
    bt = (artik_bluetooth_module *)artik_request_api_module("bluetooth");
    if (!bt) {
    fprintf(stdout,
            "TEST: Failed tor request bluetooth module skipping test...\n");
    return -1;
            }
    // Creación de un proceso aparte para evitar bloqueo
    int pid;
      pid = fork();
      switch(pid){
        case -1: // Si pid es -1 quiere decir que ha habido un error
         perror("No se ha podido crear el proceso\n");
          break;
        case 0: // Cuando pid es cero quiere decir que es el proceso hijo
    // Llamada al conjunto de funciones
            ret = show_all();
            CHECK_RET(ret);
            exit:
            return (ret == S_OK) ? 0 : -1;
            break;
        default: // Cuando es distinto de cero es el padre
          break;
      }

}
