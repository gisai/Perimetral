/*

Created by Sergio García García

Función que muestra los dispositivos bluetooth que han 
sido en emparejados anteriormente o han sido descubiertos 
con anterioridad.

*/


// Librerías necesarias

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include </usr/include/artik/base/artik_module.h>
#include </usr/include/artik/base/artik_loop.h>
#include </usr/include/artik/bluetooth/artik_bluetooth.h>

#include "show.h"

static artik_bluetooth_module *bt = NULL;



/*
------------------------------------------------------------------------------------------------------------------------------------
	Impresion de los dispositivos bluetooth ya conocidos, funciones que permiten realizarla. 
------------------------------------------------------------------------------------------------------------------------------------
*/

artik_error devicesBluetooth(void){
    artik_error ret = S_OK;
    artik_bt_device *devices = NULL;
    int num = 0;
    fprintf(stdout, "TEST: %s starting\n", __func__);
    fprintf(stdout, "TEST: %s - list devices\n", __func__);
    bt = (artik_bluetooth_module *)artik_request_api_module("bluetooth");
    ret = bt->get_devices(&devices, &num);
    if (ret != S_OK)
        goto exit;
    print_devices(devices, num);
    bt->free_devices(devices, num);
    devices = NULL;
    num = 0;
    fprintf(stdout, "TEST: %s - list connected devices\n", __func__);
    ret = bt->get_connected_devices(&devices, &num);
    if (ret != S_OK)
        goto exit;
    print_devices(devices, num);
    bt->free_devices(devices, num);
    devices = NULL;
    num = 0;
exit:
    fprintf(stdout, "TEST: %s %s\n", __func__,
        (ret == S_OK) ? "succeeded" : "failed");
    if (devices && (num > 0))
        bt->free_devices(devices, num);
    return ret;

}