#include <TriColorLED.h>
TriColorLED led = TriColorLED(5,4,6); 
void setup() {
  // put your setup code here, to run once:
  led.setColor (GREEN);
  Serial.begin (9600);
  Serial.println ( "Ready LED Set to GREEN" );
}

void loop() {
  static int color = GREEN;
  char ch;
  bool setAll = false;
  // put your main code here, to run repeatedly:
  if (Serial.available()) {
     while (Serial.available()) {
       ch = Serial.read();
       if (ch == '?') {
          setAll = true;
       }
       delay (100);
     }  
     if (setAll) {
       for (int i=2; i<17; i++) {
         pinMode (i,OUTPUT);
         Serial.print ("Set digital output: " );
         Serial.print ( i );
         Serial.println ( " to 0" );
         digitalWrite (i, 0);
         delay (2000);
         digitalWrite (i,1);
       }
     } else {   
       if (color == GREEN) {
         Serial.println ( "Setting color = RED" );
         color = RED;  
       } else if (color == RED) { 
         color = BLUE;
         Serial.println ( "Setting color = BLUE" );
       } else {
         color = GREEN;
         Serial.println ( "Setting color = GREEN" );
       }
       led.setColor (color);
       delay (200);
     } 
  }
}
