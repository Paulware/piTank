import serial
import time
import multiprocessing
import os

class HC06: 
 
   def close(self):
      print ("HC06 cleanup and close")
      self.port.close()
      self.x.terminate()
      self.x.join()

   def bindRfcomm0(self):
      cmd = 'rfcomm connect /dev/rfcomm0 ' + self.macAddress + ' 1'
      # keep trying to bind forever, the only way to kill is with self.x.terminate()
      while True:
         print (cmd)
         try:
            os.system (cmd) # 0 considered good 
         except Exception as ex:
            print ( "bindRfcomm0 Got this exception: " + str(ex) + " ignore it") 
      
   def __init__(self, macAddress):  
      self.macAddress = macAddress
      self.disconnected = False
      print ('Note you must pair with the HC05 (' + macAddress + ' via bluetooth manager before calling this procedure' )   
      self.x = multiprocessing.Process(target=self.bindRfcomm0)
      self.x.start()
      self.port = None
      
   def waitForSerialPort(self):
      print ( "Waiting for serial port " )
      while True:
         try:
            self.port = serial.Serial("/dev/rfcomm0", baudrate=9600, timeout=1)
            print ("Successfully connected serial port" ) 
            time.sleep (1)            
            break
         except Exception as ex: 
            print ("Unable to open serial port" )
            time.sleep (1)
            
   def readline (self):       
      line = ''
      try:
         if self.port == None:
            self.waitForSerialPort()
         
         line = self.port.readline()
      # Turn off the bluetooth device to cause this error
      # It is the only way to kill the thread above
      except Exception as ex:
         self.disconnected = True
         print ( "readline exception: " + str(ex) ) 
         # When the rf signal disappears, the serial port will disconnect
         # and a [device disconnected] exception will occurs here
         
      return str(line)
      
if __name__ == '__main__':
    try:
       hc06 = HC06('98:D3:31:20:53:D4')    
       
       count = 0
       while not hc06.disconnected:
          print ( 'readline yo' )
          line = hc06.readline()
          print ( str(count) + ') ' + line )
          count = count + 1
       print ( "Done in main" )  
    finally:
       hc06.close()
     
