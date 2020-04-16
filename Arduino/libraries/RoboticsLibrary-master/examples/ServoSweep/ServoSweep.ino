#include <SoftwareServo.h> 
SoftwareServo myServo (4);  // create servo object to control a servo
void setup() 
{ 
   Serial.begin (9600);
   Serial.println ( "Ready" );
} 
 
void loop() 
{ 
  char ch;
  static int sweepStep = 1;
  int angle = myServo.sweep(sweepStep);  // Increase this number to go faster
  
  if (Serial.available() ) { 
    ch = Serial.read();
    if (ch == 's') {
      sweepStep = 1 - sweepStep;
    }
  }
} 
