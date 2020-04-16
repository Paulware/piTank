#include <SoftwareServo.h>
SoftwareServo myServo (4);
void setup() {
  // put your setup code here, to run once:
  Serial.begin (9600);
}

void loop() {
  static int servoStep = 1;
  int angle;
  char ch;

  angle = myServo.sweep (servoStep);
  if (Serial.available() ) {
    ch = Serial.read();
    if (ch == 13) { 
       servoStep = 1 - servoStep;   
    }
    if (servoStep == 0) {
       Serial.print ( "Stop at angle: " );
       Serial.println ( angle );
    }
  }  
}
