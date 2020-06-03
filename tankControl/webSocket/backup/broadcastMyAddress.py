import socket
import sys

def broadcastAddress(): 
   port = 3333
   myAddress = socket.gethostbyname(socket.gethostname())
   print (myAddress)
   index = myAddress.rfind ('.')
   clientIp = myAddress[0:index] + '.255'
   sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
   msg = 'server ' + myAddress
   print ('Send ' + msg + ' to ' + clientIp + ':' + str(port) + '\n')
   msg = msg.encode()
   sock.sendto(msg, (clientIp, port))
   
broadcastAddress()