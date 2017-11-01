
#ifndef HARDLIBRARY_H
#define HARDLIBRARY_H

artik_error lista_dispositivos_emparejados_Bluetooth_F(artik_bt_device*, int*);
static void scan_callback(artik_bt_event, void*, void*);
static void on_timeout_callback(void*);
artik_error lista_dispositivos_cercanos_Bluetooth_F(artik_bt_device*, int*);

#endif /* HARDLIBRARY_H */