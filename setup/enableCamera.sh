if grep "start_x=1" /boot/config.txt
then
   exit
else
   if grep "start_x=0" /boot/config.txt
   then
      sed -i "s/start_x=0/start_x=1/g" /boot/config.txt
   else
      echo "start_x=1" >> /boot/config.txt
   fi
fi