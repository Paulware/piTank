
#ifndef Ps2Wireless_H
#define Ps2Wireless_H

#include <PS2X_lib.h> 
class Ps2Wireless
{
  public:  
    String newX              = "";
    String newY              = "";
    String newXR             = "";
    String newYR             = "";
    String newLeft           = "";
    String newRight          = "";
    String newFire           = "";
    String newXButton        = "";
    String newCircleButton   = "";
    String newSquareButton   = "";
    String newTriangleButton = "";
    
    
    bool debugIt = true;
    
    int error = 0; 
    byte type = 0;
    byte vibrate = 0;    

    PS2X ps2x; // create PS2 Controller Class    

    Ps2Wireless (bool debugMode = false ) {\
       debugIt = debugMode;
    } 
    void init(int attPin) {
       error = ps2x.config_gamepad(13,11,attPin,12, true, true);   //setup pins and settings:  GamePad(clock, command, attention, data, Pressures?, Rumble?) check for error
 
       if (debugIt) { 
          if(error == 0){
             Serial.println("Found Controller, configured successful");
          } else if(error == 1) {
             Serial.println("No controller found");   
          } else if(error == 2) {
             Serial.println("Controller found but not accepting commands");   
          } else if(error == 3) {
             Serial.println("Controller refusing to enter Pressures mode.");
          }
       }   
   
       type = ps2x.readType();
       if (debugIt) {        
          switch(type) {
             case 0:
                Serial.println("Unknown Controller");
                break;
             case 1:
                Serial.println("DualShock");
                break;
             case 2:
                Serial.println("GuitarHero");
                break;
          }
       }   
       timeout = millis() + 50; // Wait before calling first update             
    }
    
    void readStick (String name, int & stick, int & direction, int value, 
                    int & lastDirection, String dir0, String dir1, 
                    String dir2, String & newValue) {
       // String newValue;
       stick = value;
       direction = 0;
       if (value < 50) {
         direction = 1;
       } else if (value > 200) {
         direction = 2;
       }
       
       if (lastDirection != direction) {
          if (direction == 0) { 
             newValue = dir0;
          } else if (direction == 1) { 
             newValue = dir1;
          } else if (direction == 2) { 
             newValue = dir2;
          }
          if (debugIt) { 
            Serial.print ( name );
            Serial.print ( " direction changed to \"" );
            Serial.print ( newValue );
            Serial.println ( "\"" );
          }  
       }         
    } 

