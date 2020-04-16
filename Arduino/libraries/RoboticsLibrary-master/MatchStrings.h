#ifndef MATCHSTRINGS_H
#define MATCHSTRINGS_H
#include "Arduino.h"
#define MATCHINDEXES 20
#define MATCHNUMCHARS 200
struct CommandStringType
{
  int index;
  String str;
};

class MatchStrings 
{
  public:

    MatchStrings () {
       numStrings = 0;
       head = 0;
    }
    
    void addString (String str) {
       if (numStrings < MATCHINDEXES) {
          startIndexes[numStrings] = head;
          lengths[numStrings] = str.length();
          indexes[numStrings] = 0;
          for (int i=0; i<str.length(); i++) {
             if (head < MATCHNUMCHARS) {
                chars[head] = str.charAt (i);
                head = head + 1;
             } else {
                Serial.println ( F("MatchStrings.addString, ERR Too many chars") );
             }           
          } 
          numStrings = numStrings + 1;
       } else {
          Serial.println ( F("ERR Too many Strings") );
       }
    } 
    
    void clearIndexes (int skipIndex) {
       for (int i=0; i<numStrings; i++) {
          if (i != skipIndex) {
              indexes[i] = 0;
          } 
       } 
    } 
    
    int findMatch (char ch) {
       int match = -1;
       byte ind;
       char ch1;
       bool debug = false;
       for (int i=0; i<numStrings; i++) {
          if (indexes[i] == lengths[i]) { // previous match 
             indexes[i] = 0;
          } 
          ind = indexes[i];
          ch1 = chars [startIndexes[i] + ind];
          if (ch1 == ch) { 
             indexes[i] = indexes[i] + 1;
             if (indexes[i] == lengths[i]) {
                match = i;
                clearIndexes(i);
                break;
             } 
             if (debug) {
                Serial.print ( "Matched " );
                Serial.print (ch );
                Serial.print ( " count: " );
                Serial.print ( indexes[i] );                
                Serial.print ( " match: " );
                Serial.println ( match );
             } 
          } else {
             indexes[i] = 0;
          }           
       }
       return match;
    } 
     
  private: 
    int head;
    char chars[MATCHNUMCHARS];
    byte startIndexes [MATCHINDEXES];
    byte indexes [MATCHINDEXES];
    byte lengths [MATCHINDEXES];
    byte numStrings;
};
#endif
