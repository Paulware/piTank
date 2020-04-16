#ifndef Timer_h
#define Timer_h

class Timer {
public:
  Timer (unsigned long timeout) {
     timerLength = timeout;
  }; // constructor
  
  void setPeriod (unsigned long timeout) {
     timerLength = timeout;
  }
  
  void start() {
     endTime = millis() + timerLength;
     timeLeft = timerLength;
     printTimeout = millis() + 1000;
  }
  
  boolean expired () {
    boolean elapse = false;
    unsigned long timeRemaining = (endTime - millis ());
    if (endTime != -1) {
      if (millis ()  > endTime) { 
         Serial.println ( "Timer has expired" );
         elapse = true;
         endTime = -1;
      } else { 
         if (millis() > printTimeout ) {
           Serial.print (((endTime - millis() ) / 1000) + 1 );
           Serial.println ( " seconds remaining." );
           printTimeout = printTimeout + 1000;
         }  
         timeLeft = timeRemaining;
      }
    }
    return elapse;    
  }
  
  void reset () {
    endTime = -1;
  }
  
private:
  unsigned long timerLength = -1;
  unsigned long endTime = -1;
  unsigned long timeLeft = 0;
  unsigned long printTimeout = 0;
};
#endif