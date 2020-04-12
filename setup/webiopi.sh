echo "Install webiopi"
wget http://sourceforge.net/projects/webiopi/files/WebIOPi-0.7.1.tar.gz
tar xvzf WebIOPi-0.7.1.tar.gz
cd WebIOPi-0.7.1
wget https://raw.githubusercontent.com/neuralassembly/raspi2/master/webiopi-pi2bplus.patch
patch -p1 -i webiopi-pi2bplus.patch
sudo ./setup.sh
echo "(Please answer with 'n' for the last question)"