#!/usr/bin/expect -f

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
send "trust $address\r"
sleep 2
send "connect $address\r"
send_user  "Done connecting?\r"
sleep 3
send_user "\nShould be connected now.\r"
send "quit\r"
expect eof
