cd /home/pi/piTank
chmod 777 *.*
cd /boot/
# Copy setup files to /boot 
apt-get update
apt-get install python-pexpect -y
apt-get install bluetooth bluez blueman -y
apt-get install motion -y
# Note: raspberry pi camera is preferred due to less lag, using mjpg-streamer
# For raspberry pi camera 
#   enable camera using raspi-config
#   run /home/pi/piTank/setup/mjpg-streamer-experimental/go.sh
# Note: mjpgStreamer is already built
#./mjpgStreamer.sh
./ssh.sh
./keyboard.sh
./timezone.sh
./rclocal.sh
./ap.sh
./runTank.sh
./dtOverlay.sh
#ifup wlan0
echo "Done in setup, Using the wifi icon on desktop:turn wifi on, and set wifi country"
echo "Pair to hc-06 joystick transmitter, modify /etc/rc.local with mac address of hc-06"
echo "Use raspi-config to enable the camera"
echo "Then reboot"
