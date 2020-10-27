#include <Servo.h>

/* This example shows how to use an ESC controller that can go
 * forward and backard
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
    servoTimeout = millis() + 100;
    if (currentValue < targetValue) {
      currentValue = currentValue + 5;
    } else if (currentValue > targetValue ) { 
      currentValue = currentValue - 5;    
    }    
    esc.writeMicroseconds (int(currentValue));
    if (lastValue != int(currentValue)) {
       lastValue = int(currentValue);
       // Serial.println ( currentValue);
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
