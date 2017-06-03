/*

Created by Sergio García García

Programa que permite mostrar por pantalla los 
dispositivos Bluetooth.

*/

// Librerías necesarías

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include </usr/include/artik/base/artik_module.h>
#include </usr/include/artik/base/artik_loop.h>
#include </usr/include/artik/bluetooth/artik_bluetooth.h>

/*
------------------------------------------------------------------------------------------------------------------------------------
	Funcion para la impresion de los diferentes dispositivos encontrados
------------------------------------------------------------------------------------------------------------------------------------
*/

void print_devices(artik_bt_device *devices, int num){
    int i = 0, j = 0;
    for (i = 0; i < num; i++) {
        fprintf(stdout, "Address: %s\n",
            devices[i].remote_address ? devices[i].
            remote_address : "(null)");
        fprintf(stdout, "Name: %s\n",
            devices[i].remote_name ? devices[i].
            remote_name : "(null)");
        /*
       fprintf(stdout, "RSSI: %d\n", devices[i].rssi);
        fprintf(stdout, "Bonded: %s\n",
            devices[i].is_bonded ? "true" : "false");
        fprintf(stdout, "Connected: %s\n",
            devices[i].is_connected ? "true" : "false");
        fprintf(stdout, "Authorized: %s\n",
            devices[i].is_authorized ? "true" : "false");
        fprintf(stdout, "Class:\n");
        fprintf(stdout, "\tMajor:0x%02x\n", devices[i].cod.major);
        fprintf(stdout, "\tMinor:0x%02x\n", devices[i].cod.minor);
        fprintf(stdout, "\tService:0x%04x\n",
            devices[i].cod.service_class);
        if (devices[i].uuid_length > 0) {
            fprintf(stdout, "UUIDs:\n");
            for (j = 0; j < devices[i].uuid_length; j++) {
                fprintf(stdout, "\t%s [%s]\n",
                    devices[i].uuid_list[j].uuid_name,
                    devices[i].uuid_list[j].uuid);
            }
        }
        */
        fprintf(stdout, "\n");
    }
}