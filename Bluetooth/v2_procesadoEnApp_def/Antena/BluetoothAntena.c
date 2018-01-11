#include </usr/include/artik/base/artik_module.h>
#include </usr/include/artik/base/artik_loop.h>
#include </usr/include/artik/bluetooth/artik_bluetooth.h>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>

static artik_bluetooth_module *bt = NULL;

int idAntena = 1;
int potenciaDBM = 8;

/*
------------------------------------------------------------------------------------------------------------------------------------
    Obtención de dispositivos bluetooth cercanos, funciones que permiten realizarla. 
------------------------------------------------------------------------------------------------------------------------------------
*/

// Funciones auxiliares 
static void scan_callback(artik_bt_event event, void *data, void *user_data)
{
    artik_bt_device *dev = (artik_bt_device *) data;
    printf("{ID: {IDSystem:%d, IDGroup:%s, IDPerson:%s}, IDAnte:%d, pow:%d, rssi:%d, time:%d}", dev.manufacturer_id, dev.remote_name, dev.remote_address, idAntena, potenciaDBM, dev.rssi, time(NULL));
}

// Función principal

artik_error lista_dispositivos_cercanos_Bluetooth_F()
{
    artik_loop_module *loop = (artik_loop_module *)artik_request_api_module("loop");
    artik_error ret = S_OK;
    bt = (artik_bluetooth_module *)artik_request_api_module("bluetooth");
	if (!bt) { return -1;}
    
    ret = bt->set_callback(BT_EVENT_SCAN, scan_callback, NULL);	
    if (ret != S_OK)
        goto exit;
	
    ret = bt->start_scan();
    if (ret != S_OK)
        goto exit;

    loop->run();
	
exit:
    bt->stop_scan();
    bt->unset_callback(BT_EVENT_SCAN);
    artik_release_api_module(loop);
    return ret;
}


void main () {
	error lista_dispositivos_cercanos_Bluetooth_F();
}