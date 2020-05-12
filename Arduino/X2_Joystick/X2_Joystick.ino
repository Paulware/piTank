
char leftSide = 'S';
char rightSide = 's';
char leftRightTurret = 'U';
char upDownTurret = 'u';
char fire = 'f';
unsigned long txTimeout = 0;
bool changed;

void setup () {
  pinMode (6,INPUT_PULLUP);  
  pinMode (2,INPUT_PULLUP);
  pinMode (3,INPUT_PULLUP);
  pinMode (4,INPUT_PULLUP);
  pinMode (5,INPUT_PULLUP);
  Serial.begin (9600);
  txTimeout = 1;
}

void readLeftRight() {
  static int last4 = 1;
  static int last5 = 1;
  static char value = 'U';  

  int val = digitalRead (4);

  if (val != last4) { 
    if (val == 0) {
       value = 'T'; 
    } else {
       value = 'U';
    }
    last4 = val;
  }

  val = digitalRead (5);
  if (val != last5) {
    if (val == 0) {
       value = 't';
    } else {
       value = 'U';
    }
  }
  leftRightTurret = value;    
}

void readJoystick() {
  int pins[] = {A1, A3};
  static int lastValues[] = {1,1};
  char returnValues [][3] = {{'l','S','L'},{'r','s','R'}};
  int value;
  int val;
  char returnValue = 0;
  int numJoysticks = 2; // Also = len(pins) 
  bool debugIt = false;
  int leftValue;
  int rightValue;
  for (int i=0; i<numJoysticks; i++) {
     if (i == 0) {
        value = analogRead (A1);
     } else { 
        value = analogRead (A3);
     }
     // value = analogRead ( pins[i] );
     val = 1;
     if (value > 700) {
        val = 2;
     } else if (value < 200) {
        val = 0;
     }
     if (i == 0) {
        leftValue = value;
     } else {
        rightValue = value;
     }

     if (val != lastValues[i] ) {
        lastValues[i] = val;
        returnValue = returnValues [i][val];
        changed = true;
        break;
     }
  }
  // Only update 1 changed value
  switch (returnValue) {
     case 0:
        break;
     case 'l':
     case 'L':
     case 'S':
        leftSide = returnValue;
        break;
    
     case 'r':
     case 'R':
     case 's':
        rightSide = returnValue;
        break;
     default:
        break;
  }

  if (debugIt) {
     Serial.print ( "[Left,Right] [" );
     Serial.print ( leftValue );
     Serial.print ( "," );
     Serial.print ( rightValue );
     Serial.println ( "]" );
  }
}

void loop () {
  static int lastD6 = 1;
  static int lastD2 = 1;
  static int lastD3 = 1;
  int val6 = digitalRead (6);
  int val2 = digitalRead (2);
  int val3 = digitalRead (3);
  int ch = 32;
  changed = false;
  
  if (val6 != lastD6) {
    lastD6 = val6;
    if (val6 == 0) { 
       fire = 'F';
    } else { 
       fire = 'f';
    }
    changed = true;
  }
  
  if (val2 != lastD2) {
    lastD2 = val2;
    if (val2 == 0) { 
      upDownTurret = 'V';
    } else {
      upDownTurret = 'u';
    }
    changed = true;
  }
 
  if (val3 != lastD3) {
    lastD3 = val3;
    if (val3 == 0) { 
       upDownTurret = 'V';
    } else {
       upDownTurret = 'u';
    }
    changed = true;
  }
  
  readLeftRight();
  readJoystick ();
  //if (changed) { 
  //  if (millis() < txTimeout) {
  //    txTimeout = millis() + 200;
   // }
  //}
  
  if (millis() > txTimeout){ 
    txTimeout = millis() + 200;

    Serial.print  (leftSide);
    Serial.print  (rightSide ); 
    Serial.print  (fire);
    Serial.print  (leftRightTurret);
    Serial.println  (upDownTurret);

  }
}
