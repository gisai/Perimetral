#systemctl stop hostapd
#systemctl stop dnsmasq
#modprobe -r dhd
#modprobe dhd op_mode=0
#ifconfig wlan0 up
#if [ -f "/usr/lib/systemd/system/wpa_supplicant.service" ]; then
#  systemctl restart wpa_supplicant
#fi

modprobe -r dhd 
modprobe dhd op_mode=2 
ifconfig wlan0 192.168.1.1 up 
dnsmasq -C /etc/dnsmasq.conf 
./aproute.sh 
hostapd /etc/hostapd/hostapd.conf -B
node ./wifi-avanzado/index.js
