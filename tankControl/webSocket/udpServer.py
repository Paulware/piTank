import socket
import msvcrt
import select
import sys
 
# windows only
def getKeyboard():
   char = ''
   if msvcrt.kbhit():
      char = msvcrt.getch()
   return char
   
def matchString (commands, ch):
   match = -1
   count = 0
   for command in commands:
      text = command[0]
      index = command[1]
      if text[index] == ch: 
         index = index + 1
      else:
         index = 0
      command[1] = index   
         
      if index == text.__len__():
         match = count
         command[1] = 0
         break
      else:
         count = count + 1
         
   return (commands, match)    
  
# Format of command: sensorName command param
port = 3333
myAddress = socket.gethostbyname(socket.gethostname())
print myAddress
index = myAddress.rfind ('.')
print str(index)
clientIp = myAddress[0:index] + '.255'
clientIp = '192.168.100.3'
print clientIp
sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
sensorName = 'temp1'
msg = 'server ' + myAddress
sock.sendto(msg, (clientIp, port))
print 'Sent ' + msg + ' to ' + clientIp + ':' + str(port) + '\n'
print 'Press any keys (1..3) to send commands, q to quit'
commands = [['quit',0],['relayon ',0], ['relayoff ',0], ['read ',0], ['status',0], ['findsensor ', 0], 
            ['name ',0], ['findkey', 0],['temp', 0], ['on ', 0], ['off ', 0]]
print 'Commands: ' + str(commands)
parameter = ''
match = -1
while True:
    ch = getKeyboard ()
   
    if ch != '':
       sys.stdout.write (ch)
       if ch == chr(8):
          print 'backspace is ignored'
       elif ch == chr(13):
          if match == -1:
             print 'No command to execute'             
          elif match == 0: # quit
             break 
          elif match == 6: # Set the name 
             sensorName = parameter 
             print 'sensorName == ' + sensorName   
          else:
             cmd = commands[match][0]
             if match == 7: # find key (command goes first)
                cmd = cmd + ' ' + sensorName          
             else:
                cmd = sensorName + ' ' + cmd + parameter             
  
             print 'send ' + cmd + ' to ' + clientIp
             sock.sendto (cmd, (clientIp,port))           
                     
          parameter = ''
          match = -1   
          
       elif ch == chr(10):
          print 'Ignore newline'       
       elif match > -1: 
          parameter = parameter + ch        
       else:
          # commands are returned because indexes change
          (commands,match) = matchString (commands, ch)
          
          
    data = ''  
    addr = ''   
    i,o,e = select.select ([sock],[],[],0.0001)
    for s in i:
       if s == sock:
          data, addr = sock.recvfrom(1024)      
          print "rcvd:" + data + ' from: ' + str(addr[0])    
          break
          
sock.close()