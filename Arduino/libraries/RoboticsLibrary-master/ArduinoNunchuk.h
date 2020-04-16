
#ifndef ArduinoNunchuk_H
#define ArduinoNunchuk_H

#include <Arduino.h>
#include <Wire.h>
class ArduinoNunchuk
{
  public:  
    String newX = "";
    String newY = "";
    String newC = "";
    String newZ = "";
    bool debugIt = false;
    
    void init() {
      Wire.begin();
      _sendByte(0x55, 0xF0);
      _sendByte(0x00, 0xFB);     
      timeout = millis() + 100; // Wait before calling first update
      // For some strange reason, a z button event always shows up on startup.
      // This timeout will allow us to ignore values until time has elapsed
      ignoreTimeout = millis() + 500; 
    }

    void update() {
      int count = 0;
      int values[6];
      lastX = xDirection;
      lastY = yDirection;
      lastC = cButton;
      lastZ = zButton;
      lastReleased = released;
      newC = "";
      newX = "";
      newY = "";
      newZ = "";
      
      if ((millis() > timeout) && (timeout != 0)) { // Don't call too often      
         timeout = millis() + 100;  
      
         Wire.requestFrom(0x52, 6);  //0x52 is the IIC address of the nunchuk
         while(Wire.available())
         {
           values[count] = Wire.read();
           count++;
         }
         // Read the nunchuk values
         analogX = values[0];
         analogY = values[1];
         accelX = (values[2] << 2) | ((values[5] >> 2) & 3);
         accelY = (values[3] << 2) | ((values[5] >> 4) & 3);
         accelZ = (values[4] << 2) | ((values[5] >> 6) & 3);
         zButton = !((values[5] >> 0) & 1);
         cButton = !((values[5] >> 1) & 1);
         
         _sendByte(0x00, 0x00);  
    
         xDirection = 0; // Initialized to release
         if (analogX < 50) { 
           xDirection = 1; // Left 
         } else if (analogX > 200) {
           xDirection = 2; // Right
         }
         
         yDirection = 0; // Initialized to release
         if (analogY < 50) {
           yDirection = 2; // Down
         } else if (analogY > 200) { 
           yDirection = 1; // Up
         }

         if ((millis() > ignoreTimeout) && (ignoreTimeout != 0)) { 
            newX = "";           
            if (lastX != xDirection) {
               if (xDirection == 0) { 
                  newX = "RELEASED";
               } else if (xDirection == 1) { 
                  newX = "LEFT";
               } else if (xDirection == 2) { 
                  newX = "RIGHT";
               }
               // showData();
               if (debugIt) { 
                  Serial.print ( "X Direction changed to \"" );
                  Serial.print ( newX );
                  Serial.println ( "\"" );
               }  
            }              
            
            newY = "";
            if (lastY != yDirection) {
               if (yDirection == 0) { 
                  newY = "RELEASED";
               } else if (yDirection == 1) { 
                  newY = "UP";
               } else if (yDirection == 2) { 
                  newY = "DOWN";
               }
               if (debugIt) { 
                  Serial.print ( "Y Direction changed to \"" );
                  Serial.print ( newY );
                  Serial.println ( "\"" );
               }  
            }             
          
            newC = "";
            if (lastC != cButton) { 
               if (cButton == 1) { 
                  newC = "PRESSED";
               } else { 
                  newC = "RELEASED";
               } 
               if (debugIt) {
                  Serial.print ( "C button changed to \"" );
                  Serial.print ( newC );
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
         }   
      }   
    }  
    
    void showData() {
         Serial.print ( "[x,y,c,z]: [" );
         Serial.print ( analogX );
         Serial.print ( "," );
         Serial.print ( analogY );
         Serial.print ( "," ); 
         Serial.print ( cButton );
         Serial.print ( "," );
         Serial.print ( zButton );
         Serial.print ( "], [xDirection, yDirection]: [" );
         Serial.print ( xDirection );
         Serial.print ("," );
         Serial.print ( yDirection );
         Serial.println ( "]" );         
    }
    
    // Check for a joystick change in the x and y direction 
    bool joystickReleased () { 
       bool rel = false;
       if ((lastX == 0) && (lastY == 0)) {
         released = 1;
       } else {
         released = 0;
       }
       if (lastReleased != released) { // released has changed
         if (released == 1) {
            rel = true;
         }
       }
       return rel;
    }  
    
    void _sendByte(byte data, byte location) {
      Wire.beginTransmission(0x52);  // 0x52 = IIC address of nunchuk
      Wire.write(location);
      Wire.write(data);
      Wire.endTransmission();
      delay(10);
    }


  private:
    unsigned long timeout = 0;
    unsigned long ignoreTimeout = 0;
    int analogX = 0;
    int analogY = 0;
    int accelX = 0;
    int accelY = 0;
    int accelZ = 0;
    
    int lastC        = 0; // 0 = Released, 1 = Pressed
    int lastZ        = 0; // 0 = Released, 1 = Pressed
    int cButton      = 0; // 0 = Released, 1 = Pressed
    int zButton      = 0; // 0 = Released, 1 = Pressed
    int xDirection   = 0; // 0 = Released, 1 = Left, 2 = Right
    int lastX        = 0; // 0 = Released, 1 = Left, 2 = Right
    int yDirection   = 0; // 0 = Released, 1 = Left, 2 = Right  
    int lastY        = 0; // 0 = Released, 1 = Up, 2 = Right
    int lastReleased = 0; // 0 = Not Released, 1 = Released 
    int released     = 0; 
    
};

#endif
