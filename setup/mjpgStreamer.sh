echo "Camera should be enabled first: sudo raspi-config"
sudo sudo apt-get install cmake libjpeg8-dev -y
sudo apt-get install gcc g++ -y

cd mjpg-streamer-experimental
make
sudo make install

sudo cp mjpg_streamer /usr/local/bin
sudo cp output_http.so input_file.so /usr/local/lib/
sudo cp -R www /usr/local/www
sudo mkdir /tmp/stream
chmod 777 /tmp/stream
export LD_LIBRARY_PATH=.
./mjpg_streamer -o "output_http.so -w ./www" -i "input_raspicam.so -hf"
# raspistill --nopreview -w 640 -h 480 -q 5 -o /tmp/stream/pic.jpg -tl 100 -t 9999999 -th 0:0:0 &
