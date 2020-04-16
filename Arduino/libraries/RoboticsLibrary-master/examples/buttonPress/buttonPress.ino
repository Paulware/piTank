#include <ButtonPress.h>
ButtonPress buttonPress = ButtonPress(16); // D16 = A2 
void setup() {
  // put your setup code here, to run once:
  Serial.begin (9600);
  Serial.println ( "Ready" );
}

void loop() {  
  // put your main code here, to run repeatedly:
  if (buttonPress.buttonIsReleased() ) {
    Serial.println ( "Button was released" );
  } else if (buttonPress.buttonIsPressed() ) {
    Serial.println ( "Button was pressed" );
  }
  buttonPress.update();
}
