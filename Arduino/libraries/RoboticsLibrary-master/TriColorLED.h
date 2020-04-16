#ifndef Tri_Color_LED_h
#define Tri_Color_LED_h

#define GREEN 0
#define BLUE 1
#define RED 2
#define PURPLE 3
#define YELLOW 4
#define BLUEBLUE 5
#define WHITE 6
#define OFF 7
#define LASTCOLOR 7

class TriColorLED {
public:
  TriColorLED (int greenPin, int bluePin, int redPin) {
     
     colors[0] = greenPin;
     colors[1] = bluePin;
     colors[2] = redPin;
     
     for (int i=0; i<3; i++) {
        pinMode (colors[i], OUTPUT);
     }   
     off();     
  }; // constructor
  
  void showColors() {
    Serial.print ( "colors: {" );
    Serial.print ( colors[0] );
    Serial.print ( "," );
    Serial.print ( colors[1] );
    Serial.print ( "," );
    Serial.print ( colors[2] );
    Serial.println ( "}" );   
  }
  
  void policeLights (unsigned long _timeout = -1 ) {
     state = 1;
     if (_timeout != -1) { 
       stopTimeout = millis() + _timeout;
     }  
  };

  void off () {
     for (int i=0; i<3; i++) {
        digitalWrite (colors[i], 1); 
     }   
  }
  
  String currentColor () { 
     if (colorSelected == 0) {
       return "GREEN";
     } else if (colorSelected == 1) {
       return "BLUE";
     } else if (colorSelected == 2) {
       return "RED";
     } else {
       return "PURPLE";
     }
  }
  
  void cycleColors (unsigned long frequency) {    
    cycleFrequency = frequency;
    if (frequency == -1) { 
      cycleTimeout = -1;
    } else {
      cycleTimeout = millis() + cycleFrequency;   
    }      
  }
  
  void nextColor() {
     if (colorSelected == LASTCOLOR) {
       colorSelected = 0;
     } else {
       colorSelected = colorSelected + 1;
     }
     setColor (colorSelected);
  }
  
  void setColor (int which, unsigned long timeout = -1) {
     if (colorSelected != which) { 
        off();
        cycleTimeout = -1;
        if (which == PURPLE) { 
          digitalWrite (colors[BLUE], 0);
          digitalWrite (colors[RED], 0);
        } else if (which == YELLOW) { 
          digitalWrite (colors[GREEN], 0);
          digitalWrite (colors[RED], 0);
        } else if (which == BLUEBLUE) { 
          digitalWrite (colors[GREEN], 0);
          digitalWrite (colors[BLUE], 0);       
        } else if (which == WHITE) {
          digitalWrite (colors[GREEN], 0);
          digitalWrite (colors[BLUE], 0);       
          digitalWrite (colors[RED], 0);        
        } else if (which != OFF) { 
          digitalWrite (colors[which], 0);
        }
     }  
     colorSelected = which;     
     if (timeout == -1) {
        lastColor = which;
     } else {         
        stopTimeout = millis() + timeout;
     } 
  }; 
  
  void reset () {
     off();
     state = 0;
     stopTimeout = -1;
  }
  
  void update (void) {
     static unsigned long changeTimeout = 0;
     
     if (cycleTimeout != -1) {
        if (millis() > cycleTimeout) {
          nextColor();
          cycleTimeout = millis() + cycleFrequency;
        }  
     }
     
     if (stopTimeout != -1) { 
       if (stopTimeout != 0) { 
         if (millis() > stopTimeout) {
           stopTimeout = -1;
           setColor (lastColor);
         }  
       } 
     }
     
     switch (state) {
        case 1: 
           if (millis() > changeTimeout) {
             if (colorSelected == BLUE) {
                setColor (RED);
             } else {
                setColor (BLUE);
             }
             changeTimeout = millis() + 500;
           }
           break;
          
        default:        
           break;
     }
  };
private:
  int state = 0;
  int green = 5;
  int red = 4;
  int blue = 7;
  int colors[3];
  int colorSelected = 0;
  int lastColor = green;
  unsigned long stopTimeout = -1;  
  unsigned long cycleTimeout = -1;
  unsigned long cycleFrequency = -1;
};
#endif