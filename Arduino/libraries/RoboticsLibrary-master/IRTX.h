#ifndef IR_TX_h
#define IR_TX_h

#include <Arduino.h>
// #include <avr/interrupt.h>

// Off time = 500 microseconds
#define OFFTIME 500
class IRTX {
public:
  IRTX ( int irTransmitPin)  {
	   irTransmit = irTransmitPin;
	   repairRobot = false;
    pinMode (irTransmit,OUTPUT); 
    digitalWrite (irTransmit, 0); // Keep output low when not in use        
  }; // constructor

  // Fields
  int fireType;   
  uint16_t firePulses[32];
  int fourNibbles[4];
  
  // Methods 
  void fire(void);
    
  // mac is a hex digit 
  void createFireSequenceChars (char mac1, char mac2, char mac3) {
     unsigned int total = 0;
     total = total + chToHex (mac1);
     total = (total * 16) + chToHex (mac2);
     total = (total * 16) + chToHex (mac3);    
     createFireSequence (total);
  }   
  void fireData(void);
  void fireAll (void);  
  void sendFirePulse(void);
  void showNibbles() {
    Serial.print ( F("fourNibbles[] = ") );
    for (int i=0; i<4; i++) { 
       if (i==0) {      
         Serial.print ( "{0x" );
         Serial.print ( fourNibbles [i],HEX );
       } else if (i == 3) { 
         Serial.print ( ",0x" );  
         Serial.print ( fourNibbles [i],HEX );
         Serial.println ( "};" );
       } else { 
         Serial.print ( ",0x" );
         Serial.print ( fourNibbles [i],HEX );
       }
    } 
  }  
  
  void createFirePulse (int nibble1, int nibble2, int nibble3, int nibble4){
    int index = 0;
    int bitValue = 0;
    int fourBits[4];
    int nibble;
    Serial.print ( F("createFirePulse (") );
    Serial.print (nibble1,HEX );
    Serial.print ( "," );
    Serial.print (nibble2,HEX);
    Serial.print ("," );
    Serial.print (nibble3,HEX);
    Serial.print (",");
    Serial.print (nibble4,HEX);
    Serial.println ( ")");
    // Create FirePulses based on data address     
    for (int i=0; i<4; i++) {
      if (i == 0) 
         nibble = nibble1;
      else if (i == 1) 
         nibble = nibble2;
      else if (i == 2)
         nibble = nibble3;
      else if (i == 3)
         nibble = nibble4;
        
      fourBits[0] = nibble & 0x8;
      fourBits[1] = nibble & 0x4;
      fourBits[2] = nibble & 0x2;
      fourBits[3] = nibble & 0x1; 
      // 16 on and 16 off pulses,     
      for (int j=0; j<4; j++) {
         if (fourBits[j] != 0) { // 1 value = twice off time          
           firePulses[index] =  OFFTIME * 2;
         } else { // 0 value, ON time = OFF time
           firePulses[index] = OFFTIME;
         }         
         // Add the off pulse
         index = index + 1;
         firePulses[index] = OFFTIME;
         index = index + 1;
      }     
    } 
  }

  void createDataSequence (unsigned int data){
    
    fourNibbles[0] = (data & 0xF00) / 0x100;
    fourNibbles[1] = (data & 0xF0) / 0x10;
    fourNibbles[2] = (data & 0xF);
    

    createFirePulse (0, fourNibbles[0], fourNibbles[1], fourNibbles[2] );
  }
  
  int getChecksum (int val1, int val2, int val3) {
     int checksum = val1;
     checksum = checksum ^ val2;
     checksum = checksum ^ val3;
     return checksum;
  }  
  
  void createFireSequence (unsigned int data){
    
    fourNibbles[0] = (data & 0xF00) / 0x100;
    fourNibbles[1] = (data & 0xF0) / 0x10;
    fourNibbles[2] = (data & 0xF);
    
    // Create Fire sequence from data, you care about the last3
    fourNibbles[3] = getChecksum (fourNibbles[0],fourNibbles[1], fourNibbles[2]);
    createFirePulse (fourNibbles[0], fourNibbles[1], fourNibbles[2], fourNibbles[3] );
  }

  int MACtoHex (char * MAC) { 
    int value = (chToHex(MAC[0]) * 0x100) + (chToHex(MAC[1]) * 0x10) + chToHex(MAC[2]);    
    return value;
  }
      
  void fireShot() {
    if (millis() < pipFireTimeout) {
      Serial.println ( F("Wait for previous shot to finish") );
    } else {
      fireData();
      pipFireTimeout = millis() + 600;
      Serial.println ( F("ot") );
    }
  }
  
  void fireValue(unsigned int value) {
     createFireSequence (value);
     fireShot();
  }
     
  char intToHex (int hex ) {
    char ch;
    if ((hex >=0) && (hex <= 9)) {
      ch = hex + '0';
    } else {
      ch = hex + 'a' - 10;
    }
    return ch;
  };
  
  // Is this function used anywhere?
  int chToHex (char ch) {
    int value;
    if ((ch >= '0') && (ch <= '9'))
       value = ch - '0';
    else if (( ch >= 'A') && (ch <= 'Z')) 
       value = ch - 'A' + 10;
    else 
       value = ch - 'a' + 10;
    return value;
  };
  
private:
  int irTransmit;
  unsigned long pipFireTimeout = 0;
  bool repairRobot;
  void space(int time);
  void sendRaw(unsigned int uDelay, int index);
  void enableIROut();
  
};
#endif