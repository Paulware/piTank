#ifndef Health_Ring_h
#define Health_Ring_h
#include <Adafruit_NeoPixel.h>


#define NUMPIXELS      12
#define BRIGHTNESS     50
Adafruit_NeoPixel pixels;

class HealthRing {
public:
  // repairRobotValue is set true if the unit is a repair robot
  HealthRing ( int dataPin){
    pixels = Adafruit_NeoPixel(NUMPIXELS, dataPin, NEO_GRB + NEO_KHZ800);
    pixels.begin();   
  }; // constructor

  
  void setRing (int startLed, int stopLed, int red, int green, int blue ) {
    for (int i=startLed; i<stopLed; i++) {
      pixels.setPixelColor(i, pixels.Color(red,green,blue)); 
      pixels.show();
    }
  }

  void setXRing(int numPixels, int green, int  red, int blue) {
    setRing (0,numPixels, green,red,blue); 
  }

  void setHealth (int health) {
     // validation of input
     if (health > 12) {
        health = 12;
     } else if (health < 0) {
        health = 0;
     } 
     setXRing (12, 0, BRIGHTNESS, 0); // Set all Red
     setXRing (health, BRIGHTNESS, 0, 0); // Set health to Green
  }
private:
  Adafruit_NeoPixel pixels;
};
#endif