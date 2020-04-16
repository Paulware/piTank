#include <ButtonPress.h>
#include <TriColorLED.h>
#include "IR.h"
#include "IRPipboy.h"
#include "TimerOne.h"
#include "EEPROM.h"
#include "Piezo.h"

Piezo piezo = Piezo (2);
TriColorLED led = TriColorLED (5,4,6); 
ButtonPress buttonPress = ButtonPress(16); // D16 = A2 
IRPipboy ir (17,3, &Timer1, false); // Receive pin not used
bool checksumBad = true;
void setup() {
  int checkSum=0;
  int hexValue;
  
  // put your setup code here, to run once:
  Serial.begin (9600);
  Serial.println ( "Pipstol Ready" );

  ir.init(); 

  for (int i=0; i<4; i++) {
    ir.fourNibbles[i] = EEPROM.read(i);
    Serial.print ( "Read: " );
    Serial.println ( ir.fourNibbles[i],HEX );
    checkSum = checkSum ^ ir.fourNibbles[i];
    if (ir.fourNibbles[i] != 255) {
      checksumBad = false;
    }
  } 

  if (checksumBad) { 
    Serial.println ( "Check sum has not been saved yet" ); 
    led.setColor (BLUE);
  } else if (checkSum != 0) {
    Serial.print ( "Check sum has a bad sum (error) " );
    Serial.println ( checkSum, HEX );
    led.setColor (RED);
  } else {
    Serial.println ( "CheckSum is good!" );
    hexValue = (ir.fourNibbles[0] * 0x100) + (ir.fourNibbles[1] * 0x10) + ir.fourNibbles[2]; 
    ir.createFireSequence (hexValue);    
    led.setColor (GREEN);
  }   
}

void loop() { 
  static char MAC[] = "abc";
  char ch; 
  int hexValue;
    
  // put your main code here, to run repeatedly:
  if (buttonPress.buttonIsPressed() ) {
    led.setColor (RED, 1000);
    ir.fireShot(checksumBad);
    piezo.fireSound();
  } 
  // Send Serial commands to esp
  if (Serial.available() ) {
    ch = Serial.read();
    if (ch ==10) {
       Serial.print ( "\nConvert this MAC to a hex digit:" );
       Serial.println ( MAC );
       hexValue = ir.MACtoHex(MAC);
       Serial.print ( "Got a hex digit: " );
       Serial.println ( hexValue, HEX );
       ir.createFireSequence (hexValue);
       Serial.println ( "Done creating a fire sequence" );
       ir.showNibbles();
       checksumBad = false;
       for (int i=0; i<4; i++) {
          EEPROM.write(i, ir.fourNibbles[i]);             
       }   
    } else if (ch != 13) {
       MAC [0] = MAC [1];
       MAC [1] = MAC [2];
       MAC [2] = ch;
    }
  }
  
  buttonPress.update();
  led.update();
  piezo.update();
}