    void update() {
      int count = 0;
      int values[6];
      lastXR           = xRDirection;
      lastYR           = yRDirection;
      lastX            = xDirection;
      lastY            = yDirection;
      lastLeft         = leftButton;
      lastRight        = rightButton;
      lastFire         = fireButton;
      lastReleased     = released;
      lastXButton      = xButton;
      lastSquareButton = squareButton;
      lastCircleButton = circleButton;
      lastTriangleButton = triangleButton;
      newLeft = "";
      newRight = "";
      newFire           = "";
      newXButton        = "";
      newX = "";
      newXR = "";
      newYR = "";
      newY = "";
      newCircleButton   = "";
      newSquareButton   = "";
      newTriangleButton = "";
      
      if (timeout) { 
        if (millis() > timeout) { 
           timeout = millis() + 50;
           ps2x.read_gamepad(false, vibrate);          //read controller and set large motor to spin at 'vibrate' speed
           
           readStick ("Right joystick", analogXR, xRDirection,
                      ps2x.Analog(PSS_RX), lastXR,
                      "RELEASED", "LEFT", "RIGHT", newXR);
                      
           readStick ("Right joystick", analogYR, yRDirection,
                      ps2x.Analog(PSS_RY), lastYR,
                      "RELEASED", "UP", "DOWN", newYR);                                   
                      
           readStick ("Left joystick", analogX, xDirection, 
                      ps2x.Analog(PSS_LX), lastX,
                      "RELEASED", "LEFT", "RIGHT", newX);                      

           readStick ("Left joystick", analogY, yDirection, 
                      ps2x.Analog(PSS_LY), lastY,
                      "RELEASED", "UP", "DOWN", newY);                      
      

           // Check if any button changes state (on to off, or off to on)
           if (ps2x.NewButtonState())             
           {    

              leftButton = 0;                                                     
              if (ps2x.Button(PSB_L1) || ps2x.Button(PSB_L2)) {
                 leftButton = 1;
              }             
              
              rightButton = 0;                                                     
              if (ps2x.Button(PSB_R1) || ps2x.Button(PSB_R2)) {
                 rightButton = 1;
              }       
              
              fireButton = 0;
              if (ps2x.Button(PSB_L3) || ps2x.Button(PSB_R3)) {
                 fireButton = 1;
              }                 
           } 
           
            newLeft = "";
            if (lastLeft != leftButton) { 
               if (leftButton == 1) { 
                  newLeft = "PRESSED";
               } else { 
                  newLeft = "RELEASED";
               } 
               if (debugIt) {
                  Serial.print ( "Left button changed to \"" );
                  Serial.print ( newLeft );
                  Serial.println ( "\"" );
               }   
            } 

            newRight = "";
            if (lastRight != rightButton) { 
               if (rightButton == 1) { 
                  newRight = "PRESSED";
               } else { 
                  newRight = "RELEASED";
               } 
               if (debugIt) {
                  Serial.print ( "Right button changed to \"" );
                  Serial.print ( newRight );
                  Serial.println ( "\"" );
               }   
            } 

            
            newFire = "";
            if (lastFire != fireButton) {
              if (fireButton == 1) { 
                newFire = "PRESSED";
              } else { 
                newFire = "RELEASED";
              } 
              if (debugIt) { 
                 Serial.print ( "Fire button changed to \"" );
                 Serial.print ( newFire );
                 Serial.println ( "\"" );
              }   
            }            
           
            if (debugIt) { 
              if(ps2x.Button(PSB_START))                   //will be TRUE as long as button is pressed
                  Serial.println("Start is being held");
              if(ps2x.Button(PSB_SELECT))
                  Serial.println("Select is being held");                                
              if(ps2x.Button(PSB_PAD_UP)) {         //will be TRUE as long as button is pressed
                Serial.print("Up held this hard: ");
                Serial.println(ps2x.Analog(PSAB_PAD_UP), DEC);
              }
              if(ps2x.Button(PSB_PAD_RIGHT)){
                 Serial.print("Right held this hard: ");
                 Serial.println(ps2x.Analog(PSAB_PAD_RIGHT), DEC);
              }
              if(ps2x.Button(PSB_PAD_LEFT)){
                 Serial.print("LEFT held this hard: ");
                 Serial.println(ps2x.Analog(PSAB_PAD_LEFT), DEC);
              }
              if(ps2x.Button(PSB_PAD_DOWN)){
                 Serial.print("DOWN held this hard: ");
                 Serial.println(ps2x.Analog(PSAB_PAD_DOWN), DEC);
              }   
            }
           
            vibrate = ps2x.Analog(PSAB_BLUE);        //this will set the large motor vibrate speed based on 
                                                     //how hard you press the blue (X) button    
           
           //if (ps2x.NewButtonState())               //will be TRUE if any button changes state (on to off, or off to on)
           //{    
           //    if(ps2x.Button(PSB_GREEN))
           //     Serial.println("Triangle pressed");            
           //}   

           newCircleButton = "";
           // Check if button pressed
           if(ps2x.ButtonPressed(PSB_RED)) {
              circleButton = 1;
           }
           else if (ps2x.ButtonReleased (PSB_RED)) {
              circleButton = 0;
           } 
           if (circleButton != lastCircleButton) {
              if (circleButton == 1) {
                 newCircleButton = "PRESSED";
              } else {
                 newCircleButton = "RELEASED";
              }
           }   
  
           newTriangleButton = "";
           // Check if button pressed
           if(ps2x.ButtonPressed(PSB_TRIANGLE)) {
              triangleButton = 1;
           }
           else if (ps2x.ButtonReleased (PSB_TRIANGLE)) {
              triangleButton = 0;
           } 
           if (triangleButton != lastTriangleButton) {
              if (triangleButton == 1) {
                 newTriangleButton = "PRESSED";
              } else {
                 newTriangleButton = "RELEASED";
              }
           } 
  
           newSquareButton = "";
           if(ps2x.ButtonPressed(PSB_PINK)) {
              squareButton = 1;
           } else if (ps2x.ButtonReleased(PSB_PINK)) {
              squareButton = 0;
           }            
           if (squareButton != lastSquareButton) {
              if (squareButton == 1) {
                  newSquareButton = "PRESSED";
              } else {
                  newSquareButton = "RELEASED";
              }
           } 
           
           newXButton = "";
           if(ps2x.ButtonPressed(PSB_BLUE)) { 
              xButton = 1;
           } else if (ps2x.ButtonReleased(PSB_BLUE)) {
              xButton = 0;
           } 
           if (xButton != lastXButton) {
               if (xButton == 1) {
                  newXButton = "PRESSED";
               } else {
                  newXButton = "RELEASED";
               } 
           } 
           
           
           /*
           if(ps2x.Button(PSB_L1) || ps2x.Button(PSB_R1)) // print stick values if either is TRUE
           {
               Serial.print("Stick Values:");
               Serial.print(ps2x.Analog(PSS_LY), DEC); //Left stick, Y axis. Other options: LX, RY, RX  
               Serial.print(",");
               Serial.print(ps2x.Analog(PSS_LX), DEC); 
               Serial.print(",");
               Serial.print(ps2x.Analog(PSS_RY), DEC); 
               Serial.print(",");
               Serial.println(ps2x.Analog(PSS_RX), DEC); 
           } 
           */
        }
      }
    }  
    
