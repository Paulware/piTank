#include <MotorControl.h>
MotorControl motorControl (5,6,9,10);
unsigned long timeout = 0;
void setup() {
  Serial.begin (9600);
  Serial.println ("Motor Control Check");
  timeout = 1;
}

int state = 0;
void loop() {
  if (millis() > timeout ) {
    timeout = millis() + 4000;
    switch (state) {
      case 0:
        Serial.println ( "Go Forward" );
        motorControl.goForward(250);
      break;
      case 1:
        Serial.println ( "Go Reverse" );
        motorControl.goReverse(250);
      break;
      case 2:
        Serial.println ( "Go Left (half-speed)" );
        motorControl.goLeft(100);
      break;
      case 3:
        Serial.println ( "Go Right (half-speed)" );
        motorControl.goRight(100);
      break;      
    }
    state = state + 1;
    state = state % 4;    
  }
}
