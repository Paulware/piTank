#include "ESC.h"
ESC esc0 (5);
ESC esc1 (6);
ESC esc2 (3);
ESC esc3 (9);
ESC esc4 (10);
ESC esc5 (11);

ESC esc[] = {esc0, esc1, esc2, esc3, esc4, esc5};
#define NUMESCS 6
bool ready = false;
void setup() {
  Serial.begin (9600);
  Serial.println ( "Arming ESCs" );
  for (int i=0; i<NUMESCS; i++) { 
    esc[i].arm1();
  }
  delay (2000);
  for (int i=0; i<NUMESCS; i++) {
    esc[i].arm2();
  }
 delay (2000);
 Serial.println ( "Ready" );
 for (int i=0; i<NUMESCS; i++) {
    esc[i].ready = true;
 }
 ready = true; 
}

void readPWMs() {
  int sum;
  int value;
  int analogPins[] = {A0, A1, A2, A3, A4, A5}; 
  static int counts[] = {0,0,0,0,0,0};
  static int index = 0;
  static int lastStates[] = {0,0,0,0,0,0};
  int state;
  
  index = index + 1;
  for (int i=0; i<NUMESCS; i++) { 
     sum = 0;
     value = analogRead (analogPins[i]);
     if (value > 500) { 
        counts [i] = counts[i] + 1;
        //Serial.print ( "value: " );
        //Serial.println ( value );
     } 

     if (index == 10) { 
        if (counts[i] == 10) { 
           state = 1;        
        } else if (counts[i] > 0) { 
           state = 0;
        } else {
           state = -1;
        }
        if (state != lastStates[i]) {
          lastStates[i] = state;
          Serial.print ("esc[" );
          Serial.print (i);
          Serial.print ( "]:" );
          Serial.print ( state );
          Serial.print ( " count: " );
          Serial.println ( counts[i] );
          if (state == 1) { 
            esc[i].forward();
          } else if (state == 0) { 
            esc[i].stop();
          } else {
            esc[i].reverse();
          }          
        }
        counts[i] = 0;        
     }
  }  
  index = index % 10;
}

void loop() {
  char ch;
  if (ready) {
    if (Serial.available()) {
       ch = Serial.read();
       Serial.print (ch);
       
       if (ch == 'L')  { // Left Forward      
          esc[0].forward(); 
       } else if (ch == 'l')  { // Left Reverse   
          esc[0].reverse();
       } else if (ch == 'R')  { // Right Forward
          esc[1].forward();
       } else if (ch == 'r')  { // Right Reverse
          esc[1].reverse();
       } else if (ch == 'S') { // Left stop 
          esc[0].stop();
       } else if (ch == 's') { // Right stop 
          esc[1].stop();
       }
    }

    readPWMs();
    for (int i=0; i<NUMESCS; i++) {
      esc[i].update();
    }
  }
}
