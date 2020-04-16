#ifndef IR_Tank_h
#define IR_Tank_h
#include "IRTimer.h"

class IRTank : public IRTimer {
public:
  IRTank ( int irrcvpin, int irTransmitPin) : IRTimer (irrcvpin) {
	fireType = 0;
	irTransmit = irTransmitPin;
  }; // constructor

  // Method  
  void init (void);
  void fireAll(void);
  int maxFireTypes (void); 
  
  // Fields
  int shotDetected();  
  int fireType;
  
private:
  int irTransmit;
};
#endif