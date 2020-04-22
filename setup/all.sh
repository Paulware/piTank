cd /home/pi/piTank
chmod 777 *.*
cd /boot/
# Copy setup files to /boot 
apt-get update
apt-get install expect -y
apt-get install python-pexpect -y
apt-get install bluetooth bluez blueman -y
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
./runTank.sh
./makeStreamerService.sh
./enableCamera.sh
./dtOverlay.sh
#cp /home/pi/piTank/setup/mjpg-streamer-experimental/mjpg_streamer.service /lib/systemd/system/mjpg_streamer.service
#systemctl enable mjpg_streamer.service
#systemctl disable mjpg-streamer.service
#systemctl start mjpg_streamer.service
#ifup wlan0
echo "Done in setup, Using the wifi icon on desktop:turn wifi on, and set wifi country"
echo "Then reboot to turn camera on"
echo "Place sd card in pizero-w, power up, connect to access point"
echo "Turn on the bluetooth device and then run ./connect.sh"
