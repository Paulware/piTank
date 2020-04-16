void setup() {
  // put your setup code here, to run once:
  Serial.begin (9600);
  pinMode (6,OUTPUT);
  Serial.println ( "Set 6 = 0" );
  digitalWrite (6,0);
  delay (2000);
  digitalWrite (6,1);
  pinMode (4,OUTPUT);
  Serial.println ( "Set 4 = 0" );
  digitalWrite (4,0);
  delay (2000);
  digitalWrite (4,1);
  pinMode (5,OUTPUT);
  Serial.println ( "Set 5 = 0" );
  digitalWrite (5,0);
  delay (2000);
  digitalWrite (5,1);
}

void loop() {
  // put your main code here, to run repeatedly:

}