    void showData() {
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


  private:
    unsigned long timeout = 0;
    unsigned long ignoreTimeout = 0;
    int analogX = 0;
    int analogY = 0;
    int analogXR = 0;
    int analogYR = 0;
    int accelX = 0;
    int accelY = 0;
    int accelZ = 0;
    
    int lastTriangleButton = 0;
    int triangleButton     = 0;
    int lastXButton        = 0; 
    int xButton            = 0;
    int lastCircleButton   = 0;
    int circleButton       = 0;
    int lastSquareButton   = 0;
    int squareButton       = 0;
    int lastLeft           = 0; // 0 = Released, 1 = Pressed
    int leftButton         = 0; // 0 = Released, 1 = Pressed
    int lastRight          = 0; // 0 = Released, 1 = Pressed
    int rightButton        = 0; // 0 = Released, 1 = Pressed
    int lastFire           = 0; // 0 = Released, 1 = Pressed
    int fireButton         = 0; // 0 = Released, 1 = Pressed
    int xDirection         = 0; // 0 = Released, 1 = Left, 2 = Right
    int lastX              = 0; // 0 = Released, 1 = Left, 2 = Right
    int yDirection         = 0; // 0 = Released, 1 = Left, 2 = Right  
    int lastY              = 0; // 0 = Released, 1 = Up, 2 = Right
    int lastReleased       = 0; // 0 = Not Released, 1 = Released 
    int released           = 0; 
    int xRDirection        = 0; // 0 = Released, 1 = Left, 2 = Right
    int lastXR             = 0; // 0 = Released, 1 = Left, 2 = Right
    int yRDirection        = 0; // 0 = Released, 1 = Left, 2 = Right  
    int lastYR             = 0; // 0 = Released, 1 = Up, 2 = Right
    
};

#endif
