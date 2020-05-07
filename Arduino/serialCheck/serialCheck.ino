void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println ( "Ready" );
}

void loop() {
   char ch;
   if (Serial.available()) {
      ch = Serial.read();
      Serial.print (ch);
   }
}
