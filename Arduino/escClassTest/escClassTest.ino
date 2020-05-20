#include "ESC.h"
ESC leftTread (5);
ESC rightTread (6);

void setup() 
{
  Serial.begin (9600);
  Serial.println ( "Ready escClassTest");
  //rightTread.arm();
  leftTread.arm1();
  rightTread.arm1();
  delay (2000);
  leftTread.arm2();
  rightTread.arm2();
  delay (2000);
  rightTread.ready = true;
  leftTread.ready = true;
} 

// Enter a + to increase voltage, - to decrease the voltage at motor
void loop() 
{ 
  char ch;

  rightTread.update();
  leftTread.update();

  if (Serial.available() ) {   
     ch = Serial.read();
     Serial.print (ch); 
     switch (ch) { 
        case '+': 
           if (rightTread.currentValue < 2000){ 
              rightTread.currentValue = rightTread.currentValue + 100;
           }
           Serial.print ( "rightTread.currentValue:" );
           Serial.println ( rightTread.currentValue );
           
           if (leftTread.currentValue < 2000){ 
              leftTread.currentValue = leftTread.currentValue + 100;
           }
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
           if (rightTread.currentValue > 1000){ 
              rightTread.currentValue = rightTread.currentValue - 100;
           }
           Serial.print ( "rightTread.currentValue:" );
           Serial.println ( rightTread.currentValue );
           if (leftTread.currentValue > 2000){ 
              leftTread.currentValue = leftTread.currentValue - 100;
           }
           break;
        default:
           break;
     }
  }  
} 
