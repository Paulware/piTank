echo "#!/bin/sh -e" > /etc/rc.local
echo "rfcomm bind 0 $1 1" >> /etc/rc.local
echo "exit 0" >> /etc/rc.local