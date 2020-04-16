#ifndef ButtonPress_h
#define ButtonPress_h

#include <Arduino.h>
class ButtonPress {
public:

  // It is assumed that this button has one end connected to ground
  ButtonPress (int _buttonPin) {
    buttonPin = _buttonPin;   
    pinMode (buttonPin,INPUT);
    digitalWrite (buttonPin,1); // PULLUP
    timeout = millis();
  }; // constructor
  
  bool isPressed (void) {
    bool pressed = false;
    if (buttonChanged) { 
      if (buttonPressed) {
        pressed = true;
        buttonChanged = false;
      }
    } 
    return pressed;    
  }
  
  bool isReleased (void) {
    bool released = false;
    if (buttonChanged) { 
      if (!buttonPressed) { 
        released = true;
        buttonChanged = false;
      } 
    }
    return released;
  }
    
  void update (void) {
    int value;
    if (millis() > timeout) { 
      value = digitalRead (buttonPin);
      if (value == 1) { 
        if (buttonPressed) { 
          buttonPressed = false;
          buttonChanged = true;
        }
      } else { // Button is pressed 
        if (!buttonPressed) {
          buttonPressed = true;
          buttonChanged = true;
        }        
      }
      timeout = millis() + 100; // Check every 100 ms for a button press
    }    
  };

  
private:
  int buttonPin;
  bool buttonChanged = false;
  bool buttonPressed = false;
  unsigned long timeout = 0;
};
#endif