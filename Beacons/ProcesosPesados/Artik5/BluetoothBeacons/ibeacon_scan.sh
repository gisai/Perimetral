#!/bin/bash
# iBeacon Scan 


# Funciones que permiten obtener y poner en formato los diferentes campos de un beacon
function parse_ib_uuid {
    UUID=`echo $1 | sed 's/^.\{69\}\(.\{47\}\).*$/\1/'`
    UUID=`echo $UUID | sed -e 's/\ //g' -e 's/^\(.\{8\}\)\(.\{4\}\)\(.\{4\}\)\(.\{4\}\)\(.\{12\}\)$/\1-\2-\3-\4-\5/'`
}

function parse_ib_major {
    MAJOR=`echo $1 | sed 's/^.\{117\}\(.\{5\}\).*$/\1/'`
    MAJOR=`echo $MAJOR | sed 's/\ //g'`
    MAJOR=`echo "ibase=16; $MAJOR" | bc`
}

function parse_ib_minor {
    MINOR=`echo $1 | sed 's/^.\{123\}\(.\{5\}\).*$/\1/'`
    MINOR=`echo $MINOR | sed 's/\ //g'`
    MINOR=`echo "ibase=16; $MINOR" | bc`
}

function parse_ib_power {
    POWER=`echo $1 | sed 's/^.\{129\}\(.\{2\}\).*$/\1/'`
    POWER=`echo "ibase=16; $POWER" | bc`
    POWER=$[POWER - 256]
}

function parse_rssi {
      LEN=$[${#1} - 2]
      RSSI=`echo $1 | sed "s/^.\{$LEN\}\(.\{2\}\).*$/\1/"`
      RSSI=`echo "ibase=16; $RSSI" | bc`
      RSSI=$[RSSI - 256]
}

# Ejecución de las lineas de comando adecuadas para obtener los beacons.
if [[ $1 == "parse" ]]; then
    packet=""
    capturing=""
    count=0
    while read line
    do
        count=$[count + 1]
        if [ "$capturing" ]; then
            if [[ $line =~ ^[0-9a-fA-F]{2}\ [0-9a-fA-F] ]]; then
                packet="$packet $line"
            else
                if [[ $packet =~ ^04\ 3E\ 2A\ 02\ 01\ .{26}\ 02\ 01 ]]; then
                    parse_ib_uuid "$packet"
                    parse_ib_major "$packet"
                    parse_ib_minor "$packet"
                    parse_ib_power "$packet"
                    parse_rssi "$packet"
                    if [[ $2 == "-b" ]]; then
	                    echo "$UUID $MAJOR $MINOR $POWER $RSSI"
                    else
                        # Escribimos el beacon en un archivo, llamado evento.txt
    	                echo  "$UUID $MAJOR $MINOR $POWER $RSSI" > evento.txt
                    fi
                fi
                capturing=""
                packet=""
            fi
        fi

        if [ ! "$capturing" ]; then
            if [[ $line =~ ^\> ]]; then
                packet=`echo $line | sed 's/^>.\(.*$\)/\1/'`
                capturing=1
            fi
        fi
    done
else
    hcitool lescan  1>/dev/null &
    if [ "$(pidof hcitool)" ]; then
        hcidump --raw | ./$0 parse $1
    fi
fi