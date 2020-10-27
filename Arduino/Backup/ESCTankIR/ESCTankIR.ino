#include <MemoryFree.h>
#include <EEPROM.h>
#include <TimerTwo.h>
#include <IR.h>
#include <IRTank.h>
#include <Pixel.h>
#include "ESC.h"

#define FULLSPEED 255
#define PIXELPIN 2
#define IRRECEIVEPIN 17
#define IRTRANSMIT 3


ESC leftTread (5);
ESC rightTread (6);

int mainGunCount = 0;

Pixel pixels (PIXELPIN,4,300);
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
IRTank ir (IRRECEIVEPIN, IRTRANSMIT, &Timer2, false);
bool ready = false;

void setup() {
  unsigned long clearTimeout;
  char ch;
  health = EEPROM.read(0);
  if (true) { // (health > 4) || (health < 0) ) {
     health = 4;
     EEPROM.write (0,4);
  }
  
  Serial.begin (9600);// Must be 9600 because receiver is same

  Serial.print ( "Got an EEPROM health of: " );
  Serial.println ( health );


  pinMode (9, OUTPUT);
  digitalWrite (9, 0);

  pinMode (10, OUTPUT);
  digitalWrite (10,0); 
 
  pinMode (7, OUTPUT);
  digitalWrite (7,0);
  
  Serial.println ( "Arming ESCs" );
  leftTread.arm1();
  rightTread.arm1();
  delay (2000);
  leftTread.arm2();
  rightTread.arm2();
  delay (2000);
  rightTread.ready = true;
  leftTread.ready = true;     
  testTimeout = 1; // Not used currently

  speedTimeout = 1;

  initPixelsTimeout = millis() + 5000;

   
  ir.init(); 
  Timer2.initialize (25);
  Timer2.attachInterrupt(callback,25); 
  ir.resetIR();
 
  
  Serial.println ( "GenericTankIR" );
  health = EEPROM.read(0);
  if ((health > 4) || (health < 0) ) {
     health = 4;
     EEPROM.write (0,4);
  }
  Serial.print ( "My health is: " );
  Serial.println ( health );
  pixels.setHealth (health);

  fireTimeout = 0;
  ready = true;

}

void callback() // Timer2 is set to 25 microsecond to balance PWM output
{
  static bool skip = false;
  skip = !skip;
  if (!skip)
    ir.callback(); 
}

/*
 * TODO: Add run-away check
 */
void loop() {
  char ch;
  //int irDetected;  
  static char lastCh = ' ';
  static bool fire = false;
  int irDetected;

  /*
  if (fireTimeout != 0) {
      fireTimeout = 0;
      ir.startSequence();      
  }
  */

  if (ready) 
  
  if (Serial.available()) {
     ch = Serial.read();
     Serial.print (ch);
     if (ch == 'L')  { // Left Forward      
        leftTread.forward(); 
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
        ir.startSequence();
        ir.fireAll();

        Timer2.initialize (25);
        Timer2.attachInterrupt(callback,25); 
        ir.resetIR();        
     } else if (ch == 'f') {
        fire = false;
     }
  }

  //if (mainGunCount < 100) { 
  /*
  if (ir.fireType != 0) {
    Serial.print ( "ir.fireType: " );
    Serial.println ( ir.fireType );    
    ir.update();
  } else {   
  */
    irDetected = ir.decodeBits (15, true, false);  // ir.IRDetected ();
    if (irDetected == 0x1A5) {
      Serial.println ( "Main Gun" );
      if (health > 0) {
         health = health - 1;
         pixels.setHealth (health);
         Serial.print ("health");
         Serial.println ( health );         
      }
    }     
    if (irDetected != 0) {  
       Serial.print ( "irDetected:" );
       Serial.println ( irDetected );
       ir.resetIR();    
    }
  //}
      /* 
      if (irDetected == 1) { // Huan Qi
         Serial.println ( "Got a Huan Qi" );
         mainGunCount = mainGunCount + 1;
         //led.setColor (RED,500);
         //pixels.minus();
      } else if (irDetected != 0) {
        if (irDetected == 0x15A) { 
          Serial.println ( "MG" );
        } else if (irDetected == 0x1A5) {
          Serial.println ( "Main Gun" );
          if (health > 0) {
             health = health - 1;
             EEPROM.write (0,health);
             pixels.setHealth (health);
             Serial.print ("health");
             Serial.println ( health );         
          }      
        } else {
          Serial.print ( "Got a shot value of: " );
          Serial.println ( irDetected, HEX );  
        }
        
        //led.setColor (RED,500);
      }
    }
  //}
  ir.update();
  //pixels.update(); 
  */
  //ir.update();
  leftTread.update();
  rightTread.update();
}
