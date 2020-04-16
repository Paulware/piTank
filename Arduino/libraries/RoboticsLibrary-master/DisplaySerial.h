#ifndef DISPLAY_SERIAL_h
#define DISPLAY_SERIAL_h
#include <SoftwareSerial.h>

class DisplaySerial {
public:
  #define NOT_CONNECTED_PIN 20
  DisplaySerial (uint8_t pin) : displaySerial (NOT_CONNECTED_PIN,pin) {
    displaySerial.begin (9600);
    clearScreen();
  }; 
  
  void printChar (char ch ) {
    bool debugIt = false;
    if ((ch != 10) && (ch != 13)) { 
      if (ch == '^') { 
        clearScreen(); 
      } else {
        if (debugIt) {
          Serial.print ( "char [" );
          Serial.print ( x );
          Serial.print ( "," );
          Serial.print ( y );
          Serial.print ( "] = '" );
          Serial.print ( ch );
          Serial.println ( "'" );
        }  
        if ((x == 0) && (y == 4)) { 
          clearScreen();
        }
        displaySerial.print (ch);
        x = x + 1;
        if (x == 20) { 
          x = 0;
          y = y + 1;
          delay (50);
        }
      }  
    }  
  };
  
  void printString (String line) {
    for (int i=0; i<line.length(); i++ ) {       
       printChar (line.charAt(i));
    }
  }
  
  void printString (char * line) { 
    int len = strlen (line);
    for (int i=0; i<len; i++ ) {
      printChar (line[i]);
    }
  };
  
  void clearScreen () {
    displaySerial.print ( "^" );
    x = 0;
    y = 0;
  };  
    
private:  
  SoftwareSerial displaySerial;
  int x;
  int y;
};
#endif