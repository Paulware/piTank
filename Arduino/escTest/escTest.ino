#include <Servo.h>

/* This example shows how to use an ESC controller that can go
 * forward and backward
 *   Note: There is goofy code in here, trying to disable the brake feature.
 *         Next version will be tested on an ESC with no-brake
 */

Servo esc;
float targetValue;
float currentValue;
#define MINVALUE 1420
#define MAXVALUE 1580
 
void setup() 
{
  Serial.begin (115200);
  Serial.println ( "Ready");
  // Arm the ESC
  esc.attach (9,1000,2000);
  esc.writeMicroseconds (2000);
  delay (2000);
  esc.writeMicroseconds (1500);
  delay (2000); 
  currentValue = 1500;
  targetValue = MINVALUE;
} 
unsigned long servoTimeout = 0; 
// Enter a + to increase voltage, - to decrease the voltage at motor
void loop() 
{ 
  char ch;
  static int lastValue = 0;
  
  if (millis() > servoTimeout) {

    servoTimeout = millis() + 100; // Faster in the do-nothing range

    if (currentValue < targetValue) {
      currentValue = currentValue + 5;
      currentValue = targetValue;
    } else if (currentValue > targetValue ) { 
      currentValue = currentValue - 4;  
      if ((currentValue >= 1460) && (currentValue <= 1520)) { 
        currentValue = currentValue - 30;
      }  
    }    
    esc.writeMicroseconds (int(currentValue));
    if (lastValue != int(currentValue)) {
       lastValue = int(currentValue);
       Serial.println ( currentValue);
    }
  } 
  
  if (Serial.available() ) {   
     ch = Serial.read();
     if (ch == '+' ) {
        targetValue = MINVALUE;
     } else if (ch == '-') {
        targetValue = MAXVALUE;
     }
  }  
} 