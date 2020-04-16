#include <ArduinoNunchuk.h>
#include <IR.h>
#include <IRPipboy.h>
#include <TimerOne.h>

#define IRRECEIVEPIN 16
#define IRTRANSMITPIN 3

IRPipboy ir(IRRECEIVEPIN,IRTRANSMITPIN,&Timer1);
ArduinoNunchuk nunchuk = ArduinoNunchuk();

void setup()
{
  Serial.begin(9600);
  nunchuk.init();
  Serial.println ( "NunChuck IR Ready" ); 
}

// IR cmds: use 8 bits
// w s d a for direction
// k = fire 
void loop()
{ 
  if (nunchuk.newY == "UP") {
     Serial.println ( "Forward");
     ir.createFireSequence('w');
     ir.fireData();      
  } else if (nunchuk.newY == "DOWN") {
     Serial.println ( "Reverse");
     ir.createFireSequence('s');
     ir.fireData(); 
  } else if (nunchuk.newX == "LEFT") {
     Serial.println ( "Go Left");
     ir.createFireSequence('a');
     ir.fireData();      
  } else if (nunchuk.newX == "RIGHT") {
     Serial.println ( "Go Right");
     ir.createFireSequence('d');
     ir.fireData();      
  } else if (nunchuk.newX == "RELEASED") {
     Serial.println ( "X Released");
     ir.createFireSequence('0');
     ir.fireData();      
  } else if (nunchuk.newY == "RELEASED") {
     Serial.println ( "Y Released");
     ir.createFireSequence('0');
     ir.fireData();      
  } else if (nunchuk.newC == "PRESSED") {
     Serial.println ( "C Button pressed");
     ir.createFireSequence('k');
     ir.fireData();      
  } else if (nunchuk.newZ == "PRESSED") {
     Serial.println ( "Z Button pressed");
     ir.createFireSequence('k');
     ir.fireData();      
  }
   
  nunchuk.update();  
}
