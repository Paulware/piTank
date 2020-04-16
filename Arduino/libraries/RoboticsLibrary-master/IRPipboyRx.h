#ifndef IR_Pipboy_Rx_h
#define IR_Pipboy_Rx_h
#include "IR.h"
#include <TimerOne.h>

// Off time = 500 microseconds
#define OFFTIME 500
class IRPipboyRx : public IR {
public:
  // repairRobotValue is set true if the unit is a repair robot
  IRPipboyRx ( int irrcvpin, TimerOne * timer1) : IR (irrcvpin) {
    Timer1 = timer1;
  }; // constructor

  
// Methods 
int getChecksum (int val1, int val2, int val3) {
   int checksum = val1;
   checksum = checksum ^ val2;
   checksum = checksum ^ val3;
   return checksum;
}

// return non-zero if a shot was detected
int IRDetected ( void )
{
  int shot = 0;
  unsigned int val; // IR value
  int check;
  if (irReady) {
     val = decodeBits ( 35, true, false);
     if (val == 0x0018) { // Micro Huan Qi
        shot = 1; // Huan Qi                
     } else { 
        val = decodeBits (18, true, false);    
        if (val == 0xCCCC) { // Huan Qi
           shot = 2; 
        } else {
           val = decodeBits (15, true, false);    
           if (val != 0) { 
              check = getChecksum ((val & 0xF000) / 0x1000, (val & 0xF00) / 0x100, (val & 0xF0) / 0x10);
              if ((val & 0xF) == check ) { 
                 shot = (val & 0xFFF0) / 0x10;
              } else {
                 Serial.print ( val, HEX );
                 Serial.print ( " != " );
                 Serial.println ( check, HEX );
              }        
           }         
         
        }         
     } 
     resetIR(); 
  }    
  return shot;
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
       if (val != 0) { 
          lastDecodedValue = val; 
       }
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
};
#endif