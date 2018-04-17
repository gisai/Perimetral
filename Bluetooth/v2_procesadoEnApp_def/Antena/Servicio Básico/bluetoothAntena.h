/**
 * Fichero con las rutinas de BlueZ necesarias
 * para escanear con Bluetooth
 * PERIMETER SECURITY
 */

#ifndef BLUETOOTHANTENA_H_
#define BLUETOOTHANTENA_H_

//Tiempo de reinicio, igual al tiempo máximo de escaneo en BT
//10 segundos aproximadamente
#define SCAN_TIME_MILLISECONDS 10000


//Prototipos de funciones
static void scan_callback(artik_bt_event, void*, void*);
static void scan_timeout_callback(void*);
artik_error lista_dispositivos_cercanos_Bluetooth_F();
int main(int, char*[]);


#endif /* BLUETOOTHANTENA_H_ */
