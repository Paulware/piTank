//Includes
#include <IR.h>
#include <IRPipboy.h>

// Receive pin not used, transmit pin = 3
IRPipboy irTransmit3(20,3,&Timer1);

void setup () {
  Serial.begin (9600);
  Serial.println ("IR Tx Ready");
  irTransmit3.init();
}

void loop  () {
  char ch;
  if (Serial.available() ) { 
     ch = Serial.read();
     if (ch == ' ') { // Fire when a space is entered.
       irTransmit3.createDataSequence(5);
       irTransmit3.fireShot();     
     }
  }
}
