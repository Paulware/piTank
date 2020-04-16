#ifndef IR_Tank_h
#define IR_Tank_h
#include "IR.h"
#include <TimerOne.h>

class IRTank : public IR {
public:
  // repairRobotValue is set true if the unit is a repair robot
  IRTank ( int irrcvpin, int irTransmitPin, TimerOne * timer1, bool repairRobotValue) : IR (irrcvpin) {
    Timer1 = timer1;
	   fireType = 0;
	   irTransmit = irTransmitPin;
	   repairRobot = repairRobotValue;
  }; // constructor

  // Methods 
  void init (void);
  void fireAll(void);
  void sendFirePulse(void);
  void space(int time);
  void sendRaw(unsigned int uDelay, int index);  
  void enableIROut() ;
  void fire(void) 
  {
    fireType = maxFireTypes();
	   fireTimeout = 1; // Start firing pulses
  }
  int IRDetected();  
  void startSequence(void);
  void update(void);
  void fireYo (void);
  // Fields
  int fireType;
  
private:
   #define NEWHUAN 18
   //                                    1                      A                                           5
   uint16_t newHuanQiPulses[NEWHUAN] = {2000, 500, 1100, 1000, 450, 500, 1100, 1000, 450,  1000, 450, 500, 1000, 1000, 450, 500, 1000, 300};
   #define HUANPULSES 8
   uint16_t huanQiPulses[HUANPULSES] = {12500, 600, 2150, 600, 700, 1950, 600, 8500};
   #define FOVPULSES 17   
   uint16_t FOVPulses[FOVPULSES] = {8250,1500,1600,1500,3200,1450,1600,1500,
                        3150,1500,1600,1550,1550,1500,1600,1500,1550};
   #define DANBARPULSES 19
   uint16_t DanbarPulses[DANBARPULSES] = {500, 250, 1550, 250, 900, 250, 900, 250, 500, 250,
                           500, 250,  500, 250, 500, 250, 900, 250, 500};
   #define AIRBENDERPULSES 10                                                  
   uint16_t airBenderPulses [AIRBENDERPULSES] = {16284,2168,1132,1096,2244,2180,1132,1096,2236,21788};
   #define BATTLEMACHINEPULSES 18
   uint16_t battleMachinePulses [BATTLEMACHINEPULSES] = {3050,300,300,950,300,950,300,300,300,350,300,1000,300,950,300,350,300,10500};
   #define MINITANK 12
   uint16_t miniTankPulses [MINITANK] = {23716,2488,8504,2540,2632,2496,8540,2540,2580,2696,8524,61604};
   #define REPAIRPULSES 16
   uint16_t repairPulses [REPAIRPULSES] = {500, 300, 500, 300, 500, 300, 1000, 300, 1000, 300, 1000, 300, 500, 300, 500, 300 };
   #define MICROHUANQI 10   
   uint16_t microHuanQi [MICROHUANQI] = {12840,644,2044,644,672,2016,672,2020,672,2020};


  TimerOne * Timer1;
  int maxFireTypes (void); 
  int irTransmit;
  unsigned long fireTimeout;
  bool repairRobot;
};
#endif