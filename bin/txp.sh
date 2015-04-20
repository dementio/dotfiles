#CHange MAC Address
sudo airmon-ng stop wlan1
sudo iwconfig wlan1
sudo ifconfig wlan1 down
sudo macchanger --mac 00:11:22:33:44:55 wlan1
sudo ifconfig wlan1

#Device Busy
sudo iwconfig wlan1
sudo ifconfig wlan1 down
sudo iwconfig wlan1 mode monitor
sudo ifconfig wlan1 up
sudo iwconfig wlan1
sudo airodump-ng wlan1
sleep 30

dmesg|tail -20
sudo rmmod rtl8187
sudo rfkill block all
sudo rfkill unblock all
sudo modprobe rtl8187
sudo rfkill unblock all
sudo ifconfig wlan1 up
sudo airmon-ng start wlan1
sudo airmon-ng
sudo airodump-ng mon1
sudo ifconfig wlan1 down
sudo iwconfig wlan1 mode monitor
sudo ifconfig wlan1 up
sudo iwconfig wlan1
sudo aireplay-ng -9 wlan1

#Change TX Power
iw reg set BO
iwconfig wlan1 txpower 30dbm

#Test Injection
sudo aireplay-ng -9 wlan1
