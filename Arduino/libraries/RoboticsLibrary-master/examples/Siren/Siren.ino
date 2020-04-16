#include <TriColorLED.h>
#include <Piezo.h>
TriColorLED led = TriColorLED(15,13,7); 
// Setup the piezo 2 = pin, 4000 = milliseconds of sound duration
Piezo piezo = Piezo(2,  4000);
unsigned long timeout = 0;

void setup() {
  Serial.begin (9600);
  Serial.println ( "Ready" );
  led.policeLights();
  piezo.siren();
}
void loop() {
  led.update();
  piezo.update();
} 
