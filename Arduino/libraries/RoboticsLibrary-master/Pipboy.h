#ifndef Pipboy_h
#define Pipboy_h


#include <Utilities.h>
#include <EEPROM.h>
#include <IRTX.h>
#include <MatchStream.h>

class Pipboy {
public: 
  IRTX * irTx; 
  MatchStream * matchStream;
  bool checksumGood = false;
  Pipboy (IRTX * irTxPtr, MatchStream * matchStreamPtr) {
     irTx = irTxPtr;
     matchStream = matchStreamPtr;
  } 
  
  void setup() {
     createFirePulse();
     if (checksumGood) {
        Serial.println ( F("Checksum OK!") );
     } else {
        Serial.print ( F("Checksum NOT ok, call showMAC()") );
     }
     matchStream->write ("\n\r"); // Restart esp8266
  }
  
  bool checkSumOk() {
     int checkSum = 0;
     
     Serial.println ( F("Read fire pulse values from EEPROM") );
     for (int i=0; i<4; i++) {
        irTx->fourNibbles[i] = EEPROM.read(i);
        Serial.print ( F("Read: ") );
        Serial.println ( irTx->fourNibbles[i], HEX );
        checkSum = checkSum ^ irTx->fourNibbles[i];
        if (irTx->fourNibbles[i] == 255) {
          break;
        }        
     } 
     Serial.print (F("checkSum:"));
     Serial.println ( checkSum );     
     checksumGood = (checkSum == 0);
     return checksumGood;
  } 
  
  void update() {
     static bool gettingMAC = false;
     static char MAC[3] = { ' ',' ',' '};
     char ch = matchStream->ch;
     int hexValue;
     if (ch == 10) { // ignore LF
     } 
     else if (ch == 13) 
     {
        if (gettingMAC) {
           hexValue = (Utilities::chToHex(MAC[0]) * 0x100) + 
                      (Utilities::chToHex(MAC[1]) * 0x10) + 
                       Utilities::chToHex(MAC[2]);          
                   
           Serial.print ( F("\ngettingMAC is true, hexValue: ") );
           Serial.println ( hexValue, HEX );                    
           irTx->createFireSequence (hexValue );
        
           // Save MAC address to EEPROM
           for (int i=0; i<4; i++) {
               EEPROM.write(i, irTx->fourNibbles[i]);             
               Serial.print ( F("EEPROM>write (") );
               Serial.print ( i );
               Serial.print ( "," );
               Serial.print ( irTx->fourNibbles[i],HEX);
               Serial.println ( ")");
           }
        }
        gettingMAC = false;
     } 
     else if (ch != ':') // Store last 3 digits in MAC 
     {
         MAC[0] = MAC[1];
         MAC[1] = MAC[2];
         MAC[2] = ch;
     } 
     if (matchStream->match ("MAC:")) {
         Serial.println ( F("Got a match on MAC:, setting gettingMAC true") );
         gettingMAC = true;
     } 
     else 
     {
         if (gettingMAC) { 
         } 
         else // Handle other possible matches. 
         {
         }           
         
     }
  }
  
  void createFirePulse () { 
     if (checkSumOk()) {
        irTx->createFirePulse (irTx->fourNibbles[0], irTx->fourNibbles[1], 
                               irTx->fourNibbles[2], irTx->fourNibbles[3]);
     } else {
        Serial.println ( F("Checksum was bad, call showMAC()") );
     }
    
  } 
};
#endif