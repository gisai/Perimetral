#include </usr/include/artik/base/artik_module.h>
#include </usr/include/artik/base/artik_loop.h>
#include </usr/include/artik/bluetooth/artik_bluetooth.h>

#include "../Hardware/hardLibrary.h";

int main (int argc, char** argv) {
	int pipe = atoi(argv[1]);
	
	artik_bt_device *devices = NULL;
	int *num = 0;
	artik_error ret = S_OK;
	
	ret = lista_dispositivos_cercanos_Bluetooth_F (devices, num, 20000);
	
	fprintf(pipe, "{closeDevices:[");
	
	for (i = 0; i < *num; i++) {
        fprintf(pipe, "{deviceAddr:%s,\n",
            devices[i].remote_address ? devices[i].
            remote_address : "(null)");
        fprintf(pipe, "ID:%s},\n",
            devices[i].remote_name ? devices[i].
            remote_name : "(null)");        
    }	
	fprintf(pipe, "{}]}");
}