#include <EEPROM.h>
#include <SoftwareSerial.h>
#include <IR.h>
#include <IRPipboy.h>
#include <TimerOne.h>
#include <TriColorLED.h>
#include <MotorControl.h>
#include <DisplaySerial.h>
#include <SoftwareServo.h>
#include <Ultrasonic.h>
#include <Piezo.h>

#define HTIMEOUT 200
#define BUMPPIN 11
#define IRRECEIVEPIN 17
#define IRTRANSMITPIN 3
// 3 Second freeze time after getting shot
#define FREEZETIME 3000

int speed = 255;
IRPipboy ir (IRRECEIVEPIN, IRTRANSMITPIN, &Timer1, false);
TriColorLED led = TriColorLED(15,13,7); 
SoftwareSerial espSerial (14, 8); // RX, TX
DisplaySerial displaySerial (12, 16); // NotConnected, Transmit pin to Display Rx
MotorControl motorControl (5,6,9,10);
SoftwareServo myServo (4);
Ultrasonic ultrasonic (18,19);
Piezo piezo (2,4000);

boolean died = false;
boolean initialized = false;
boolean checksumBad = true;
unsigned long fireTimeout = 0;
unsigned long blueTimeout = 0;
unsigned long servoTimeout = 0;

void callback() // Timer1 is set to 25 microsecond to balance PWM output
{
  static bool skip = false;
  skip = !skip;
  if (!skip)
    ir.callback();
}

void setup()
{
  int checkSum=0;
  int hexValue;

  Serial.begin(9600); 
  Serial.println ("Sumobot V1.2 (sumoESPIRRxTx) ");

  espSerial.begin (9600);
  //delay (1000);
  //espSerial.println ( "\nLOGIN (\"RichardsWiFi\", \"Star123!\")\n" );
  
  motorControl.clearPins();

  ir.init(); 
  Timer1.initialize (25);
  Timer1.attachInterrupt(callback,25);  

  pinMode (BUMPPIN,INPUT_PULLUP); // Trigger

  checksumBad = false;
  ir.createFireSequence (0xbad);    
   
  if (died) {
    led.setColor (RED);    
  } else {
    led.setColor (GREEN);    
  } 
  // Send the startup message to the LCD display
  delay (1000); // So display can initialize
  displaySerial.printString ( "Enter 20 characters ");
  displaySerial.printString (  "Per Line Thanks!!!  " );
  displaySerial.printString (  "Four lines  maximum " );
  displaySerial.printString (  "Have a good day !!!!");

  motorControl.goForward();
  delay (150);
  motorControl.goReverse();
  delay (150);
  motorControl.clearPins();
}


void loop()
{
  char ch; 
  unsigned int irValue;
  unsigned int hexValue;
  static boolean gotMAC = false;
  static char MAC[] = "abc";
  static int lastTrigger = 1;
  int trigger = digitalRead (BUMPPIN);
  static bool readSlider = false;
  int outValue;
  static int servoStep = 1;
  int angle;
  bool valid;
  long inches;
  int speed;

  piezo.update();
  
  if (servoStep != 0) {
    angle = myServo.sweep(servoStep);  // Increase this number to go faster
  }

  if (ultrasonic.rangeChanged (valid, inches) ) {
    if (valid) {
      if ((inches < 3) && (servoTimeout == 0)) {
        servoStep = 0;
        led.setColor (RED);
        Serial.print ( "Ultrasonic: " );
        Serial.println ( inches );
        servoTimeout = millis() + 3000;
        displaySerial.printString ( "^Object detected!    " );
        if (angle > 90) {
          displaySerial.printString ( "On the Left side!" ); 
        } else {
          displaySerial.printString ( "On the Right side!" );
        }
      }
    }
  }

  led.update();
   
  // Send Serial commands to esp
  if (Serial.available() ) {
    ch = Serial.read();
    if (ch == '!') {                                           
      ir.fireData();
      fireTimeout = 1;
    } else {
      espSerial.print (ch);
    }  
  }
  
  if (espSerial.available() ) {
    ch = espSerial.read();
    Serial.print (ch);
    switch (ch ) {
      case 'f': // Flash lights
        led.policeLights();
        break;
      
      case 'k': // fire
        //ir.fire();
        ir.fireData();
        fireTimeout = 1;
        piezo.fireSound();     
        break;  
        
      case 0:
      case '0': 
        motorControl.clearPins();
        break;
      case 'w':
        led.setColor (GREEN);
        motorControl.goForward();
        break;
      case 'd':
        led.setColor (GREEN);
        motorControl.goReverse();
        break;
      case 'q':
        led.setColor (GREEN);
        motorControl.goLeft();
        break;
      case 'e':
        led.setColor (GREEN);
        motorControl.goRight();        
        break;             
      case 's': // Toggle the Sweep
        servoStep = 1 - servoStep;
        break;
      // Ignore CR and LF
      case 13:
      case 10:
        break;
        
      default:
        break;
     
    }      
  }

  irValue = ir.IRDetected(); 
  if (irValue != 0) { 
    if ((irValue > 'A') && (irValue <= ('A' + 13))) {
      Serial.print ( "Move backward: " );
      Serial.println ( irValue - 'A');
      speed = (irValue - 'A') * 20;
      motorControl.goReverse (speed);
    } else if ((irValue > '0') && (irValue <= ('0' + 13))) {
      Serial.print ( "Move forward: " );
      Serial.println ( irValue - '0');
      speed = (irValue - '0') * 20;
      motorControl.goForward (speed);
    } else if ((irValue > 'O') && (irValue <= ('O' + 13))) {
      Serial.print ( "Move left: " );
      Serial.println ( irValue - 'O');
      speed = (irValue - 'O') * 20;
      motorControl.goLeft (speed);
      myServo.write (0);
      servoStep = 0;
    } else if ((irValue > ' ') && (irValue <= (' ' + 13))) {
      Serial.print ( "Move right: " );
      Serial.println ( irValue - ' ' );      
      speed = (irValue - ' ') * 20;
      motorControl.goRight (speed);
      myServo.write (180);
      servoStep = 0;
    } else if (irValue == ' ') { 
      Serial.println ( "Stop" );
      motorControl.clearPins();
    } else {  
      Serial.print ( "irValue: " );
      Serial.println ( irValue, HEX );
      espSerial.print ( "sendMsg(\"ouch:" );
      espSerial.print ( ir.intToHex(( irValue & 0xF00) / 0x100) );
      espSerial.print ( ir.intToHex(( irValue & 0xF0) / 0x10));
      espSerial.print ( ir.intToHex(irValue & 0xF));
      espSerial.println ( "\")" );

      displaySerial.printString ( "^I have been shot!");
        
      blueTimeout = millis()+ FREEZETIME; 
      led.policeLights(3000);
      piezo.hitSound(); 
    }  
  }     

  if (blueTimeout) { 
    if (millis() > blueTimeout) {
      blueTimeout = 0;
      if (died) {
        led.setColor (RED);    
      } else {
        led.setColor (GREEN);    
      }
    }
  }

  // Check if I am firing the weapon.
  if (fireTimeout) {
    if (millis() > fireTimeout) {   
        fireTimeout = 0;
        Serial.println ( "Done" );
        led.setColor (GREEN);    
    }
  }    
  
  if (servoTimeout) {
    if (millis() > servoTimeout) {
      servoStep = 1;
      displaySerial.printString ( "^Scanning...." );
      led.setColor (GREEN);
      servoTimeout = 0;
    }
  }
  
  myServo.refresh();
}

