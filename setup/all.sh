cd /home/pi/piTank
chmod 777 *.*
cd /boot/
# Copy setup files to /boot 
apt-get update
apt-get install expect -y
apt-get install python-pexpect -y
apt-get install bluetooth bluez -y
# Bluetooth manager
# apt-get install blueman -y
#apt-get install motion -y
# Note: raspberry pi camera is preferred due to less lag, using mjpg-streamer
# For raspberry pi camera 
#   enable camera using raspi-config
#   run /home/pi/piTank/setup/mjpg-streamer-experimental/go.sh
# Note: mjpgStreamer is already built
#./mjpgStreamer.sh
./ssh.sh
./keyboard.sh
./timezone.sh
./rclocal.sh $1
./ap.sh
# Run /home/pi/piTank/tankControl/tankControl.py on boot up
./runTank.sh
#./makeStreamerService.sh
#./enableCamera.sh
#./dtOverlay.sh
#cp /home/pi/piTank/setup/mjpg-streamer-experimental/mjpg_streamer.service /lib/systemd/system/mjpg_streamer.service
#systemctl enable mjpg_streamer.service
#systemctl disable mjpg-streamer.service
#systemctl start mjpg_streamer.service
#ifup wlan0
echo "Done in setup, Using the wifi icon on desktop:turn wifi on, and set wifi country"
echo "Then with raspi-config enable SPI and I2C, then shutdown"
echo "Move sd card to pi-zero w, connect to Walker (SSID) with password 1234ABCD, "
echo " Turn on HC-06, and run /boot/connect.sh from putty to pair with HC-06 receiver" 