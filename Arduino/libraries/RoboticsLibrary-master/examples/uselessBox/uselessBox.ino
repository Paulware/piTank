#include <SoftwareServo.h>
SoftwareServo myServo (4);
unsigned long timeout = 0;
void setup() {
  // put your setup code here, to run once:
  Serial.begin (9600);
  Serial.println ( "Ready" );
  timeout = 1;
  pinMode (3,OUTPUT);
  digitalWrite (3,0); // GND
  pinMode (2,INPUT_PULLUP);
}



void loop() {
  static int angle = 50;
  static int last2 = 0;
  char ch;

  if (timeout) {
    if (millis() > timeout) {
       myServo.write (50); // Failure retract anyway 
       timeout = 0;
    }
  }  

  if (digitalRead (2) == 0) {
    last2 = 0;
    angle = 5;
    timeout = millis() + 3000;
    myServo.write (angle);
  }

  // Check for switch being thrown back 
  if ((digitalRead (2) == 1) && (last2 == 0)) {   
     timeout = 0;
     angle = 50;
     myServo.write (angle);    
  }

  if (Serial.available() ) {
    ch = Serial.read();
    if (ch == 13) { 
       myServo.write (angle); 
       Serial.println ( angle );
       if (angle == 50) {
          angle = 180;
       } else {
          angle = 50;
       }
    }
  }  
  myServo.refresh();
}
