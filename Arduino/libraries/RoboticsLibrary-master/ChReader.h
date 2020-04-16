#ifndef ChReader_h
#define ChReader_h

class ChReader {
public:
  ChReader () {
    ch = 0;
    line = "";
  }; // constructor
  
  void update () {
    if (Serial.available()) {
       ch = Serial.read();
       if ((ch == 10) || (ch == 13)) {
          line = ""; 
       } else {
          line = line + ch;
       }
    } else {
       ch = 0;
    }
  } 
  
  String read() {  
    String value = "";
    if ((ch != 0) && (ch != 10) && (ch != 13)) {     
      value += ch;
    }  
    return value;
  }
  
  String readLine() {  
    return line;
  }

  
private:
  char ch;
  String line;
};
#endif