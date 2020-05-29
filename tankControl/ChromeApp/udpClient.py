
import socket
import time
from time import localtime, strftime 
import select
import sys
 
UDP_PORT = 3333

sock = socket.socket(socket.AF_INET, # Internet
                     socket.SOCK_DGRAM) # UDP
sock.bind(('', UDP_PORT))
sock.setblocking(0) # turn off blocking
print ('   UDP Client    press any key to stop\n') 
print (socket.gethostbyname(socket.gethostname()) + ' Listening at port 3333')

while True:
   i,o,e = select.select ([sock],[],[],0.0001)
   recvData = False
   for s in i:
      if s == sock:
         data, addr = sock.recvfrom(1024)           
         print ("received message:" + str(data) + ' from: ' + str(addr[0]))

print ('Done in udpClient.py')