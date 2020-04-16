/*
  Ultrasonic.h - Library for HR-SC04 Ultrasonic Ranging Module.
  Created by ITead studio. Alex, Apr 20, 2010.
  iteadstudio.com
*/


#ifndef Ultrasonic_h
#define Ultrasonic_h
#include <Arduino.h>

class Ultrasonic
{
  public:
    // This class is for a SR-04
    Ultrasonic(int TriggerPin, int EchoPin) {
      Trig_pin=TriggerPin;
      Echo_pin=EchoPin;
      pinMode(Trig_pin,OUTPUT);
      pinMode(Echo_pin,INPUT);
    }

    long Timing() {
      static long duration = 0;
      static unsigned long timeout = 0;
      
      if (millis() > timeout) {
        timeout = millis() + 100; // Only read maximum of 10 times a second
        digitalWrite(Trig_pin, LOW);
        delayMicroseconds(2);
        digitalWrite(Trig_pin, HIGH);
        delayMicroseconds(10);
        digitalWrite(Trig_pin, LOW);
        duration = pulseIn(Echo_pin,HIGH, maxRange);
      }  
      return duration;
    }
        
    bool range(long & inches) {
      static long lastValue = 100;
      long duration = Timing();
      bool valid = false;
      if ((duration > 0) && (duration < maxRange)) { 
         
        inches = (lastValue + duration / 74 / 2) / 2;
        lastValue = duration / 74 / 2;
        valid = true;
      }
      return valid;
    };   

    bool rangeChanged (bool & valid, long & value) {
      static bool wasValid = false;
      static long oldRange = 0;      
      bool changed = false;            
      valid = range ( value );
      changed = (valid != wasValid) || (valid && (value != oldRange));
      
      if (changed) {      
        wasValid = valid;
        oldRange = value;
      }
      
      return changed;
    };
   

  private:
    int Trig_pin;
    int Echo_pin;
    unsigned long maxRange = 5480; // Maximum number of microseconds to wait
};

#endif