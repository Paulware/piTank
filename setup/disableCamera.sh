if grep "start_x=0" /boot/config.txt
then
   exit
else
   sed -i "s/start_x=1/start_x=0/g" /boot/config.txt
fi