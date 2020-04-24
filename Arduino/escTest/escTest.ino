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

void arm(int pin) {
  // Arm the ESC
  esc.attach (pin,1000,2000);
  esc.writeMicroseconds (2000); // Full Throttle
  delay (2000);
  esc.writeMicroseconds (1500); // Neutral
  delay (2000); 
}
void escUpdate (float & currentValue, float targetValue) { 
  if (currentValue < targetValue) {
    currentValue = targetValue; // Can increase value quickly
  } else if (currentValue > targetValue ) { 
    // Must decrease slowly to avoid automatic brake
    currentValue = currentValue - 4;  
    if ((currentValue >= 1460) && (currentValue <= 1520)) { 
      currentValue = currentValue - 30;
    }  
  }    
}

void setup() 
{
  Serial.begin (115200);
  Serial.println ( "Ready");
  arm(5);
  currentValue = 1500;
  targetValue = MAXVALUE;
} 

unsigned long servoTimeout = 0; 
// Enter a + to increase voltage, - to decrease the voltage at motor
void loop() 
{ 
  char ch;
  static int lastValue = 0;
  
  if (millis() > servoTimeout) {
    servoTimeout = millis() + 100;
    escUpdate (currentValue, targetValue);
    
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
