#include <TriColorLED.h>
TriColorLED led = TriColorLED (14,4,7); 
void setup() {
  // put your setup code here, to run once:
  Serial.begin (9600);
  Serial.println ( "Ready" );
  led.setColor (GREEN);
}

void loop() {  
  char ch;
  if (Serial.available() ) {
     ch = Serial.read();
     if (ch == 'r') { 
        led.setColor (RED);     
     } else if (ch == 'g') { 
        led.setColor (GREEN);           
     } else if (ch == 'b') { 
        led.setColor (BLUE);           
     }
  }
}
