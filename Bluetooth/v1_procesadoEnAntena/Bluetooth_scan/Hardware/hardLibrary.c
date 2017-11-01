#include </usr/include/artik/base/artik_module.h>
#include </usr/include/artik/base/artik_loop.h>
#include </usr/include/artik/bluetooth/artik_bluetooth.h>

#include "hardLibrary.h";

static artik_bluetooth_module *bt = NULL;
static int numD;
static artik_bt_device *devB = NULL;

/*
------------------------------------------------------------------------------------------------------------------------------------
	Obtención de los dispositivos bluetooth ya conocidos, funciones que permiten realizarla. 
------------------------------------------------------------------------------------------------------------------------------------
*/

artik_error lista_dispositivos_emparejados_Bluetooth_F(artik_bt_device *devices, int *num){
    artik_error ret = S_OK;
    int num1 = 0;
	int num2 = 0;
	
    bt = (artik_bluetooth_module *)artik_request_api_module("bluetooth");
	if (!bt) { return -1;}
	
    ret = bt->get_devices(&devices, &num1);
    if (ret != S_OK)
        goto exit;   
		
    ret = bt->get_connected_devices(&devices+num1, &num2);
    if (ret != S_OK)
        goto exit;
    *num=num1+num2;
	
exit:
    if (devices && (num1 > 0 || num2 > 0)) {
        bt->free_devices(devices, num1+num2);
	}
    return ret;
}

/*
------------------------------------------------------------------------------------------------------------------------------------
    Obtención de dispositivos bluetooth cercanos, funciones que permiten realizarla. 
------------------------------------------------------------------------------------------------------------------------------------
*/

// Funciones auxiliares 

static void scan_callback(artik_bt_event event, void *data, void *user_data)
{
    artik_bt_device *dev = (artik_bt_device *) data;
	*(devB+numD) = *dev;
	numD++;
}

static void on_timeout_callback(void *user_data)
{
    artik_loop_module *loop = (artik_loop_module *) user_data;    
    loop->quit();
}

// Función principal

artik_error lista_dispositivos_cercanos_Bluetooth_F(artik_bt_device *devices, int *num, int timer)
{
    artik_loop_module *loop = (artik_loop_module *)artik_request_api_module("loop");
    artik_error ret = S_OK;
    bt = (artik_bluetooth_module *)artik_request_api_module("bluetooth");
	if (!bt) { return -1;}
    int timeout_id = 0;
    
    ret = bt->set_callback(BT_EVENT_SCAN, scan_callback, NULL);	
    if (ret != S_OK)
        goto exit;
	
    ret = bt->start_scan();
    if (ret != S_OK)
        goto exit;
	
    loop->add_timeout_callback(&timeout_id, timer, on_timeout_callback,
                   (void *)loop);
    loop->run();
	*num = numD;
	
	for (int i = 0; i<numD ; i++) {
		*(devices+i) = *(devB+i);
	}
	
exit:
    bt->stop_scan();
    bt->unset_callback(BT_EVENT_SCAN);
    artik_release_api_module(loop);
    return ret;
}

