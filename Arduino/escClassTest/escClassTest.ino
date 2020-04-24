#include "ESC.h"
ESC leftTread (5);
ESC rightTread (6);

void setup() 
{
  Serial.begin (9600);
  Serial.println ( "Ready escClassTest");
  leftTread.arm();
  rightTread.arm();
} 

// Enter a + to increase voltage, - to decrease the voltage at motor
void loop() 
{ 
  char ch;
  leftTread.update();
  rightTread.update();
  if (Serial.available() ) {   
     ch = Serial.read();
     Serial.print (ch); 
     switch (ch) { 
        case '+': 
           leftTread.forward();
           rightTread.forward();
           break;
        case 'L':
           leftTread.forward();
           break;
        case 'R':
           rightTread.forward();
           break;
        case 'l':
           leftTread.reverse();
           break;
        case 'r':
           rightTread.reverse();
           break;
        case 'S':
           leftTread.stop();
           break;
        case 's':
           rightTread.stop();
           break;
        case '-':
           leftTread.reverse();
           rightTread.reverse();
           break;
        default:
           break;
     }
  }  
} 
