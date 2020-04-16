#include "Ultrasonic.h"

Ultrasonic ultrasonic(18,19); // TriggerPin, EchoPin
void setup() {
  Serial.begin ( 9600);
}

void loop()
{
  bool valid;
  long inches;
  if (ultrasonic.rangeChanged (valid, inches) ) {
    if (valid) {
      Serial.print ( "Inches: " );
      Serial.println ( inches );          
    } else {
      Serial.println ( "Invalid" );
    }
  }
}
