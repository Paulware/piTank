//Includes
#include <VirtualWire.h>

uint8_t buf[500];
uint8_t buflen = 500;

String msgReceived () {
  String msg = "";
  buf[0] = 0;
  if (vw_get_message(buf, &buflen)) { // Non-blocking
     buf[buflen] = 0;
  }
  msg = (String)(char *)&buf[0];
  return msg;
}


void setup () { // --- This runs once ---
  Serial.begin (9600);
  Serial.println ("Vx Ready");   
  vw_set_rx_pin (12);
  vw_setup(2000);
  vw_rx_start(); // Start the receiver PLL running  
}


void loop()   /*----( LOOP: RUNS CONSTANTLY )----*/
{  
   String msg;
   if (vw_have_message()){
      msg = msgReceived();
      Serial.print (msg); // Send data to other processor
   }
}