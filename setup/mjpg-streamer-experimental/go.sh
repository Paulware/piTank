export LD_LIBRARY_PATH=.
#export LD_LIBRARY_PATH=/home/pi/piTank/setup/mjpg-streamer-experimental/
/home/pi/piTank/setup/mjpg-streamer-experimental/mjpg_streamer -o "output_http.so -w ./www" -i "input_raspicam.so"

