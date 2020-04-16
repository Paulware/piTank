#ifndef CounterPin_h
#define CounterPin_h

#include <Arduino.h>
class CounterPin {
public:
  CounterPin (int _pin, int _maxCount) {
    pin = _pin;
    pinMode(pin, OUTPUT);
    digitalWrite (pin,1); 
    timeout = millis() + 1000;
    state = 0;
    maxCount = _maxCount;
    currentCount = maxCount;
  }; // constructor
    
  void update (int targetCount) {
    if (targetCount != currentCount) {
      if (millis() > timeout) {
        timeout = millis() + 150;        
        if (state == 0) { 
          digitalWrite (pin,0);
          state = 1;
        } else {
          state = 0;
          digitalWrite (pin,1);
          if (currentCount == 0) {
            currentCount = maxCount;
          } else {
            currentCount = currentCount - 1;
          }            
        }
      }
    }  
  };
   
private:
    int pin;
    int currentCount;
    unsigned long timeout;
    int state;
    int maxCount;
};
#endif