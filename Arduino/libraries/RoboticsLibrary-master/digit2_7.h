#ifndef Digit2_7_h
#define Digit2_7_h

#include <Arduino.h>
class Digit2_7 {
public:
// www.TinkerHobby.com
// Natalia Fargasch Norman
// Dual seven-segment LED Display
// Common Anode digit 1 pin 10
// Common Anode digit 2 pin 5

//       CA1 G  F  A  B
//        |  |  |  |  |      -> pins and segments they control
//   ---------    ---------
//   |   A   |    |   A   |
//  F|       |B  F|       |B
//   |---G---|    |---G---|
//  E|       |C  E|       |C
//   |   D   |    |   D   |
//   ---------    ---------
//        |  |  |  |  |      -> pins and segments they control
//        D  DP E  C CA2         

// Segments that make each number when lit:
// 0 => -FEDCBA
// 1 => ----BC-
// 2 => G-ED-BA
// 3 => G--DCBA
// 4 => GF--CB-
// 5 => GF-DC-A
// 6 => GFEDC-A
// 7 => ----CBA
// 8 => GFEDCBA
// 9 => GF-DCBA

  Digit2_7 (int A, int B, int C, int D, int E, int F_SEG, int G, 
            int _CA1, int _CA2, int _MAXNUMBER) {   
    pinMode(A, OUTPUT);
    pinMode(B, OUTPUT);
    pinMode(C, OUTPUT);
    pinMode(D, OUTPUT);
    pinMode(E, OUTPUT);
    pinMode(F_SEG, OUTPUT);
    pinMode(G, OUTPUT);
    CA1 = _CA1;
    CA2 = _CA2;
    pinMode(CA1, OUTPUT);
    pinMode(CA2, OUTPUT);       
    segs[0] = A;
    segs[1] = B;
    segs[2] = C;
    segs[3] = D;
    segs[4] = E;
    segs[5] = F_SEG;
    segs[6] = G;
    if (_MAXNUMBER < 100) {
      MAXNUMBER = _MAXNUMBER;
    } else {
      MAXNUMBER = 99;     
    }    
    currentNumber = MAXNUMBER;
  }; // constructor
  
  void lightSegments(byte number) {
    for (int i = 0; i < 7; i++) {
      int bit = bitRead(number, i);
      digitalWrite(segs[i], bit);
    }
  };
    
  void lightDigit1(byte number) {
    digitalWrite(CA1, LOW);
    digitalWrite(CA2, HIGH);
    lightSegments(number);
  };

  void lightDigit2(byte number) {
    digitalWrite(CA1, HIGH);
    digitalWrite(CA2, LOW);
    lightSegments(number);
  };

  void outputNumber () {
    int digit1 = currentNumber / 10;
    int digit2 = currentNumber - (digit1 * 10);

    lightDigit1 ( numbers[digit1] );
    delay (5);
    lightDigit2 ( numbers[digit2] ); 
    delay (5);
  };  
  
  void decrementNumber () {   
    if (currentNumber == 0) { 
      currentNumber = MAXNUMBER;
    } else {
      currentNumber = currentNumber - 1; 
    }                       
    outputNumber();
  };
  
  void incrementNumber () {   
    if (currentNumber == MAXNUMBER) { 
      currentNumber = 0;
    } else {
      currentNumber = currentNumber + 1; 
    }                       
    outputNumber();
  };
  
  void update (void) {
    outputNumber();
  };
   
private:
    int CA1;
    int CA2;
    int segs[7]; 
    int MAXNUMBER;
    int currentNumber;
    // Segments that make each number
    const byte numbers[10] = { 0b0111111, 0b0000110, 0b1011011, 0b1001111, 0b1100110, 0b1101101,
    0b1111101, 0b0000111, 0b1111111, 0b1101111 };
};
#endif