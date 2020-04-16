#ifndef IR_RX_TX_h
#define IR_RX_TX_h
#include "IR.h"
#include "IRTx.h"
#include <TimerOne.h>

class IRRxTx {
public:
  IRRxTx ( IR * irRxPtr, IRTX * irTxPtr, TimerOne * timer1Ptr) {
     timer1 = timer1Ptr;
     irRx = irRxPtr;
     irTx = irTxPtr;          
  }; // constructor
  
  void fire() {
     timer1->stop(); 
     irTx->fire();
     timer1 -> resume();     
  } 
  
  void fireShot() {
     irTx->fireShot();
  } 
  
  
  
  // macs are hex digits 
  void createFireSequence (int hexValue) { 
     irTx -> createFireSequence (hexValue);
  } 
  
  void update() {
  } 
  
// return non-zero if a shot was detected
int IRDetected ( void )
{
  int shot = 0;
  unsigned int val; // IR value
  int check;
  if (irRx->irReady) {
     val = irRx->decodeBits ( 35, true, false);
     if (val == 0x0018) { // Micro Huan Qi
        shot = 1; // Huan Qi                
     } else { 
        val = irRx->decodeBits (18, true, false);    
        if (val == 0xCCCC) { // Huan Qi
           shot = 2; 
        } else {
           val = irRx->decodeBits (15, true, false);    
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
     irRx->resetIR(); 
  }    
  return shot;
}

bool irReady() {
   return irRx -> irReady;
} 
  

private:

  int getChecksum (int val1, int val2, int val3) {
     int checksum = val1;
     checksum = checksum ^ val2;
     checksum = checksum ^ val3;
     return checksum;
  }
  
  TimerOne * timer1;
  IR * irRx;
  IRTX * irTx;
};
#endif