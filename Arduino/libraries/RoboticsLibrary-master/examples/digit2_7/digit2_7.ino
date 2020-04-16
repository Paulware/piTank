#include <digit2_7.h>

// Arduino digital pins used to light up
// corresponding segments on the LED display
#define A 8
#define B 9
#define C 11
#define D 14
#define E 12
#define F_SEG 7
#define G 6

// Pins driving common anodes
#define CA1 5
#define CA2 10

#define triggerPin 16
#define MAXAMMO 50

Digit2_7 digit2_7 = Digit2_7 ( A, B, C, D, E, F_SEG, G, CA1, CA2, MAXAMMO );

void setup() {
  Serial.begin (9600);
  Serial.println ( "Ready" );
}

void loop() {
  static int value = 25;
  static unsigned long timeout = 0;
  char ch;

  if (Serial.available() ) {
    ch = Serial.read();
    if (ch == 10) {
      digit2_7.decrementNumber();
    }
  }
  
  digit2_7.update();
}
