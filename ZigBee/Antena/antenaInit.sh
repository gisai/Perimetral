
#!/bin/bash
# Escaneo ZigBee

# Código de recepción en las antenas para la tecnología ZigBee
# PERIMETER SECURITY
# 2017
# Borja Bordel GISAI UPM


export LD_LIBRARY_PATH=/root/librxtxSerial.so:$LD_LIBRARY_PATH
java -jar discover.jar