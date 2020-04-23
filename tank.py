import HC06
import RPi.GPIO as GPIO
import time
import datetime
now = datetime.datetime.now()
currentTime = now.strftime ( "%H:%M:%S")
f = open ( '/home/pi/piTank/tanky.log', 'w')
f.write ( 'Current Time: ' + currentTime + '\n')
 

print ( "bind to bluetooth joystick")
f.write ( 'bind to bluetooth joystick\n' )
hc06 = HC06.HC06() 

print ('hc 06 has been created...now connect gpio pins')  
GPIO.setmode(GPIO.BCM)
GPIO.setup(6, GPIO.OUT)
leftForward = GPIO.PWM(6, 50)  # channel=12 frequency=50Hz
leftForward.start(0)
GPIO.setup(13, GPIO.OUT)
leftReverse = GPIO.PWM(13, 50)  # channel=12 frequency=50Hz
leftReverse.start(0)
GPIO.setup(19, GPIO.OUT)
rightForward = GPIO.PWM(19, 50)  # channel=12 frequency=50Hz
rightForward.start(0)
GPIO.setup(26, GPIO.OUT)
rightReverse = GPIO.PWM(26, 50)  # channel=12 frequency=50Hz
rightReverse.start(0)
GPIO.setup(5, GPIO.OUT)
leftTurret = GPIO.PWM (5, 50)
leftTurret.start(0)
GPIO.setup(21, GPIO.OUT)
rightTurret = GPIO.PWM (21, 50)
rightTurret.start(0)
GPIO.setup(20, GPIO.OUT)
upDown = GPIO.PWM (20, 50)
upDown.start(0)
GPIO.setup(16,GPIO.OUT)

f.write ( 'Wait for user input\n' )
quitTimeout = time.time() + 5
try:
   lastTime = time.time()
   lastTank = ''
   
   count = 0   
   while not hc06.disconnected:
      
      if time.time() > quitTimeout:
         f.write ( 'user input timeout yo\n' )
         break
   
      time.sleep (0) 
      tank = hc06.readline();

      if tank != lastTank:
         print ( str(count) + ') ' + tank )
         f.write ( str(count) + ') ' + tank + '\n')
         lastTank = tank
         quitTimeout = time.time() + 10
      count = count + 1
      
      
      if tank.find ('L') > -1: 
         #pwm left forward 
         leftReverse.ChangeDutyCycle(0) 
         leftForward.ChangeDutyCycle(100)
      elif tank.find ('l') > -1: 
         #pwm left reverse
         leftForward.ChangeDutyCycle(0)
         leftReverse.ChangeDutyCycle(100)
      else:
         #pwm left off
         leftForward.ChangeDutyCycle(0)
         leftReverse.ChangeDutyCycle(0)

      if tank.find ('R') > -1:
         #pwm right forward
         rightReverse.ChangeDutyCycle(0)
         rightForward.ChangeDutyCycle(100)
      elif tank.find ('r') > -1:   
         #pwm right reverse
         rightForward.ChangeDutyCycle (0)
         rightReverse.ChangeDutyCycle(100)
      else:
         #pwm right off    
         rightForward.ChangeDutyCycle (0)
         rightReverse.ChangeDutyCycle (0)
         
      if tank.find ('T') > -1:
         rightTurret.ChangeDutyCycle (0)
         leftTurret.ChangeDutyCycle (100)
      elif tank.find ('t') > -1:
         leftTurret.ChangeDutyCycle (0)
         rightTurret.ChangeDutyCycle (100)
      else:
         leftTurret.ChangeDutyCycle (0)
         rightTurret.ChangeDutyCycle(0)
       
      if tank.find ('V') > -1:
         upDown.ChangeDutyCycle (100)
      else:
         upDown.ChangeDutyCycle (0)
     
      if tank.find ('F') > -1:
         GPIO.output(16,True)         
      else:
         GPIO.output(16,False)
     
finally: 
   hc06.close()
   f.close ()    
print ( "Done in main" )  
  
GPIO.cleanup()

