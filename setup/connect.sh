#!/usr/bin/expect -f

set prompt "#"
set address [lindex $argv 0]

if {$address eq ""} {
   send_user "You must specify mac address of the bluetooth device"
   send_user "Usage example: ./connect.sh 98:D3:31:20:53:D4"
} else {

   spawn sudo bluetoothctl 
   # -a
   send "power on\r"
   sleep 1
   expect -re "Changing"
   send "remove $address\r"
   sleep 1
   expect -re $prompt
   send "pairable on\r"
   sleep 1
   expect -re "Changing"
   send "scan on\r"
   send_user "\nSleeping 15 seconds\r"
   sleep 15
   send_user "\nDone sleeping\r"
   expect -re $prompt
   send "scan off\r"
   expect "Discovery"
   sleep 2
   send_user "\nPair with device\r"
   send "pair $address\r"
   sleep 2
   expect "agent"
   send "1234\r"
   sleep 2
   expect -re "Pairing"
   sleep 1
   send_user "\rShould be now paired.\r"
   send "quit\r"
   expect eof
}