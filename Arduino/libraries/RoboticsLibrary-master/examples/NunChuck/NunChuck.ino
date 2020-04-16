#include <ArduinoNunchuk.h>
ArduinoNunchuk nunchuk = ArduinoNunchuk();

void setup()
{
  Serial.begin(9600);
  nunchuk.init();
  Serial.println ( "Ready" );  
}

void loop()
{
  int value;
  nunchuk.update();
  if (nunchuk.newY == "UP") {
     Serial.println ( "Forward");     
  } else if (nunchuk.newY == "DOWN") {
     Serial.println ( "Reverse");
  } else if (nunchuk.newX == "LEFT") {
     Serial.println ( "Go Left");      
  } else if (nunchuk.newX == "RIGHT") {
     Serial.println ( "Go Right");      
  } else if (nunchuk.newX == "RELEASED") {
     Serial.println ( "X Released");     
  } else if (nunchuk.newY == "RELEASED") {
     Serial.println ( "Y Released");     
  } else if (nunchuk.newC == "PRESSED") {
     Serial.println ( "C Button pressed");     
  } else if (nunchuk.newZ == "PRESSED") {
     Serial.println ( "Z Button pressed");     
  }
}
