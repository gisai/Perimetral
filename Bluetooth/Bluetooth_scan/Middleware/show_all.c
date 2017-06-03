
/*

Created by Sergio García García

Programa que muestra conjuntamente tanto los dispositivos 
bluetooth emparejados anteriormente como los dispositvos
bluetooth cercanos en la actualidad. 

Uso de las librerías scan.c y devices.c

*/

#include </usr/include/artik/base/artik_module.h>
#include </usr/include/artik/base/artik_loop.h>
#include </usr/include/artik/bluetooth/artik_bluetooth.h>

#include "../Hardware/scan.h"
#include "../Hardware/devices.h"


int show_all(){
	devicesBluetooth();
	scanBluetooth();
}