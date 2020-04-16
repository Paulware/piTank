#ifndef TextStream_h
#define TextStream_h

#include <SoftwareSerial.h>
class TextStream : public SoftwareSerial {
public:
  TextStream (int pin) : SoftwareSerial (pin,20) {
      begin (9600);
  };
  
  TextStream (int rxPin, int txPin) : SoftwareSerial (rxPin,txPin) {
      begin (9600);
  };
  
  TextStream() : SoftwareSerial (20,20) {
      useSerial = true;
  } 
         
  void update (void) {
     //bool debug = false;
     ch = 0;
     if (useSerial) {
        if (Serial.available()) {
           ch = Serial.read();
           /*
           if (debug) {
              if (ch == 10) { 
                 Serial.println ( "Ch == LF");            
              } else if (ch == 13) {
                 Serial.println ( "Ch == CR");            
              } else {          
                 Serial.print ( "Ch =" );
                 Serial.println (ch);
              }   
           }      
           */           
        }
     } else {
        if (available()) {
           ch = read();
        }
     }      
  };
  char ch; 
private:  
  bool useSerial = false;
};
#endif