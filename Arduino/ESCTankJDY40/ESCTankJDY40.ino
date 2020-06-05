#include <MemoryFree.h>
#include <MatchStrings.h>
#include <EEPROM.h>
#include "ESC.h"
#define FULLSPEED 255

ESC leftTread (5);
ESC rightTread (6);

int mainGunCount = 0;

char testCharacters [] = {'-','-','-','-','+','+','+','+'};
int testIndex = 0;
unsigned long testTimeout = 0;
unsigned long offTimeout = 0;
unsigned long speedTimeout = 0;
unsigned long fireTimeout = 0;
int turnPower = 50;
int timeoutTime = 900;

byte health = 0;
unsigned long initPixelsTimeout = 0;
int state = 0;
bool ready = false;

void(* resetFunc) (void) = 0;

MatchStrings matchStrings;

void setup() {
  unsigned long clearTimeout;
  char ch;
  

  // Turret setup pins
  pinMode (9, OUTPUT);
  digitalWrite (9, 0);
  pinMode (10, OUTPUT);
  digitalWrite (10,0); 
  pinMode (7, OUTPUT);
  digitalWrite (7,0);

  leftTread.attach();
  rightTread.attach();
  /*
  leftTread.arm1();
  rightTread.arm1();
  delay (1000);
  leftTread.arm2();
  rightTread.arm2();
  
  delay (1000);
 */
  
  rightTread.ready = true;
  leftTread.ready = true;     

  Serial.begin (9600);// Must be 9600 because receiver is same
  Serial.println ( "ESCTankJDY40" );
  Serial.println ( "Waiting for SsUu" );

  matchStrings.addString ( "SsUu" );
}

void loop() {
  char ch;
  // static char lastCh = ' ';
  static bool fire = false;
  int match;

  ch = ' ';
  if (Serial.available()) {
     ch = Serial.read();
     Serial.print (ch);
     if (!ready) {
        match = matchStrings.findMatch (ch);
        if (match > -1) { 
           ready = true;    
        }
     }
  }

  if (ready) {  
     if (ch == 'L')  { // Left Forward      
        leftTread.forward(); 
        Serial.println ( "Left Tread Forward" );
     } else if (ch == 'l')  { // Left Reverse   
        leftTread.reverse();
     } else if (ch == 'R')  { // Right Forward
        Serial.println ( "Right Forward" );
        rightTread.forward();
     } else if (ch == 'r')  { // Right Reverse
        rightTread.reverse();
        Serial.println ( "Right reverse" );
     } else if (ch == 'S') { // Left stop 
        leftTread.stop();               
     } else if (ch == 's') { // Right stop 
        rightTread.stop();
     } else if (ch == 'T') { // turret left
        digitalWrite (9,0);
        digitalWrite (10,1);        
     } else if (ch == 't') { // turret right
        digitalWrite (10,0);
        digitalWrite (9,1); 
     } else if (ch == 'V') { // turret up/down
        digitalWrite (7,1);
     } else if (ch == 'u') { // turret up/down stop 
        digitalWrite (7,0);
     } else if (ch == 'U') { // turret stop 
        digitalWrite (9,0);
        digitalWrite (10,0);
     } else if ((ch == 'D') || (ch == '!')) { // reset health
        EEPROM.write (0,4);        
     } else if (ch == 'F') { // IR command 
        // resetFunc(); // Necessary?
     } else if (ch == 'f') {
        fire = false;
     }    
  }

  leftTread.update();
  rightTread.update();
}
