echo "Install webiopi part 2"
wget https://raw.githubusercontent.com/neuralassembly/raspi2/master/webiopi.service
sudo mv webiopi.service /etc/systemd/system/
echo "To start: "
echo "sudo service webiopi start"
echo "To stop:"
echo "sudo service webiopi stop"