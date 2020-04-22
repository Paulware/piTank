#!/usr/bin/expect -f
#  Filename: connect.sh
#  Note: the mac address must be the first parameter to this command file when run

set prompt "#"
set address [lindex $argv 0]

spawn sudo bluetoothctl 
# -a
expect -re $prompt
send "remove $address\r"
sleep 1
expect -re $prompt
send "scan on\r"
send_user "\nSleeping 10 seconds\r"
sleep 10
send_user "\nDone sleeping\r"
send "scan off\r"
expect "Controller"
send "pair $address\r"
sleep 2
send "1234\r"
send_user "\nShould be connected now.\r"
send "quit\r"
expect eof
