
/*-----( Import needed libraries )-----*/
#include <Wire.h>  // Comes with Arduino IDE
#include <LiquidCrystal_I2C.h>

/*-----( Declare Constants )-----*/
/*-----( Declare objects )-----*/
// set the LCD address to 0x27 for a 16 chars 2 line display
// A FEW use address 0x3F
// Set the pins on the I2C chip used for LCD connections:
//                    addr, en,rw,rs,d4,d5,d6,d7,bl,blpol
LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);  // Set the LCD I2C address
 
/*-----( Declare Variables )-----*/
//NONE
void setup()   /*----( SETUP: RUNS ONCE )----*/
{
  Serial.begin(9600);  // Used to type in characters
  Serial.println ( "LCD Ready" );
  delay (1000);

  lcd.begin(20,4);   // initialize the lcd for 20 chars 4 lines, turn on backlight
  lcd.backlight();   // backlight on  

//-------- Write characters on the display ------------------
// NOTE: Cursor Position: (CHAR, LINE) start at 0  
  lcd.setCursor(0,0);
  lcd.write("Ready");

}/*--(end setup )---*/


void loop()   /*----( LOOP: RUNS CONSTANTLY )----*/
{
  static int x = 0;
  static int y = 0;
  char ch;
  
  // when characters arrive over the serial port...
  if (Serial.available()) {
    // wait a bit for the entire message to arrive
    delay(100);
    // read all the available characters
    while (Serial.available() > 0) {
      ch = Serial.read();
      // display each character to the LCD
      if (ch == '^') {
        lcd.clear(); // Clear the screen 
        x = 0;
        y = 0;
      } else if ((ch != 10) && (ch != 13)) {
        if (x == 20) {
          x = 0;
          y = y + 1;
          if (y == 4) { 
            y = 0;                          
          }
        }
        lcd.setCursor (x,y);
        Serial.print (ch);
        lcd.write(ch);
        x = x + 1;
      }   
    }
  } 
}
