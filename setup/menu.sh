EDITOR=vim
PASSWD=/etc/passwd
RED='\033[0;41;30m'
STD='\033[0;0;39m'
pause(){
  read -p "Press [Enter] key to continue.." fackEnterKey
}
one(){
  echo "one() called"
  cd /boot
  python menuGrid.py
     pause
}

two(){
  echo "two() called"
     pause
}

show_menus(){
   clear
   echo "~~~~~~~~~~~~~~~~~~"
   echo " M A I N - M E N U"
   echo "~~~~~~~~~~~~~~~~~~"
   echo "1. pygame menu"
   echo "2. tank control"
   echo "3. pixel matrix"
}   
read_options(){
   local choice
   read -p "Enter choice [1..3]" choice
   case $choice in
      1) one ;;
      2) two ;;
      3) exit 0;;
      *) echo -e "${RED}Error...${STD}" && sleep 2
   esac
}
while true
do
   show_menus
   read_options
done