import serial
import time
import multiprocessing
import os

class HC06: 
 
   def close(self):
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
      self.failed = False
      print ('Note you must pair with the HC05 (' + macAddress + ' via bluetooth manager before calling this procedure' )   
      self.x = multiprocessing.Process(target=self.bindRfcomm0)
      self.x.start()
      self.port = None
      
   def waitForSerialPort(self):
      print ( "Waiting for serial port " )
      while True:
         try:
            self.port = serial.Serial("/dev/rfcomm0", baudrate=9600)
            print ("Successfully connected serial port" ) 
            time.sleep (1)            
            break
         except Exception as ex: 
            print ("Unable to open serial port" )
            time.sleep (1)
            
   def readline (self):       
      done = False
      line = ''
      try:
         line = self.port.readline()
      # Turn off the bluetooth device to cause this error
      # It is the only way to kill the thread above
      except Exception as ex:
         done = True
         print ( "readline exception: " + str(ex) ) 
         # When the rf signal disappears, the serial port will disconnect
         # and a [device disconnected] exception will occurs here
         
      return (done,line)
      
if __name__ == '__main__':
    hc06 = HC06('98:D3:31:20:53:D4')    
    hc06.waitForSerialPort()
    
    count = 0
    done = False
    while not done:
       print ( 'readline yo' )
       (done,line) = hc06.readline()
       print ( str(count) + ') ' + line )
       count = count + 1
    print ( "Done in main" )  
    hc06.close() # Kill HC06 binding thread  
       
