/**
 * Fichero con las rutinas de BlueZ necesarias
 * para escanear con Bluetooth
 * PERIMETER SECURITY
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <artik_module.h>
#include <artik_loop.h>
#include <artik_bluetooth.h>
#include <time.h>
#include "bluetoothAntena.h"

//Modulo BT
static artik_bluetooth_module *bt;

//Parámetros que no pueden ser transmitidos por BT y
//quedan configurados en la antena
int idAntena = 1;
int potenciaDBM = 8;


/*
------------------------------------------------------------------------------------------------------------------------------------
    Obtención de dispositivos bluetooth cercanos, funciones que permiten realizarla.
------------------------------------------------------------------------------------------------------------------------------------
*/

// Funciones auxiliares de callback para pintura y reinicio
static void scan_callback(artik_bt_event event, void *data, void *user_data)
{
    artik_bt_device *dev = (artik_bt_device *) data;
    printf("{ID: {IDSystem:%i, IDGroup:%s, IDPerson:%s}, IDAnte:%i, pow:%i, rssi:%i, time:%i}\n", dev[0].manufacturer_id, dev[0].remote_name, dev[0].remote_address, idAntena, potenciaDBM, dev[0].rssi, (unsigned int)time(NULL));
}

//Función de reinicio tras timeout
static void scan_timeout_callback(void *user_data)
{
	bt->stop_scan();
	bt->remove_devices();
	artik_loop_module *loop = (artik_loop_module *) user_data;
    loop->quit();
}

// Función de listado
artik_error lista_dispositivos_cercanos_Bluetooth_F()
{

	int timeout_id = 0;
    bt = (artik_bluetooth_module *)artik_request_api_module("bluetooth");
	if (!bt) {return -1;}
	artik_loop_module *loop = (artik_loop_module *)artik_request_api_module("loop");
	artik_error ret = S_OK;
    ret = bt->set_callback(BT_EVENT_SCAN, scan_callback, NULL);
    if (ret != S_OK)
        goto exit;

    while (1) {
		ret = bt->start_scan();
		if (ret != S_OK)
			goto exit;
		loop->add_timeout_callback(&timeout_id, SCAN_TIME_MILLISECONDS, scan_timeout_callback, (void *)loop);
		loop->run();
    }

exit:
    bt->stop_scan();
    bt->unset_callback(BT_EVENT_SCAN);
    artik_release_api_module(loop);
    return ret;
}


/**
 * Función principal de arranque
 */
int main(int argc, char *argv[]) {
	artik_error error = lista_dispositivos_cercanos_Bluetooth_F();
	return (int)error;
}
