
cat > /lib/systemd/system/streamer.service <<EOF
#filename:  /lib/systemd/system/streamer.service
[Unit]
Description=Start MJPG Streamer

[Service]
Environment=DISPLAY=:0
Environment=XAUTHORITY=/home/pi/.Xauthority
WorkingDirectory=/home/pi/piTank/setup/mjpg-streamer-experimental
ExecStart=/usr/bin/python3 /home/pi/piTank/setup/mjpg-streamer-experimental/go.py
#ExecStartPre=/bin/sleep 2
Restart=no
RestartSec=10s
KillMode=process
TimeoutSec=infinity

[Install]
WantedBy=graphical.target


EOF

chmod 644 /lib/systemd/system/streamer.service
systemctl daemon-reload
systemctl enable streamer
systemctl start streamer
chmod 777 /home/pi/piTank/setup/mjpg-streamer-experimental/*.*
chmod 777 /home/pi/piTank/setup/mjpg-streamer-experimental/mjpg_streamer
# remove the autorun option from the file manager
#sed -i 's/autorun=1/autorun=0/' /home/pi/.config/pcmanfm/LXDE-pi/pcmanfm.conf
#export DISPLAY=desktop:0
echo "On reboot the streamer service should be running yo"

