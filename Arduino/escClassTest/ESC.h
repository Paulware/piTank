#ifndef ESC_h
#define ESC_h

#include "Servo.h"

class ESC {
public:
  ESC (int _pin) {
    escPin = _pin;
  }; // constructor
  
  // Arm should be run when the ESC is powering up
  void arm() {
    // Arm the ESC
    esc.attach (escPin,loRange,fullThrottle);
    esc.writeMicroseconds (fullThrottle);
    delay (2000); // 2 seconds
    esc.writeMicroseconds (1500); // Neutral
    delay (2000); // 2 seconds
    currentValue = 1500;
    targetValue = 1500;
  }
  
  // update should be called from loop 
  void update () {
     if (millis() > timeout) { 
        timeout = millis() + 100;
        if (currentValue < targetValue) {
           currentValue = targetValue; // Can increase value quickly
        } else if (currentValue > targetValue ) { 
           // Must decrease slowly to avoid automatic brake
           currentValue = currentValue - 4;  
           if ((currentValue >= 1460) && (currentValue <= 1520)) { 
              currentValue = currentValue - 30;
           }  
        } 
        esc.writeMicroseconds (int(currentValue));
        if (lastValue != int(currentValue)) {
          lastValue = int(currentValue);
          Serial.print ( "esc[" );
          Serial.print ( escPin );
          Serial.print ( "]:" );
          Serial.println ( currentValue);
        }       
     }
  } 
  
  void forward () {
     targetValue = MINVALUE;
  } 

  void stop() {
     targetValue = neutral;
  }
  
  void reverse () {
     targetValue = MAXVALUE;
  } 

  // Change these values for a different sound  0
  int targetValue = 0;

private:
  int MINVALUE = 1420;
  int MAXVALUE = 1580;
  int escPin = 0;
  int fullThrottle = 2000;
  int loRange = 1000;
  int neutral = 1500; // For bidirectional ESC
  Servo esc;
  int currentValue = 0;
  unsigned long timeout = 0;
  int lastValue = 0;  
  
};
#endif
