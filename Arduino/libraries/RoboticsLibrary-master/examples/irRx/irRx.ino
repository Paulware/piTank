//Includes
#include <IR.h>
#include <IRPipboy.h>
#include <TimerOne.h>

//Instantiations
IRPipboy irReceive12(12,20,&Timer1); // Receive pin = 12, tx pin not used

void callback() // Timer1 is set to 25 microsecond to balance PWM output
{
  static bool skip = false;
  skip = !skip;
  if (!skip)
    irReceive12.callback();
}

void setup () {
  Serial.begin (9600);
  Serial.println ("IR Receive Ready");
  irReceive12.init();
  Timer1.initialize (25);
  Timer1.attachInterrupt(callback,25);

}

void loop  () {
  int val = irReceive12.irValue();
  if (val != 0) {
    Serial.print ( "Received value" );
    Serial.println ( val );
  } 
  //Updates

}
