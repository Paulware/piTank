#include <SoftwareSerial.h>
#include <TriColorLED.h>
#include <DisplaySerial.h>

TriColorLED led = TriColorLED(15,13,7); 
DisplaySerial displaySerial (20,12); // Arduino Tx Line

void setup() {
  // put your setup code here, to run once:
  Serial.begin (9600);
  Serial.println ( "Enter '!' for red, '?' for blue and '$' for green " );
  Serial.println ( "All other text will be written to the display " );
  Serial.println ( "Use a '^' to clear the display" );  
  displaySerial.printString ( "^This is a 4X20 LCD  " );
  displaySerial.printString (  "Display.  That means" );
  displaySerial.printString (  "you can display 4   " );
  displaySerial.printString (  "lines each 20 chars " ); 
  led.setColor (GREEN);
}

void loop() {
  char ch;
  // put your main code here, to run repeatedly:
  if (Serial.available()) { 
    ch = Serial.read();      
    if (ch == '!' ) {
      led.setColor (RED);
    } else if (ch == '?') {
      led.setColor (BLUE);
    } else if (ch == '$') {
      led.setColor (GREEN);
    } else {
      displaySerial.printChar (ch);
    }
  }
}
