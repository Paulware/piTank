#include <Wire.h>
#include <GFX.h>
#include <SSD1306.h>

#define OLED_RESET 4
SSD1306 display(OLED_RESET);

#if (SSD1306_LCDHEIGHT != 64)
#error("Height incorrect, please fix SSD1306.h!");
#endif

void setup()
{
  Serial.begin(9600);  // Used to type in characters
  Serial.println ( "OLED Ready" );
  delay (1000);
  
  // by default, we'll generate the high voltage from the 3.3v line internally! (neat!)
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);  // initialize with the I2C addr 0x3C (for the 128x32)
  // init done

  // Clear the buffer.
  display.clearDisplay(); 
  display.display();

  // Show the user that the display is ready
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0,0);
  display.println("Ready");
  display.display();
}

void loop() {
 static int x = 0;
  static int y = 0;
  char ch;
  String oneCh = " ";
  
  // when characters arrive over the serial port...
  if (Serial.available()) {
    // wait a bit for the entire message to arrive
    delay(100);
    // read all the available characters
    while (Serial.available() > 0) {
      ch = Serial.read();
      // display each character to the LCD
      if (ch == '^') {
        display.clearDisplay();
        display.display();
        display.setCursor (0,0);
      } else{
        oneCh [0] = ch;
        display.print(oneCh); 
        display.display();      
      }   
    }
  } 
}