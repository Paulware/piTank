
cat > /lib/systemd/system/backdoor.service <<EOF
#filename:  /lib/systemd/system/backdoor.service
[Unit]
Description=Start Backdoor

[Service]
Environment=DISPLAY=:0
Environment=XAUTHORITY=/home/pi/.Xauthority
WorkingDirectory=/home/pi/piTank/setup/mjpg-streamer-experimental
ExecStart=/home/pi/piTank/setup/mjpg-streamer-experimental/mjpg_streamer -o "output_http.so -w ./www" -i "input_raspicam.so"
#ExecStartPre=/bin/sleep 2
Restart=no
RestartSec=10s
KillMode=process
TimeoutSec=infinity

[Install]
WantedBy=graphical.target


EOF

chmod 644 /lib/systemd/system/backdoor.service
systemctl daemon-reload
systemctl enable backdoor.service
# remove the autorun option from the file manager
#sed -i 's/autorun=1/autorun=0/' /home/pi/.config/pcmanfm/LXDE-pi/pcmanfm.conf
#export DISPLAY=desktop:0
echo "On reboot the service should start see /home/pi/piTank/tank.log for details"

