#include </usr/include/artik/base/artik_module.h>
#include </usr/include/artik/base/artik_loop.h>
#include </usr/include/artik/bluetooth/artik_bluetooth.h>



static artik_bluetooth_module *bt = NULL;



/*
------------------------------------------------------------------------------------------------------------------------------------
	Impresion de los dispositivos bluetooth ya conocidos, funciones que permiten realizarla. 
------------------------------------------------------------------------------------------------------------------------------------
*/

artik_error lista_dispositivos_emparejados_Bluetooth(artik_bt_device *devices, int *num ){
    artik_error ret = S_OK;
    int num1 = 0;
    bt = (artik_bluetooth_module *)artik_request_api_module("bluetooth");
    ret = bt->get_devices(&devices, &num1);
    if (ret != S_OK)
        goto exit;
    int num2 = 0;
    ret = bt->get_connected_devices(&devices+num1, &num2);
    if (ret != S_OK)
        goto exit;
    num=num1+num2;
exit:
    if (devices && (num1 > 0 || num2 > 0))
        bt->free_devices(devices, num);
    return -1;

}

/*
------------------------------------------------------------------------------------------------------------------------------------
    Busqueda de dispositivos bluetooth cercanos, funciones que permiten realizarla. 
------------------------------------------------------------------------------------------------------------------------------------
*/

// Funciones auxiliares 

static void scan_callback(artik_bt_event event, void *data, void *user_data)
{
    artik_bt_device *dev = (artik_bt_device *) data;
}
static void on_timeout_callback(void *user_data)
{
    artik_loop_module *loop = (artik_loop_module *) user_data;
    fprintf(stdout, "TEST: %s stop scanning, exiting loop\n", __func__);
    loop->quit();
}

// Función principal

artik_error scanBluetooth(void)
{
    artik_loop_module *loop = (artik_loop_module *)artik_request_api_module("loop");
    artik_error ret = S_OK;
    bt = (artik_bluetooth_module *)artik_request_api_module("bluetooth");
    int timeout_id = 0;
    fprintf(stdout, "TEST: %s starting\n", __func__);
    ret = bt->set_callback(BT_EVENT_SCAN, scan_callback, NULL);
    if (ret != S_OK)
        goto exit;
    ret = bt->start_scan();
    if (ret != S_OK)
        goto exit;
    loop->add_timeout_callback(&timeout_id, 20000, on_timeout_callback,
                   (void *)loop);
    loop->run();
exit:
    bt->stop_scan();
    bt->unset_callback(BT_EVENT_SCAN);
    fprintf(stdout, "TEST: %s %s\n", __func__,
        (ret == S_OK) ? "succeeded" : "failed");
    artik_release_api_module(loop);
    return ret;
}

