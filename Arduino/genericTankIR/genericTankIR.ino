//  NRF24L01 truck or tank
#include <MemoryFree.h>
#include <EEPROM.h>
#include <TimerOne.h>
#include <IR.h>
#include <IRTank.h>
#include <Pixel.h>

#define FULLSPEED 255
#define PIXELPIN 2
#define IRRECEIVEPIN 17
#define IRTRANSMIT 3

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
IRTank ir (IRRECEIVEPIN, IRTRANSMIT, &Timer1, false);

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
    
  pinMode (5, OUTPUT); 
  analogWrite (5, 0);

  pinMode (6, OUTPUT);
  analogWrite (6, 0);

  pinMode (9, OUTPUT);
  analogWrite (9, 0);

  pinMode (10, OUTPUT);
  analogWrite (10,0); 

  /*
   * D12 Turret Left
   * D11 Turret Right
   *  D7 Turret Up
   *  D8 Turret Down
   *  D4 Fire Relay
   *  D2 Pixel Data
   * D17 IR Receieve
   * D3  IR Transmit
   */
  // Turret, Left/Right
  pinMode (12, OUTPUT);
  digitalWrite (12,0);   
  pinMode (11, OUTPUT);
  digitalWrite (11,0); 
  pinMode (7, OUTPUT);
  digitalWrite (7,0);   
  pinMode (8, OUTPUT);
  digitalWrite (8,0); 
     
  testTimeout = 1; // Not used currently

  speedTimeout = 1;

  initPixelsTimeout = millis() + 5000;


  // Clear serial buffer for 3 seconds
  clearTimeout = millis() + 3000; 
  Serial.print ( "Ignoring: " );
  while (millis() < clearTimeout) {
     if (Serial.available()) {
        ch = Serial.read();
        Serial.print (ch);              
     }
  }
  
  ir.init(); 
  Timer1.initialize (25);
  Timer1.attachInterrupt(callback,25); 
  ir.resetIR();
  
  Serial.println ( "GenericTankIR" );
  health = EEPROM.read(0);
  if ((health > 4) || (health < 0) ) {
     health = 4;
     EEPROM.write (0,4);
  }
  Serial.print ( "My health is: " );
  Serial.println ( health );
  //pixels.setHealth (health);

  fireTimeout = 0;
}

void callback() // Timer1 is set to 25 microsecond to balance PWM output
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
  
  if (Serial.available()) {
     ch = Serial.read();
     Serial.print (ch);
     if (ch == 'L')  { // Left Forward      
        analogWrite (6,0);
        analogWrite (5,FULLSPEED);
     } else if (ch == 'l')  { // Left Reverse   
        analogWrite (5,0);
        analogWrite (6,FULLSPEED);
     } else if (ch == 'R')  { // Right Forward
        analogWrite (10,0);
        analogWrite (9,FULLSPEED);
     } else if (ch == 'r')  { // Right Reverse
        analogWrite (9,0);
        analogWrite (10,FULLSPEED);
     } else if (ch == 'S') { // Left stop 
        analogWrite (6,0);
        analogWrite (5,0);
     } else if (ch == 's') { // Right stop 
        analogWrite (9,0);
        analogWrite (10,0);
     } else if (ch == 'T') { // turret left
        digitalWrite (11,0);
        digitalWrite (12,1);        
     } else if (ch == 't') { // turret right
        digitalWrite (12,0);
        digitalWrite (11,1); 
     } else if (ch == 'V') { // turret up/down
        digitalWrite (7,0);
        digitalWrite (8,1);
     } else if (ch == 'v') { // turret up/down stop 
        digitalWrite (7,0);
        digitalWrite (8,0);
     } else if (ch == 'u') { // turret stop 
        digitalWrite (12,0);
        digitalWrite (11,0);
     } else if ((ch == 'D') || (ch == '!')) { // reset health
        EEPROM.write (0,4);        
     } else if (ch == 'F') { // IR command 
        ir.startSequence();
        ir.fireAll();

        //Timer1.initialize (25);
        Timer1.attachInterrupt(callback,25); 
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
         //pixels.setHealth (health);
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
  // ir.update();
  
}
