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

#include "middleware.h"

/*
------------------------------------------------------------------------------------------------------------------------------------
	Main de la aplicacion, para probar el correcto funcionamiento
------------------------------------------------------------------------------------------------------------------------------------
*/

int main(){
   m_lista_dispositivos_todos_Bluetooth (stdout);
}
