
cat > /lib/systemd/system/backdoor.service <<EOF
#filename:  /lib/systemd/system/backdoor.service
[Unit]
Description=Start Backdoor

[Service]
Environment=DISPLAY=:0
Environment=XAUTHORITY=/home/pi/.Xauthority
WorkingDirectory=/home/pi/piTank
ExecStart=/usr/bin/python3 tank.py
ExecStartPre=/bin/sleep 2
Restart=always
RestartSec=10s
KillMode=process
TimeoutSec=infinity

[Install]
WantedBy=graphical.target


EOF

chmod 644 /lib/systemd/system/backdoor.service
systemctl daemon-reload
systemctl enable backdoor
systemctl start backdoor
# remove the autorun option from the file manager
#sed -i 's/autorun=1/autorun=0/' /home/pi/.config/pcmanfm/LXDE-pi/pcmanfm.conf
#export DISPLAY=desktop:0
echo "Note: You will need to pair the HC-06 with the pi before getting data."

