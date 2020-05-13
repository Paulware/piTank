#include <TimerOne.h>
#include <IR.h>
#include <IRTank.h>
#include <Pixel.h>
#include <EEPROM.h>

void(* resetFunc) (void) = 0;//declare reset function at address 0

// Note: IR receiver is not used.
#define IRRECEIVEPIN 17
#define IRTRANSMIT 3

Pixel pixels (8,4,300);
IRTank ir (IRRECEIVEPIN, IRTRANSMIT, &Timer1, false);
unsigned long fireTimeout = 0;
unsigned long irTimeout = 0;
unsigned long waitTime = 15000;
int turnSpeed = 255;

byte health = 0;

void callback() // Timer1 is set to 25 microsecond to balance PWM output
{
  static bool skip = false;
  skip = !skip;
  if (!skip)
    ir.callback(); 
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin (9600);
  Serial.println ( "\nStereoTurret Ready");
    
  health = EEPROM.read(0);
  if ((health > 4) || (health < 0) ) {
     health = 4;
     EEPROM.write (0,4);
  }
  Serial.print ( "My health is: " );
  Serial.println ( health );
  pixels.setHealth (health);

  // Turret left/right
  pinMode (9, OUTPUT); 
  digitalWrite (9, 0);
  pinMode (10, OUTPUT);
  digitalWrite (10, 0);

  // Turret up/down
  pinMode (7,OUTPUT);
  digitalWrite (7,0);

  // Hit indicator
  pinMode (5,OUTPUT); // TODO: Use 4 on next pcb
  digitalWrite (5,0);
  
  ir.init(); 
  Timer1.initialize (25);
  Timer1.attachInterrupt(callback,25); 
  ir.resetIR();   
  
  pixels.setHealth (health);
  // pixels.setPixels(0); // GREEN    
  fireTimeout = 1;

}

void loop() {
  char ch = ' ';
  char chValues[] = {'0','1','2','3'};
  int irDetected;
  static char lastCh = ' ';
  static unsigned long ledTimeout = 0;
  
  if (fireTimeout != 0) {    
      fireTimeout = 0;
      // ir.startSequence();
  }
  if (Serial.available()) {
    ch = Serial.read();
    if (lastCh == '$') {
      Serial.print ( "Process: " );
      Serial.println ( ch );
      if ((ch != 10) && (ch != 13)) { 
        if (ch >= 32) { 
           if (lastCh != ch) {
             Serial.print (ch); 
           } 
        } else {
           Serial.print ( "Got an EEPROM health of: " );
           Serial.println (chValues[ch]);
        }
        
        if ((ch >= 0) && (ch <= 4))  {
           health = ch;
           pixels.setHealth (ch); 
           EEPROM.write (0,health);        
        } else if ((ch >= '0') && (ch <= '4')) {
           health = ch - '0';
           pixels.setHealth (ch - '0');
           EEPROM.write (0,health);
        } else if (ch == 'T') {
           digitalWrite (10,0);
           digitalWrite (9,1);
        } else if (ch == 't') {
           digitalWrite (9,0);
           digitalWrite (10,1);
        } else if (ch == 'U') {
           digitalWrite (9,0);
           digitalWrite (10,0);
        } else if (ch == 'V') {
           digitalWrite (7,1);
        } else if (ch == 'u' ) {
           digitalWrite (7,0);
        } else if ((ch == 'F') || (ch == 'f')) {
           Serial.println ( "Got an f command!" );
           if (ir.fireType == 0) {
              ir.startSequence();
           }
        } else if ((ch == 'h') || (ch == '-') || (ch == 'H')) {
           if (health > 0) { 
              health = health - 1;
           }
           pixels.setHealth (health);
           EEPROM.write (0,health);
           digitalWrite (5,1); // TODO: Change this to pin 4 on new pcb
           ledTimeout = millis() + 1000;
        } else if (ch == '!') {
           health = 4;
           pixels.setHealth (health);
           EEPROM.write (0,health);          
        } else if (ch == '+') {
           if (health < 4) { 
              health = health + 1; 
           }
           pixels.setHealth (health);
           EEPROM.write (0,health);         
        }         
      }      
    }
    lastCh = ch;
  }
  
  if (ir.fireType == 0) {  
    irDetected = ir.decodeBits (15, true, false);  // ir.IRDetected (); 
    if (irDetected == 1) { // Huan Qi
       Serial.println ( "Got a Huan Qi" );
       //led.setColor (RED,500);
       //pixels.minus();
    } else if (irDetected != 0) {
      if (irDetected == 0x15A) { 
        Serial.println ( "MG" );
      } else if (irDetected == 0x1A5) {
        Serial.println ( "Main Gun" );
        digitalWrite (5,1);
        ledTimeout = millis() + 1000;
        if (health > 0) {
           health = health - 1;
           EEPROM.write (0,health);
           pixels.setHealth (health);         
        }      
      } else {
        Serial.print ( "Got a shot value of: " );
        Serial.println ( irDetected, HEX );  
      }
      ir.resetIR();    
      //led.setColor (RED,500);
    }
  }

  ir.update();
  //pixels.update();  

  if (ledTimeout) { 
    if (millis() > ledTimeout) {
      digitalWrite (5,0); // TODO change this to D4, in next pcb
      ledTimeout = 0;
    }
  }
  
}
