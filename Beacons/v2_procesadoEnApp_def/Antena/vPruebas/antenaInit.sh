#!/bin/bash

# Código de inicialización de antenas Beacon
# PERIMETER SECURITY
# 2017
# Borja Bordel GISAI UPM

#IMPORTANTE Para poder aplicar la conexión USB esta antena debe
#tener activado el servidor ADB

#systemctl start adbd.service
#systemctl enable adbd.service

#Reiniciamos todos los módulos Bluetooth por si hubiera algún 
#sistema caído
service bluetooth restart
service dbus restart 
hciconfig hci0 reset 

touch /root/prueba.txt

root/beaconAntena.sh /root/prueba.txt