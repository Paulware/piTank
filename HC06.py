import serial
import time
import multiprocessing
import os
#import pexpect
import subprocess

class HC06: 
 
   def close(self):
      print ("HC06 cleanup and close")
      try: 
         self.port.close()
         #self.x.terminate()
         #self.x.join()
      except Exception as ex:
         print ( "exception: " + str(ex)) 
 
   ''' 
   # Wait for device with macAddress to appear       
   def waitForDevice(self):
      print ( 'Waiting for device: ' + self.macAddress + ' to appear')
      try: 
         out = subprocess.check_output("killall bluetoothctl", shell = True)      
      except Exception as ex:
         print ( "Could not killall bluetoothctl because: " + str(ex)) 
      child = pexpect.spawn('sudo bluetoothctl')
      child.sendline ('scan on')      
      #stopTimeout = time.time() + 20 
      while True:
          try: 
             line = child.readline()
             info = line.split (' ')
             if len(info) > 3: 
                device = info[3]
                if device == self.macAddress:
                   print (self.macAddress + ' has appeared')
                   found = True 
                   break
                else:
                   print (device)         
          except Exception as ex:
             print ("exception: " + str(ex))           
          time.sleep(1)          
      child.sendline ('scan off')           
      child.sendline ('exit')   
   '''
   
   def pythonBind (self):
      host = input()
      port = 1

      cmd = "sudo rfcomm connect /dev/rfcomm0 ' + self.macAddress + ' {} {} &".format(host, port)
      conn = subprocess.Popen(cmd, shell=True)
      if conn.returncode is None:
          print("error in opening connection")   
      
   def bindRfcomm0(self):    
      print ( 'now bind hello' )   
      self.disconnected = False
      print ('Note you must pair with the HC05 (' + self.macAddress + ' via bluetooth manager before calling this procedure' )   
      # self.x = multiprocessing.Process(target=self.bindRfcomm0)
      # self.x.start()
  
      cmd = 'rfcomm connect /dev/rfcomm0 ' + self.macAddress + ' 1 &'
 
      print ( 'Start trying to bind' )
      while True: 
         try: 
            os.system(cmd)
            print ( "Done with os.system cmd")
            print ("We are good...")
            break
         except Exception as ex:
            print ("Got exception: " + str(ex))
      '''
      # keep trying to bind forever, the only way to kill is with self.x.terminate()
      while True:
         print (cmd)
         try:
            os.system (cmd) # 0 considered good 
         except Exception as ex:
            print ( "bindRfcomm0 Got this exception: " + str(ex) + " ignore it") 
            time.sleep (1)
      

      if self.deviceActive(): 
         self.disconnected = False
         print ('Note you must pair with the HC05 (' + macAddress + ' via bluetooth manager before calling this procedure' )   
         # self.pythonBind()
         self.bindRfcomm0()
         # self.x = multiprocessing.Process(target=self.bindRfcomm0)
         # self.x.start()
         self.port = None
      else:
         self.disconnected = True
      '''
      
   def __init__(self, macAddress): 
      print ( 'In init')   
      self.macAddress = macAddress 
      self.disconnected = False  
      self.port = None      
      # self.bindRfcomm0()
      print ( 'Done in init')
      
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
          line = hc06.readline()
          if line != '':
             print ( str(count) + ') ' + line.strip() )
             count = count + 1
          time.sleep (0.1)
       print ( "Done in main" )  
    except Exception as ex:
       print ( "Got exception: " + str(ex)) 
    finally:
       hc06.close()
     
