#ifndef ESC_h
#define ESC_h

#include "Servo.h"

class ESC {
public:
  ESC (int _pin) {
    escPin = _pin;
    ready = false;
    timeout = 0;
  }; // constructor

  void command (int value) {
    currentValue = value;
    esc.writeMicroseconds (currentValue);    
  }

  void attach() { 
    esc.attach (escPin,1000,2000);        
  }

  void arm1() {
    attach();
    command (fullThrottle);    
  }

  void arm2() {
    command (neutral); // Neutral    
  }

  // update should be called from loop 
  void update () {
     if (ready) { 
       if (millis() > timeout) { 
          timeout = millis() + 100;
          esc.writeMicroseconds (int(currentValue));
       }
     }
  }   
  
  // Arm should be run when the ESC is powering up
  void arm() {
    // Arm the ESC
    arm1();
    delay (2000); // 2 seconds
    arm2();
    delay (2000); // 2 seconds
    ready = true;
  }
  
  void forward () {
     command (MINVALUE);
  } 

  void stop() {
     command (neutral);
  }
  
  void reverse () {
     command (MAXVALUE);
  } 

  // Change these values for a different sound  0
  int currentValue = 1500;
  unsigned long timeout = 0;
  bool ready = false;

private:
  int MINVALUE = 1300;  // TODO store these values in EEPROM
  int MAXVALUE = 1650;
  int escPin;
  int fullThrottle = 2000;
  int neutral = 1500; // For bidirectional ESC
  Servo esc;
};
#endif
