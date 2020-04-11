#!/bin/bash
#
# see https://www.raspberrypi.org/documentation/configuration/wireless/access-point.md
# for more information
#

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

press_key () {
   userinput=""
   echo "Press ESC key to continue"
   # read a single character
   while read -r -n1 key
   do
   # if input == ESC key
   if [[ $key == $'\e' ]];
   then
   break;
   fi
   # Add the key to the variable which is pressed by the user.
   userinput+=$key
   done
   #printf "\nYou have typed : $userinput\n"
}


echo "modify /boot/config.txt" 
#press_key
if line_exists_in /boot/config.txt "gpio=6=op,dl"
then
  echo " "
  echo "/boot/config.txt has already been modified"
else
  echo "Adding dtoverlay info to /boot/config.txt low on boot, high on shutdown"
  echo "gpio=6=op,dl" >> /boot/config.txt
  echo "gpio=13=op,dl" >> /boot/config.txt
  echo "gpio=19=op,dl" >> /boot/config.txt
  echo "gpio=26=op,dl" >> /boot/config.txt
  echo "gpio=5=op,dl" >> /boot/config.txt
  echo "gpio=21=op,dl" >> /boot/config.txt
  echo "gpio=20=op,dl" >> /boot/config.txt  
fi
