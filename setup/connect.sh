#!/usr/bin/expect -f

set prompt "#"
set address [lindex $argv 0]

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
send_user "\nSleeping 10 seconds\r"
sleep 10
send_user "\nDone sleeping\r"
send "scan off\r"
expect "Controller"
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
