void setup() {
  Serial.begin (9600);
  Serial.println ( "Ready");
  pinMode (A0,INPUT);
  
  // put your setup code here, to run once:

}

void loop() {
  // put your main code here, to run repeatedly:
  static int lastA0 = 0;
  int pin0 = digitalRead (A0);
  if (pin0 != lastA0) {
     Serial.println ( pin0);
     lastA0 = pin0;
     delay (100);
  }
}
