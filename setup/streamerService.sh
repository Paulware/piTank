cat > /lib/systemd/system/streamer.service <<EOF
#filename:  /lib/systemd/system/streamer.service
[Unit]
Description=Start Backdoor

[Service]
Environment=DISPLAY=:0
Environment=XAUTHORITY=/home/pi/.Xauthority
ExecStart=sudo ./home/pi/piTank/setup/runStreamer.sh
#ExecStartPre=/bin/sleep 2
Restart=always
RestartSec=10s
KillMode=process
TimeoutSec=infinity

[Install]
WantedBy=graphical.target


EOF

chmod 644 /lib/systemd/system/streamer.service
systemctl daemon-reload
systemctl enable streamer.service
echo "On reboot the streamer service should start"