echo "#!/bin/sh -e" > /etc/rc.local
echo "rfcomm bind 0 98:D3:31:20:53:D4 1" >> /etc/rc.local
echo "exit 0" >> /etc/rc.local