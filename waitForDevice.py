import HC06
import RPi.GPIO as GPIO
import time

print ( "Wait for bluetooth joystick")

hc06 = HC06.HC06('98:D3:31:20:53:D4')  
hc06.waitForDevice()
print ( 'Done in waitfor device' )

