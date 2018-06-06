/*====================================================================================================*/
/*Programa para detectar nodos inalámbricos en RFID*/
/* ---------------------------------------------------------------------------------------------------*/
/*PERIMETER SECURITY*/
/*Borja Bordel*/
/*====================================================================================================*/

#include <time.h>
#include <stdlib.h>
#include <stdio.h>

#include "interpreter.h"

//Identificador de antena
int antenaID = 1;
int rssi;
int32_t personID;
int groupID = 20000;
char systemID [] = "E2C56DB5-DFFB-48D2-B060-D0F5A7109E0";
time_t current_time;
int potencia = 0;
    
/*
* Función para procesar los mensajes recibidos
*/
void packetProcessing (char packet[]) {
	/* Obtain current time. */
    current_time = time(NULL);
	
    personID = packet[25] | (int32_t)packet[24] << 8 | (int32_t)packet[23] << 16 | (int32_t)packet[22] << 24;
	rssi = (int32_t)packet[28] - 255;
 	printf("{tech:RFID, ID: {IDSystem:%s, IDGroup:%d, IDPerson:%d}, IDAnte:%d, pow:%d, rssi:%d, time:%d}", systemID, groupID, personID, antenaID, potencia, rssi, current_time);
	printf("\n");
}