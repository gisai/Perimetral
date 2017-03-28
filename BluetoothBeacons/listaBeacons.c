
/* File listaBeacons.c */

#include <stdio.h>
#include <stdlib.h>
#include "listaBeacons.h"
#include <signal.h>



int lista_beacons(){
	system("timeout 10s hcitool lescan --duplicates");
	exit(1);
}