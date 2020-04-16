#ifndef IR_Pipboy_h
#define IR_Pipboy_h
#include "IR.h"
#include <TimerOne.h>

// Off time = 500 microseconds
#define OFFTIME 500
class IRPipboy : public IR {
public:
  // repairRobot is set true if the unit is a repair robot
  IRPipboy ( int irrcvpin, int irTransmitPin, TimerOne * timer1) : IR (irrcvpin) {
    Timer1 = timer1;
	   irTransmit = irTransmitPin;
	   repairRobot = false;
        
  }; // constructor

  // Fields
  int fireType;   
  uint16_t firePulses[32];
  int fourNibbles[4];
  
  // Methods 
  void init (void);
  void fire(void);
  int IRDetected(); 
  int getChecksum (int val1, int val2, int val3);
    
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
    Serial.print ( "fourNibbles[] = " );
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
  
  void createFireSequence (unsigned int data){
    
    fourNibbles[0] = (data & 0xF00) / 0x100;
    fourNibbles[1] = (data & 0xF0) / 0x10;
    fourNibbles[2] = (data & 0xF);
    
    // Create Fire sequence from data, you care about the last3
    fourNibbles[3] = getChecksum (fourNibbles[0],fourNibbles[1], fourNibbles[2]);
    createFirePulse (fourNibbles[0], fourNibbles[1], fourNibbles[2], fourNibbles[3] );
  }

  // return true if a shot (with checksum) was detected
  unsigned int irValue( void )
  {
    unsigned int val; // IR value
    int check;
    bool shot = false;
    if (irReady) {
       val = decodeBits (15, true, false);    
       //if (val != 0) { 
       //   check = getChecksum ((val & 0xF000) / 0x1000, (val & 0xF00) / 0x100, (val & 0xF0) / 0x10);
       //   if ((val & 0xF) == check ) { 
       //      shot = true;
       //   }        
       //}   
       resetIR(); 
    }    
    return val;
  }
  
  // return true if a shot (with checksum) was detected
  bool shotDetected ( void )
  {
    unsigned int val; // IR value
    int check;
    bool shot = false;
    if (irReady) {
       val = decodeBits (15, true, false);    
       if (val != 0) { 
          check = getChecksum ((val & 0xF000) / 0x1000, (val & 0xF00) / 0x100, (val & 0xF0) / 0x10);
          if ((val & 0xF) == check ) { 
             shot = true;
          }        
       }   
       resetIR(); 
    }    
    return shot;
  }

  
  int MACtoHex (char * MAC) { 
    int value = (chToHex(MAC[0]) * 0x100) + (chToHex(MAC[1]) * 0x10) + chToHex(MAC[2]);    
    return value;
  }
      
  void fireShot() {
    if (millis() < pipFireTimeout) {
      Serial.println ( "Wait for previous shot to finish" );
    } else {
      fireData();
      pipFireTimeout = millis() + 600;
      Serial.println ( "ot" );
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
  
  void update() {
    // do nothing
  }
  
private:
  TimerOne * Timer1;
  int irTransmit;
  unsigned long pipFireTimeout = 0;
  bool repairRobot;
  #include "IRPulses.h"    
};
#endif