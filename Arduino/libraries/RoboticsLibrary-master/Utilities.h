#ifndef Utilities_h
#define Utilities_h

class Utilities {
public:
   static int inRange (int value, int minimumValue, int maximumValue ) {       
      if (value < minimumValue) {
         value = minimumValue;
      } else if (value > maximumValue) {
         value = maximumValue;
      }
      return value;
   } 
   
   static int chToHex (char ch) {
      int value;
      if ((ch >= '0') && (ch <= '9'))
         value = ch - '0';
      else if ((ch >= 'a') && (ch <= 'f')) 
         value = ch - 'a' + 10;
      else 
         value = ch - 'A' + 10;
      return value;
   }   
};
#endif