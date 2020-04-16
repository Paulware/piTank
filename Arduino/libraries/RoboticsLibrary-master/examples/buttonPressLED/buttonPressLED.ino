#include <ButtonPress.h>
#include <TriColorLED.h>
TriColorLED led = TriColorLED (5,4,6); 
ButtonPress buttonPress = ButtonPress(16); // D16 = A2 
void setup() {
  // put your setup code here, to run once:
  Serial.begin (9600);
  Serial.println ( "Ready" );
  led.setColor (GREEN);
}

void loop() {  
  // put your main code here, to run repeatedly:
  if (buttonPress.buttonIsPressed() ) {
    led.setColor (RED);
  } else if (buttonPress.buttonIsReleased() ) {
    led.setColor (BLUE);
  } 
  buttonPress.update();
}
