echo "Run all scripts to configure the pi"
echo " first parameter is the mac address of the bt joystick"
echo "Usage example: ./setup.sh 98:D3:31:20:53:D4"
if [ $(id -u) -ne 0 ]; then echo "You must use sudo: sudo ./setup.sh"; exit 1; fi
if [ -z "$1" ]; then echo "You must specify mac address of bt device"; exit 1; fi
cd /home/pi
git clone https://www.github.com/Paulware/piTank
cd /boot/
cp /home/pi/piTank/setup/*.sh .
chmod 777 *.sh
./all.sh $1
