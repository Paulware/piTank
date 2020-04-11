echo "Run all scripts to configure the pi"
if [ $(id -u) -ne 0 ]; then echo "You must use sudo: sudo ./all.sh"; exit 1; fi
cd /home/pi
git clone https://www.github.com/Paulware/piTank
cd /home/pi/piTank
touch mainConfig.txt
chmod 777 *.*
cd /boot/
# Copy setup files to /boot 
cp /home/pi/piTank/setup/*.sh .
cp /boot/runPython.sh /home/pi/Desktop/runPython.sh
chmod 777 /home/pi/Desktop/runPython.sh
apt-get update
./ssh.sh
./keyboard.sh
./timezone.sh
# echo "dns-nameservers 8.8.8.8 8.8.4.4" >> /etc/network/interfaces
./ap.sh
pip install glob3
./runTank.sh
./dtOverlay.sh
apt-get install bluetooth bluez blueman -y
#ifup wlan0
echo "Done in setup, Using the wifi icon on desktop:turn wifi on, and set wifi country.  Then reboot"


