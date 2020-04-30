#include "Esp32Servo.h"

// Note 
//    Tools->Board->Esp32-Wrover-Module
//    Tools->Partition Scheme -> Huge APP
static const int servoPin = 16;

Servo servo1;

void setup() {
    Serial.begin(9600);
    Serial.println ( "Ready" );
    servo1.attach(servoPin);
}

void loop() {
   static int posDegrees = 0;
   char ch;
    
   if (Serial.available() ) {
      ch = Serial.read();
      Serial.print (ch); 
      if (ch == 'L') {
         if (posDegrees < 180) { 
            posDegrees = posDegrees + 10;
            servo1.write(posDegrees);            
         }        
      } else if (ch == 'l') { 
         if (posDegrees > 0) { 
            posDegrees = posDegrees - 10;
            servo1.write(posDegrees);            
         }
      }    
   }
}
