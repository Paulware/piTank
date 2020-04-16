#ifndef StringBuffer_H
#define StringBuffer_H
#include "Arduino.h"
#define MAXSTRINGBUFFERCHARS 50

class StringBuffer 
{
  public:

    StringBuffer () {
       head = 0;
    }
    
    static char intToHex (int hex ) {
      char ch;
      if ((hex >=0) && (hex <= 9)) {
        ch = hex + '0';
      } else {
        ch = hex + 'a' - 10;
      }
      return ch;
    }    
    
    void clearBuffer () {
       head = 0;
       for (int i=0; i<MAXSTRINGBUFFERCHARS; i++ ) {
           buf[i] = 0;           
       } 
    } 
        
    void update (char ch) {
       if (ch) {
          buf[head] = ch;
          head = head + 1;
          if (head == MAXSTRINGBUFFERCHARS) {
             head = 0; // rollover
          }
       } 
    } 
    
    bool match (char * word) {
       bool matched = false;
       int start;
       int charAt = strlen (word) - 1;        
       char ch;
       bool debug = false;
       
       if (head == 0) {
          start = MAXSTRINGBUFFERCHARS - 1;
       } else {
          start = head -1;
       } 

       while (!matched) {
          if (buf[start] == word[charAt]) {
             if (debug) {
                Serial.print ( "Matching " );
                Serial.print ( word );
                Serial.print ( " got match at: " );
                Serial.println ( charAt );
             }   
             if (charAt == 0) {
                matched = true;
                clearBuffer();
                break;
             } 
             charAt = charAt - 1;             
          } else { // nomatch 
             break;
          } 
          
          if (start == 0) {
             start = MAXSTRINGBUFFERCHARS - 1;
          } else {
             start = start - 1;
          }                        
       }         

       return matched;
    } 
     
  private: 
    int head;
    char buf[MAXSTRINGBUFFERCHARS];
    byte numStrings;
};
#endif
