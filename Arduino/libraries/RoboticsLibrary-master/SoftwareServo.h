#ifndef SoftwareServo_h
#define SoftwareServo_h
#include <inttypes.h>
#include "Arduino.h"

class SoftwareServo
{
  private:
    uint8_t pin;
    uint8_t angle;       // in degrees
    uint16_t pulse0;     // pulse width in TCNT0 counts
    uint8_t min16;       // minimum pulse, 16uS units  (default is 34)
    uint8_t max16;       // maximum pulse, 16uS units, 0-4ms range (default is 150)
    class SoftwareServo *next;
    static SoftwareServo* first;
  public:
    SoftwareServo(int _pin);
    uint8_t attach(int);     // attach to a pin, sets pinMode, returns 0 on failure, won't
                             // position the servo until a subsequent write() happens
    void detach();
    void write(int);         // specify the angle in degrees, 0 to 180
    uint8_t read();
    uint8_t attached();
    void setMinimumPulse(uint16_t);  // pulse length for 0 degrees in microseconds, 540uS default
    void setMaximumPulse(uint16_t);  // pulse length for 180 degrees in microseconds, 2400uS default
    static void refresh();    // must be called at least every 50ms or so to keep servo alive
                              // you can call more often, it won't happen more than once every 20ms
                              
    int sweepDirection (int step) {

       static unsigned long timeout = 0; 
       int pos = angle;
       int direction = step;
       
       if (millis() > timeout) { 
          timeout = millis() + 15;
          if (step != 0) {
            pos = pos + step;
            if (pos > 180) {
              pos = 180;
              direction = 0;
            } else if (pos < 0) {
              pos = 0;
              direction = 0;
            }
            write (pos);
            refresh();
          }  
       }
       return direction;
    }; 
    
    int sweep(int _step=1) {
       static int pos = 0;
       static unsigned long timeout = 0;
       static int step; 
       
       if (millis() > timeout) { 
          timeout = millis() + 15;
          if (pos >= 180) {
            step = 0 - _step;
          } else if (pos <= 0) {
            step = _step;
          }
          write (pos);
          refresh();
          pos = pos + step;          
       }
       return pos;
    }; 
};

#endif
