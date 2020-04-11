if [ "$EUID" -ne 0 ]
	then echo "Must be root"
	exit
fi

file_exists() {
   if [ -e $1 ]
   then
       # file found 
       return 0
   else
       return 1
   fi
}

# return true if line exists
line_exists_in () {
   if grep -Fxq "$2" $1
   then
      return 0
   else
      return 1
   fi
}

#mkdir /share/WOD
#cp /boot/*.py /share/WOD/.
#cp /boot/x.png /share/WOD/.

cat > /lib/systemd/system/backdoor.service <<EOF
#filename:  /lib/systemd/system/backdoor.service
[Unit]
Description=Start Backdoor

[Service]
Environment=DISPLAY=:0
Environment=XAUTHORITY=/home/pi/.Xauthority
ExecStart=/bin/bash -c 'cd /home/pi/piTank;/usr/bin/python3 tank.py > /home/pi/piTank/tank.log 2>&1'
ExecStartPre=/bin/sleep 12
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
export DISPLAY=desktop:0
echo "On reboot the service should start see /share/WOD/sshBackdoor.log for details"

