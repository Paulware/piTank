#include <HealthRing.h>
HealthRing ring = HealthRing (7);
void setup() {
  ring.setHealth (5);
  Serial.begin (9600);
  Serial.println ( "Ready");  
}

void loop() {
  char ch;
  // put your main code here, to run repeatedly:
  if (Serial.available() ) {
    ch = Serial.read();
    switch (ch) {
      case '1': 
         ring.setHealth(1);
      break;

      case '2':
         ring.setHealth(2);
      break;
    }
  }
}
