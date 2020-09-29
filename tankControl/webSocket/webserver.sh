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

cat > /lib/systemd/system/websocketserver.service <<EOF
#filename:  /lib/systemd/system/websocketserver.service
[Unit]
Description=Start websocket server

[Service]
Environment=DISPLAY=:0
Environment=XAUTHORITY=/home/pi/.Xauthority
ExecStart=/bin/bash -c 'cd /home/piTank;/usr/bin/python3 webSocketServer.py > /home/piTank/webSocketServer.log 2>&1'
Restart=always
RestartSec=10s
KillMode=process
TimeoutSec=infinity

[Install]
WantedBy=graphical.target


EOF

chmod 644 /lib/systemd/system/websocketserver.service
systemctl daemon-reload
systemctl enable websocketserver.service

echo "On reboot the service should start see /home/piTank/websocketserver.log for details"

