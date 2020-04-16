// This class is used by the master arduino to receive
// nrf data.  Tx is not required because does not need pin 10.
#ifndef CIRCULAR_BUFFER_h
#define CIRCULAR_BUFFER_h

#define CIRCULARBUFFERSIZE 256
class CircularBuffer {
public:
  CircularBuffer () {
    for (int i=0; i<CIRCULARBUFFERSIZE; i++) {
       buffer[i] = 0;
    }   
    head = 0;
    tail = 0;
  }; 
  
  char peek () {
    return buffer[tail];
  }
  
  // promote last entry to the top of the stack 
  void promote () {
    if (head != tail) { // Data is available 
      if (head == 0) {
        tail = CIRCULARBUFFERSIZE - 1;
      } else { // head > 0
        tail = head - 1;
      }  
    }
  }
  
  void push (char ch) {
    buffer[head] = ch;
    head = head + 1;
    head = head % CIRCULARBUFFERSIZE;
  }
  
  char pop () {
    char ch = buffer[tail];
    tail = tail + 1;
    tail = tail % CIRCULARBUFFERSIZE;
    return ch;
  }
  
  bool available() {
    return (head != tail);
  }
  
private:  
  char buffer [CIRCULARBUFFERSIZE];
  int head;
  int tail;
};
#endif