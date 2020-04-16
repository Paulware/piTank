#ifndef MatchStream_h
#define MatchStream_h

#include <TextStream.h>
#include <StringBuffer.h>
class MatchStream : public TextStream {
public:
  MatchStream (int pin) : TextStream (pin) {
  };
  
  MatchStream (int rxPin, int txPin ): TextStream (rxPin, txPin) {
  }; 
  
  MatchStream() : TextStream () {
  } 
         
  void update (void) {
     TextStream::update();
     stringBuffer.update(ch);
  };
  
  bool match (char * word) { 
     return stringBuffer.match (word);
  } 
  private: 
     StringBuffer stringBuffer;
};
#endif