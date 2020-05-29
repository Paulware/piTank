import LCD_1in44
import LCD_Config

from PIL import Image
from PIL import ImageDraw
from PIL import ImageFont
from PIL import ImageColor
import RPi.GPIO as GPIO
import time
import HC06
from socket import *

def checkKey (pin,msg, LCD):
   if GPIO.input(pin) == 0:
      showText (msg,LCD)
      print (msg)
      while GPIO.input(pin) == 0:         
         time.sleep (0.01)
 
def showText (msg,LCD):
   image = Image.new("RGB", (LCD.width, LCD.height), "WHITE")
   draw = ImageDraw.Draw(image)
   print ("***draw text")
   draw.text((33, 22), msg, fill = "BLUE")
   
def sendMsg (message): 
   try: 
      port = 3333
      sock = socket(AF_INET, SOCK_DGRAM)
      sock.bind (('',0)) # bind to any old port 
      sock.setsockopt (SOL_SOCKET, SO_BROADCAST, 1)
      sock.sendto(message, ('192.168.4.255', port)) # broadcast to all devices listening on port 3333
      # print 'Sent ' + message + ' to 192.168.4.1:' + str(port) + '\n'         
   except Exception as inst:
      print (str(inst))   
            
def main():

   hc06 = HC06.HC06() 
   
   # pin numbers are interpreted as BCM pin numbers.13
   GPIO.setmode(GPIO.BCM)
   pinList = [(6,"Up"), (19, "Down"), (5,"Left"), (26,"Right"),
               (21,"Top"), (20,"Middle"), (16,"Downer"), (13, "Press")]
   # Sets the pin as input and sets Pull-up mode for the pin.
   for pin in pinList:
      GPIO.setup (pin[0],GPIO.IN, GPIO.PUD_UP)
     
   LCD = LCD_1in44.LCD()
   
   print ("**********Init LCD**********")
   Lcd_ScanDir = LCD_1in44.SCAN_DIR_DFT  #SCAN_DIR_DFT = D2U_L2R
   LCD.LCD_Init(Lcd_ScanDir)
   
   image = Image.new("RGB", (LCD.width, LCD.height), "WHITE")
   draw = ImageDraw.Draw(image)
   #font = ImageFont.truetype('/usr/share/fonts/truetype/freefont/FreeMonoBold.ttf', 16)
   print ("***draw line")
   draw.line([(0,0),(127,0)], fill = "BLUE",width = 5)
   draw.line([(127,0),(127,127)], fill = "BLUE",width = 5)
   draw.line([(127,127),(0,127)], fill = "BLUE",width = 5)
   draw.line([(0,127),(0,0)], fill = "BLUE",width = 5)
   print ("***draw rectangle")
   draw.rectangle([(18,10),(110,20)],fill = "RED")
   
   print ("***draw text")
   draw.text((33, 22), 'WaveShare ', fill = "BLUE")
   draw.text((32, 36), 'Electronic ', fill = "BLUE")
   draw.text((28, 48), '1.44inch LCD ', fill = "BLUE")

   LCD.LCD_ShowImage(image,0,0)
   LCD_Config.Driver_Delay_ms(500)
      
   buttonTimeout = time.time()
   
   lastCommand = ""
   while True:
       if time.time() > buttonTimeout: 
          buttonTimeout = time.time() + 0.2
          #if buttons.checkKey ("Start"):
          #   break                   
          #if buttons.checkKey ("Select"):
          #   time.sleep (2)  
          command = ""
          fire = ""
          turret = 'u'
          upDown = "v"
          if GPIO.input(21) == 0: # Top
             image = Image.open('leftArrow.jpg')
             LCD.LCD_ShowImage(image,0,0)
             turret = 'T'
             command = "turretLeft"
          elif GPIO.input(20) == 0: # Middle
             image = Image.open('rightArrow.jpg')
             LCD.LCD_ShowImage(image,0,0)
             command = "turretRight"
             turret = 't'
          elif GPIO.input(16) == 0: # bottom button
             image = Image.open('rick.bmp')
             LCD.LCD_ShowImage(image,0,0)               
             upDown = 'V'
          elif GPIO.input(26) == 0: # right button
             leftTrack = 'L'
             rightTrack = 'r'
             command = "right"
             image = Image.open('rightArrow.jpg')
             LCD.LCD_ShowImage(image,0,0)
          elif GPIO.input(5) == 0: # left
             image = Image.open('leftArrow.jpg')
             LCD.LCD_ShowImage(image,0,0)
             command = "left"
             leftTrack = 'l'
             rightTrack = 'R'
          elif GPIO.input(6) == 0: # up button
             image = Image.open('upArrow.jpg')
             LCD.LCD_ShowImage(image,0,0)
             command = "forward"
             leftTrack = 'L'
             rightTrack = 'R'
          elif GPIO.input(19) == 0: # down button 
             image = Image.open('downArrow.jpg')
             LCD.LCD_ShowImage(image,0,0) 
             command = "reverse"
             leftTrack = 'l'
             rightTrack = 'r'
          elif GPIO.input(13) == 0: # press joystick
             fire = 'F'
             command = "fire"
             image = Image.open('tankFire.jpg')
             LCD.LCD_ShowImage(image,0,0)              
             time.sleep (0.5)          
          else:
             command = ""
             leftTrack = 'S'
             rightTrack = 's'
             fire = ''
             upDown = 'v'
          msg = leftTrack + rightTrack + fire + turret + upDown
          hc06.writeline (msg)
          # sendMsg (hc06,msg)
          if (command != lastCommand):
             if command == "":
                image = Image.open('stop.jpg')
                LCD.LCD_ShowImage(image,0,0)              
             lastCommand = command 

	
if __name__ == '__main__':
    main()

#except:
#	print("except")
#	GPIO.cleanup()