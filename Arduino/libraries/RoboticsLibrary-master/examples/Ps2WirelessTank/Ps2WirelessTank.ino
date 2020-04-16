//Includes
#include <MotorControl.h>

#include <Ps2Wireless.h>
//Instantiations
SingleMotor motor56(5,6);
SingleMotor motor910(9,10);
Ps2Wireless ps2Wireless = Ps2Wireless(false);

void setup () { // --- This runs once ---
  Serial.begin (9600);
  Serial.println ("Ready");
  ps2Wireless.init(8);
}

void loop  () { // --- This runs continually ---
  if (ps2Wireless.newY == "UP"){
    motor56.motorMove("forward","fast");
  }
  if (ps2Wireless.newY == "DOWN"){
    motor56.motorMove("reverse","medium");
  }
  if (ps2Wireless.newY == "RELEASED"){
    motor56.motorMove("forward","stop");
  }
  if (ps2Wireless.newYR == "UP"){
    motor910.motorMove("forward","fast");
  }
  if (ps2Wireless.newYR == "DOWN"){
    motor910.motorMove("reverse","medium");
  }
  if (ps2Wireless.newY == "RELEASED"){
    motor910.motorMove("forward","stop");
  }
  //Updates
  ps2Wireless.update();
}
