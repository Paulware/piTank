
#ifndef Joystick_H
#define Joystick_H
#include <Arduino.h>
class Joystick
{
  public:  
    int xPin;
    int yPin;
    int button;
    bool debugIt = false;
    String newX;
    String newY;
    String newZ;
    String bothReleased = ""; 
    int analogX = 0;
    int analogY = 0;    
        
    Joystick (int xAnalogPin, int yAnalogPin, int buttonPin ) {
       xPin = xAnalogPin;
       yPin = yAnalogPin;
       button = buttonPin;
       timeout = 1;
       pinMode (button,INPUT);
       digitalWrite (button,1); // Set the pull-up resistor
       
    } 
    
    void update() {
      int count = 0;
      lastX = xDirection;
      lastY = yDirection;
      lastZ = zButton;
      lastReleased = released;
      newX = "";
      newY = "";
      newZ = "";
      bothReleased = "";
      
      if ((millis() > timeout) && (timeout != 0)) { // Don't call too often      
         timeout = millis() + 100;  
      
         // Read the nunchuk values
         analogX = analogRead (xPin);
         analogY = analogRead (yPin);
         zButton = !digitalRead (button);
         
         xDirection = 0; // Initialized to release
         if (analogX < 200) { 
           xDirection = 1; // Left 
         } else if (analogX > 800) {
           xDirection = 2; // Right
         }
         if (debugIt) {
           Serial.print ( "[x,y]: " );
           Serial.print ( "[" );
           Serial.print ( xPin );
           Serial.print ( "," );
           Serial.print ( yPin );
           Serial.print ( "] [" );
           Serial.print ( analogX );
           Serial.print ( "," );
           Serial.print ( analogY );
           Serial.println ( "]" );
         }
         
         yDirection = 0; // Initialized to release
         if (analogY < 200) {
           yDirection = 2; // Down
         } else if (analogY > 800) { 
           yDirection = 1; // Up
         }

         newX = "";           
         if (lastX != xDirection) {
            xReleased = false;
            if (xDirection == 0) { 
               newX = "RELEASED";
               xReleased = true;
            } else if (xDirection == 1) { 
               newX = "LEFT";
            } else if (xDirection == 2) { 
               newX = "RIGHT";
            }
     
            if (debugIt) { 
               Serial.print ( "X Direction changed to \"" );
               Serial.print ( newX );
               Serial.println ( "\"" );
            }  
         }              
            
         newY = "";
         if (lastY != yDirection) {
            yReleased = false;
            if (yDirection == 0) {
               yReleased = true;             
               newY = "RELEASED";
            } else if (yDirection == 1) { 
               newY = "DOWN";
            } else if (yDirection == 2) { 
               newY = "UP";
            }
            if (debugIt) { 
               Serial.print ( "Y Direction changed to \"" );
               Serial.print ( newY );
               Serial.println ( "\"" );
            }  
         }             
          
             
         newZ = "";
         if (lastZ != zButton) {
           if (zButton == 1) { 
              newZ = "PRESSED";
           } else { 
              newZ = "RELEASED";
           } 
           if (debugIt) { 
              Serial.print ( "Z button changed to \"" );
              Serial.print ( newZ );
              Serial.println ( "\"" );
           }   
         }                    
         released = false;
         if (xReleased && yReleased) { 
            released = true;
         } 
         bothReleased = "";
         if (released != lastReleased) {
            if (released) {
               bothReleased = "YES";
            } else {
               bothReleased = "NO";
            }
            if (debugIt) {
                if (released) {
                   Serial.println ( "X & Y released" );
                } else {
                   Serial.println ( "X | Y not released" );
                }
            }
         }
      }   
    }  
    
    void showData() {
         Serial.print ( "[x,y,z]: [" );
         Serial.print ( analogX );
         Serial.print ( "," );
         Serial.print ( analogY );
         Serial.print ( "," ); 
         Serial.print ( zButton );
         Serial.print ( "], [xDirection, yDirection]: [" );
         Serial.print ( xDirection );
         Serial.print ("," );
         Serial.print ( yDirection );
         Serial.println ( "]" );         
    } 


  private:
    unsigned long timeout = 0;
    
    int lastZ        = 0; // 0 = Released, 1 = Pressed
    int zButton      = 0; // 0 = Released, 1 = Pressed
    int xDirection   = 0; // 0 = Released, 1 = Left, 2 = Right
    int lastX        = 0; // 0 = Released, 1 = Left, 2 = Right
    int yDirection   = 0; // 0 = Released, 1 = Left, 2 = Right  
    int lastY        = 0; // 0 = Released, 1 = Up, 2 = Right
    int lastReleased = 0; // 0 = Not Released, 1 = Released 
    int released     = 0; 
    bool xReleased   = true;
    bool yReleased   = true;  
};

#endif
