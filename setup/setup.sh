echo "Run all scripts to configure the pi"
if [ $(id -u) -ne 0 ]; then echo "You must use sudo: sudo ./all.sh"; exit 1; fi
cd /home/pi
git clone https://www.github.com/Paulware/piTank
cd /home/pi/piTank
chmod 777 *.*
cd /boot/
# Copy setup files to /boot 
cp /home/pi/piTank/setup/*.sh .
apt-get update
apt-get install python-pexpect -y
apt-get install bluetooth bluez blueman -y
spt-get install motion
./ssh.sh
./keyboard.sh
./timezone.sh
./rclocal.sh
./ap.sh
./runTank.sh
./dtOverlay.sh
lsusb
ls /dev/video*
# camera: sudo modprobe bcm2835-v4l2
# v4l2-ctl -V
#mkdir /home/pi/Monitor
#sudo chgrp motion /home/pi/Monitor
#chmod g+rwx /home/pi/Monitor
#https://tutorials-raspberrypi.com/raspberry-pi-security-camera-livestream-setup/
#ifup wlan0
echo "Done in setup, Using the wifi icon on desktop:turn wifi on, and set wifi country"
echo "Pair to hc-06 joystick transmitter, modify /etc/rc.local with mac address of hc-06"
echo "Use raspi-config to enable the camera"
echo "Then reboot"
