# To run mjpgStreamer for picam: 
# cd /home/pi/piTank/setup/mjpg-streamer-experimental
# ./go.sh 
# Stream will appear at 192.168.4.1:8080

#Note following is for mjpgStreamer of a web-cam (not recommended)
#cd /home/pi/piTank/setup/mjpg-streamer-experimental
#sudo cp mjpg_streamer /usr/local/bin
#cp /home/pi/piTank/setup/mjpg-streamer-experimental/*.so /usr/local/lib/.
#sudo cp -R /home/pi/piTank/setup/mjpg-streamer-experimental/www /usr/local/www
#echo "export LD_LIBRARY_PATH=/usr/local/lib/" >> ~/.bashrc
#sudo vi /usr/sbin/livestream.sh
#     #!/bin/bash
#     /usr/local/bin/mjpg_streamer -i "/usr/local/lib/input_uvc.so" -o "/usr/local/lib/output_http.so -w /var/www/stream -c username:password"
#cp /usr/sbin/livestream.sh /etc/init.d/livestream.sh
#sudo chmod 755 /etc/init.d/livestream.sh
#sudo update-rc.d livestream.sh defaults
#apt-get install uvcdynctrl -y
#lsusb
#uvcdynctrl -f
#ls /dev/video*
# To Run mjpg-streamer:
# mjpg_streamer -o "/usr/local/lib/output_http.so -w /usr/local/www -i /usr/local/lib/input_raspicam.so"
# camera: sudo modprobe bcm2835-v4l2
# v4l2-ctl -V
#mkdir /home/pi/Monitor
#sudo chgrp motion /home/pi/Monitor
#chmod g+rwx /home/pi/Monitor
#https://tutorials-raspberrypi.com/raspberry-pi-security-camera-livestream-setup/
