import serial
import time
import threading
import os

def bindRfcomm0():
   try:
      print ("Binding rfcomm0" )
      os.system ('rfcomm connect /dev/rfcomm0 98:D3:31:20:53:D4 1') # 30:15:01:07:09:37 1' )
      print ( "Done binding rfcomm0, perhaps device disconnected" )
   except Exception as ex:
      print ( "bindRfcomm0 Got this exception: " + str(ex) + " try again" ) 
      time.sleep (3) 
      break

x = threading.Thread (target=bindRfcomm0)
x.start()

while True:
   try:
      port = serial.Serial("/dev/rfcomm0", baudrate=9600)
      print ("Successfully connected serial port" )
      break
   except Exception as ex: 
      print ("Unable to open serial port" )
      time.sleep (1)
      
try:
   count = 0
   while True:
      count = count + 1
      input = port.readline()
      print (str(count) + ' ' + input)
except Exception as ex:
   print ( "main exception: " + str(ex) ) 
   # Note: If the rf signal disappears, the serial port will disconnect
   #       and a [device disconnected] exception will occur
finally: 
   quit = True
   port.close()
