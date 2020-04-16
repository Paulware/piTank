//Includes
#include <IR.h>
#include <IRPipboy.h>
#include <TriColorLED.h>

#define TRIGGERPIN 16
TriColorLED led = TriColorLED(5,4,6); //Green, Blue, Red
// Receive pin not used, transmit pin = 3
IRPipboy irTransmit3(20,3,&Timer1);
unsigned long redTimeout = 0;
void setup () {
  Serial.begin (9600);
  Serial.println ("IR Tx Ready");
  irTransmit3.init();
  pinMode (TRIGGERPIN,INPUT);
  digitalWrite (TRIGGERPIN,1);
  led.setColor (GREEN);
}

void loop  () {
  static int lastTrigger = 1;
  char ch;    
  // put your main code here, to run repeatedly:
  int value = digitalRead (TRIGGERPIN); // trigger

  if (lastTrigger != value) {
     if (value == 0) { 
       irTransmit3.createDataSequence(5);
       irTransmit3.fireShot();  
       led.setColor (RED);
       redTimeout = millis() + 1000;
     }
     lastTrigger = value;
  }  
  if (Serial.available() ) { 
     ch = Serial.read();
     if (ch == ' ') { // Fire when a space is entered.
       irTransmit3.createDataSequence(5);
       irTransmit3.fireShot();     
     }
  }

  if (redTimeout) {
     if (millis() > redTimeout) { 
        led.setColor (GREEN);
        redTimeout = 0; 
     }
  }
}
