#ifndef Piezo_h
#define Piezo_h
/*
#define  c3    7634
#define  d3    6803
#define  e3    6061
#define  f3    5714
#define  g3    5102
#define  a3    4545
#define  b3    4049
#define  c4    3816    // 261 Hz 
#define  d4    3401    // 294 Hz 
#define  e4    3030    // 329 Hz 
#define  f4    2865    // 349 Hz 
#define  g4    2551    // 392 Hz 
#define  a4    2272    // 440 Hz 
#define  a4s   2146
#define  b4    2028    // 493 Hz 
#define  c5    1912    // 523 Hz
#define  d5    1706
#define  d5s   1608
#define  e5    1517    // 659 Hz
#define  f5    1433    // 698 Hz
#define  g5    1276
#define  a5    1136
#define  a5s   1073
#define  b5    1012
#define  c6    955
 
#define  R     0      // Define a special note, 'R', to represent a rest
*/
#define NOTE_B0  31
#define NOTE_C1  33
#define NOTE_CS1 35
#define NOTE_D1  37
#define NOTE_DS1 39
#define NOTE_E1  41
#define NOTE_F1  44
#define NOTE_FS1 46
#define NOTE_G1  49
#define NOTE_GS1 52
#define NOTE_A1  55
#define NOTE_AS1 58
#define NOTE_B1  62
#define NOTE_C2  65
#define NOTE_CS2 69
#define NOTE_D2  73
#define NOTE_DS2 78
#define NOTE_E2  82
#define NOTE_F2  87
#define NOTE_FS2 93
#define NOTE_G2  98
#define NOTE_GS2 104
#define NOTE_A2  110
#define NOTE_AS2 117
#define NOTE_B2  123
#define NOTE_C3  131
#define NOTE_CS3 139
#define NOTE_D3  147
#define NOTE_DS3 156
#define NOTE_E3  165
#define NOTE_F3  175
#define NOTE_FS3 185
#define NOTE_G3  196
#define NOTE_GS3 208
#define NOTE_A3  220
#define NOTE_AS3 233
#define NOTE_B3  247
#define NOTE_C4  262
#define NOTE_CS4 277
#define NOTE_D4  294
#define NOTE_DS4 311
#define NOTE_E4  330
#define NOTE_F4  349
#define NOTE_FS4 370
#define NOTE_G4  392
#define NOTE_GS4 415
#define NOTE_A4  440
#define NOTE_AS4 466
#define NOTE_B4  494
#define NOTE_C5  523
#define NOTE_CS5 554
#define NOTE_D5  587
#define NOTE_DS5 622
#define NOTE_E5  659
#define NOTE_F5  698
#define NOTE_FS5 740
#define NOTE_G5  784
#define NOTE_GS5 831
#define NOTE_A5  880
#define NOTE_AS5 932
#define NOTE_B5  988
#define NOTE_C6  1047
#define NOTE_CS6 1109
#define NOTE_D6  1175
#define NOTE_DS6 1245
#define NOTE_E6  1319
#define NOTE_F6  1397
#define NOTE_FS6 1480
#define NOTE_G6  1568
#define NOTE_GS6 1661
#define NOTE_A6  1760
#define NOTE_AS6 1865
#define NOTE_B6  1976
#define NOTE_C7  2093
#define NOTE_CS7 2217
#define NOTE_D7  2349
#define NOTE_DS7 2489
#define NOTE_E7  2637
#define NOTE_F7  2794
#define NOTE_FS7 2960
#define NOTE_G7  3136
#define NOTE_GS7 3322
#define NOTE_A7  3520
#define NOTE_AS7 3729
#define NOTE_B7  3951
#define NOTE_C8  4186
#define NOTE_CS8 4435
#define NOTE_D8  4699

const PROGMEM uint16_t jamesMelody[] = {
NOTE_G4,NOTE_G4,0,NOTE_G4,NOTE_G4,0,NOTE_G4,NOTE_G4,NOTE_G4,NOTE_G4,NOTE_G4,

   NOTE_B3,NOTE_G3,NOTE_C4,NOTE_G3,NOTE_CS4,NOTE_G3,NOTE_C4,NOTE_G3,NOTE_B3,NOTE_G3,NOTE_C4,NOTE_G3,NOTE_CS4,NOTE_G3,NOTE_C4,NOTE_G3,

   NOTE_E4,NOTE_F4,NOTE_F4,NOTE_F4,NOTE_F4,NOTE_E4,NOTE_E4,NOTE_E4,

   NOTE_E4,NOTE_G4,NOTE_G4,NOTE_G4,NOTE_G4,NOTE_E4,NOTE_E4,NOTE_E4,

   //Introduction

  NOTE_E4,NOTE_F4,NOTE_F4,NOTE_F4,NOTE_F4,NOTE_E4,NOTE_E4,NOTE_E4,

  NOTE_E4,NOTE_G4,NOTE_G4,NOTE_G4,NOTE_G4,NOTE_E4,NOTE_E4,NOTE_E4,

  NOTE_E4,NOTE_F4,NOTE_F4,NOTE_F4,NOTE_F4,NOTE_E4,NOTE_E4,NOTE_E4,

  NOTE_E4,NOTE_G4,NOTE_G4,NOTE_G4,NOTE_G4,NOTE_E4,NOTE_E4,NOTE_E4,

  NOTE_DS5,NOTE_D5,NOTE_B4,NOTE_A4,NOTE_B4,

  NOTE_E4,NOTE_G4,NOTE_DS5,NOTE_D5,NOTE_G4,NOTE_B4,

  NOTE_B4,NOTE_FS5,NOTE_F5,NOTE_B4,NOTE_D5,NOTE_AS5,

  NOTE_A5,NOTE_F5,NOTE_A5,NOTE_DS6,NOTE_D6 
 
};

const PROGMEM uint16_t jamesTempo []  = {
  8, 8, 2, 8, 8, 2,16, 8,16, 8,
  8, 2, 4, 2, 4, 2, 4, 2, 4, 2,
  4, 2, 4, 2, 4, 2, 4, 8,16,16,
  8, 4, 8, 8, 8, 8,16,16, 8, 4,
  8, 8, 8, 8,16,16, 8, 4, 8, 8,
  8, 8,16,16, 8, 4, 8, 8, 8, 8,
 16,16, 8, 4, 8, 8, 8, 8,16,16,
  8, 4, 8, 8, 8, 8, 2, 8, 8, 1,
  8, 4, 8, 4, 8, 8, 8, 8, 4, 8,
  4, 8, 4, 8, 4, 8, 3 
};

const PROGMEM uint16_t tetrisMelody[] = {
  NOTE_E5, NOTE_E3, NOTE_B4, NOTE_C5, NOTE_D5, NOTE_E5, NOTE_D5, NOTE_C5,
  NOTE_B4, NOTE_A4, NOTE_A3, NOTE_A4, NOTE_C5, NOTE_E5, NOTE_A3, NOTE_D5,
  NOTE_C5, NOTE_B4, NOTE_E4, NOTE_G4, NOTE_C5, NOTE_D5, NOTE_E3, NOTE_E5,
  NOTE_E3, NOTE_C5, NOTE_A3, NOTE_A4, NOTE_A3, NOTE_A4, NOTE_A3, NOTE_B2,
  NOTE_C3, NOTE_D3, NOTE_D5, NOTE_F5, NOTE_A5, NOTE_C5, NOTE_C5, NOTE_G5,
  NOTE_F5, NOTE_E5, NOTE_C3, 0, NOTE_C5, NOTE_E5, NOTE_A4, NOTE_G4, NOTE_D5,
  NOTE_C5, NOTE_B4, NOTE_E4, NOTE_B4, NOTE_C5, NOTE_D5, NOTE_G4, NOTE_E5,
  NOTE_G4, NOTE_C5, NOTE_E4, NOTE_A4, NOTE_E3, NOTE_A4, 0,
  NOTE_E5, NOTE_E3, NOTE_B4, NOTE_C5, NOTE_D5, NOTE_E5, NOTE_D5, NOTE_C5,
  NOTE_B4, NOTE_A4, NOTE_A3, NOTE_A4, NOTE_C5, NOTE_E5, NOTE_A3, NOTE_D5,
  NOTE_C5, NOTE_B4, NOTE_E4, NOTE_G4, NOTE_C5, NOTE_D5, NOTE_E3, NOTE_E5,
  NOTE_E3, NOTE_C5, NOTE_A3, NOTE_A4, NOTE_A3, NOTE_A4, NOTE_A3, NOTE_B2,
  NOTE_C3, NOTE_D3, NOTE_D5, NOTE_F5, NOTE_A5, NOTE_C5, NOTE_C5, NOTE_G5,
  NOTE_F5, NOTE_E5, NOTE_C3, 0, NOTE_C5, NOTE_E5, NOTE_A4, NOTE_G4, NOTE_D5,
  NOTE_C5, NOTE_B4, NOTE_E4, NOTE_B4, NOTE_C5, NOTE_D5, NOTE_G4, NOTE_E5,
  NOTE_G4, NOTE_C5, NOTE_E4, NOTE_A4, NOTE_E3, NOTE_A4, 0,
  NOTE_E4, NOTE_E3, NOTE_A2, NOTE_E3, NOTE_C4, NOTE_E3, NOTE_A2, NOTE_E3,
  NOTE_D4, NOTE_E3, NOTE_GS2, NOTE_E3, NOTE_B3, NOTE_E3, NOTE_GS2, NOTE_E3,
  NOTE_C4, NOTE_E3, NOTE_A2, NOTE_E3, NOTE_A3, NOTE_E3, NOTE_A2, NOTE_E3,
  NOTE_GS3, NOTE_E3, NOTE_GS2, NOTE_E3, NOTE_B3, NOTE_E3, NOTE_GS2, NOTE_E3,
  NOTE_E4, NOTE_E3, NOTE_A2, NOTE_E3, NOTE_C4, NOTE_E3, NOTE_A2, NOTE_E3,
  NOTE_D4, NOTE_E3, NOTE_GS2, NOTE_E3, NOTE_B3, NOTE_E3, NOTE_GS2, NOTE_E3,
  NOTE_C4, NOTE_E3, NOTE_E4, NOTE_E3, NOTE_A4, NOTE_E3, NOTE_A2, NOTE_E3,
  NOTE_GS4, NOTE_E3, NOTE_GS2, NOTE_E3, NOTE_GS2, NOTE_E3, NOTE_GS2, NOTE_E3,
  NOTE_E5, NOTE_E3, NOTE_B4, NOTE_C5, NOTE_D5, NOTE_E5, NOTE_D5, NOTE_C5,
  NOTE_B4, NOTE_A4, NOTE_A3, NOTE_A4, NOTE_C5, NOTE_E5, NOTE_A3, NOTE_D5,
  NOTE_C5, NOTE_B4, NOTE_E4, NOTE_G4, NOTE_C5, NOTE_D5, NOTE_E3, NOTE_E5,
  NOTE_E3, NOTE_C5, NOTE_A3, NOTE_A4, NOTE_A3, NOTE_A4, NOTE_A3, NOTE_B2,
  NOTE_C3, NOTE_D3, NOTE_D5, NOTE_F5, NOTE_A5, NOTE_C5, NOTE_C5, NOTE_G5,
  NOTE_F5, NOTE_E5, NOTE_C3, 0, NOTE_C5, NOTE_E5, NOTE_A4, NOTE_G4, NOTE_D5,
  NOTE_C5, NOTE_B4, NOTE_E4, NOTE_B4, NOTE_C5, NOTE_D5, NOTE_G4, NOTE_E5,
  NOTE_G4, NOTE_C5, NOTE_E4, NOTE_A4, NOTE_E3, NOTE_A4, 0,
  NOTE_E5, NOTE_E3, NOTE_B4, NOTE_C5, NOTE_D5, NOTE_E5, NOTE_D5, NOTE_C5,
  NOTE_B4, NOTE_A4, NOTE_A3, NOTE_A4, NOTE_C5, NOTE_E5, NOTE_A3, NOTE_D5,
  NOTE_C5, NOTE_B4, NOTE_E4, NOTE_G4, NOTE_C5, NOTE_D5, NOTE_E3, NOTE_E5,
  NOTE_E3, NOTE_C5, NOTE_A3, NOTE_A4, NOTE_A3, NOTE_A4, NOTE_A3, NOTE_B2,
  NOTE_C3, NOTE_D3, NOTE_D5, NOTE_F5, NOTE_A5, NOTE_C5, NOTE_C5, NOTE_G5,
  NOTE_F5, NOTE_E5, NOTE_C3, 0, NOTE_C5, NOTE_E5, NOTE_A4, NOTE_G4, NOTE_D5,
  NOTE_C5, NOTE_B4, NOTE_E4, NOTE_B4, NOTE_C5, NOTE_D5, NOTE_G4, NOTE_E5,
  NOTE_G4, NOTE_C5, NOTE_E4, NOTE_A4, NOTE_E3, NOTE_A4, 0,
  NOTE_E4, NOTE_E3, NOTE_A2, NOTE_E3, NOTE_C4, NOTE_E3, NOTE_A2, NOTE_E3,
  NOTE_D4, NOTE_E3, NOTE_GS2, NOTE_E3, NOTE_B3, NOTE_E3, NOTE_GS2, NOTE_E3,
  NOTE_C4, NOTE_E3, NOTE_A2, NOTE_E3, NOTE_A3, NOTE_E3, NOTE_A2, NOTE_E3,
  NOTE_GS3, NOTE_E3, NOTE_GS2, NOTE_E3, NOTE_B3, NOTE_E3, NOTE_GS2, NOTE_E3,
  NOTE_E4, NOTE_E3, NOTE_A2, NOTE_E3, NOTE_C4, NOTE_E3, NOTE_A2, NOTE_E3,
  NOTE_D4, NOTE_E3, NOTE_GS2, NOTE_E3, NOTE_B3, NOTE_E3, NOTE_GS2, NOTE_E3,
  NOTE_C4, NOTE_E3, NOTE_E4, NOTE_E3, NOTE_A4, NOTE_E3, NOTE_A2, NOTE_E3,
  NOTE_GS4, NOTE_E3, NOTE_GS2, NOTE_E3, NOTE_GS2, NOTE_E3, NOTE_GS2, NOTE_E3 
}; 

const PROGMEM  uint16_t tetrisTempo []  = { 
  8, 8, 8, 8, 8, 16, 16, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8,
  8, 4, 8, 8, 16, 16, 8, 8, 8, 8, 8, 8, 8, 16, 16, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 4, 4,
  8, 8, 8, 8, 8, 16, 16, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8,
  8, 4, 8, 8, 16, 16, 8, 8, 8, 8, 8, 8, 8, 16, 16, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 4, 4,
  8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8,
  8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8,
  8, 8, 8, 8, 8, 16, 16, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8,
  8, 4, 8, 8, 16, 16, 8, 8, 8, 8, 8, 8, 8, 16, 16, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 4, 4,
  8, 8, 8, 8, 8, 16, 16, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8,
  8, 4, 8, 8, 16, 16, 8, 8, 8, 8, 8, 8, 8, 16, 16, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 4, 4,
  8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8,
  8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8,
 
};

const PROGMEM uint16_t nyanCatMelody[] = {
  NOTE_DS5, NOTE_E5, NOTE_FS5, 0, NOTE_B5, NOTE_E5, NOTE_DS5, NOTE_E5, NOTE_FS5, NOTE_B5, NOTE_DS6, NOTE_E6, NOTE_DS6, NOTE_AS5, NOTE_B5, 0,
  NOTE_FS5, 0, NOTE_DS5, NOTE_E5, NOTE_FS5, 0, NOTE_B5, NOTE_CS6, NOTE_AS5, NOTE_B5, NOTE_CS6, NOTE_E6, NOTE_DS6, NOTE_E6, NOTE_CS6,
  NOTE_FS4, NOTE_GS4, NOTE_D4, NOTE_DS4, NOTE_FS2, NOTE_CS4, NOTE_D4, NOTE_CS4, NOTE_B3, NOTE_B3, NOTE_CS4,
  NOTE_D4, NOTE_D4, NOTE_CS4, NOTE_B3, NOTE_CS4, NOTE_DS4, NOTE_FS4, NOTE_GS4, NOTE_DS4, NOTE_FS4, NOTE_CS4, NOTE_DS4, NOTE_B3, NOTE_CS4, NOTE_B3,
  NOTE_DS4, NOTE_FS4, NOTE_GS4, NOTE_DS4, NOTE_FS4, NOTE_CS4, NOTE_DS4, NOTE_B3, NOTE_D4, NOTE_DS4, NOTE_D4, NOTE_CS4, NOTE_B3, NOTE_CS4,
  NOTE_D4, NOTE_B3, NOTE_CS4, NOTE_DS4, NOTE_FS4, NOTE_CS4, NOTE_D4, NOTE_CS4, NOTE_B3, NOTE_CS4, NOTE_B3, NOTE_CS4,
  NOTE_FS4, NOTE_GS4, NOTE_D4, NOTE_DS4, NOTE_FS2, NOTE_CS4, NOTE_D4, NOTE_CS4, NOTE_B3, NOTE_B3, NOTE_CS4,
  NOTE_D4, NOTE_D4, NOTE_CS4, NOTE_B3, NOTE_CS4, NOTE_DS4, NOTE_FS4, NOTE_GS4, NOTE_DS4, NOTE_FS4, NOTE_CS4, NOTE_DS4, NOTE_B3, NOTE_CS4, NOTE_B3,
  NOTE_DS4, NOTE_FS4, NOTE_GS4, NOTE_DS4, NOTE_FS4, NOTE_CS4, NOTE_DS4, NOTE_B3, NOTE_D4, NOTE_DS4, NOTE_D4, NOTE_CS4, NOTE_B3, NOTE_CS4,
  NOTE_D4, NOTE_B3, NOTE_CS4, NOTE_DS4, NOTE_FS4, NOTE_CS4, NOTE_D4, NOTE_CS4, NOTE_B3, NOTE_CS4, NOTE_B3, NOTE_B3,
  NOTE_B3, NOTE_FS3, NOTE_GS3, NOTE_B3, NOTE_FS3, NOTE_GS3, NOTE_B3, NOTE_CS4, NOTE_DS4, NOTE_B3, NOTE_E4, NOTE_DS4, NOTE_E4, NOTE_FS4,
  NOTE_B3, NOTE_B3, NOTE_FS3, NOTE_GS3, NOTE_B3, NOTE_FS3, NOTE_E4, NOTE_DS4, NOTE_CS4, NOTE_B3, NOTE_E3, NOTE_DS3, NOTE_E3, NOTE_FS3,
  NOTE_B3, NOTE_FS3, NOTE_GS3, NOTE_B3, NOTE_FS3, NOTE_GS3, NOTE_B3, NOTE_B3, NOTE_CS4, NOTE_DS4, NOTE_B3, NOTE_FS3, NOTE_GS3, NOTE_FS3,
  NOTE_B3, NOTE_B3, NOTE_AS3, NOTE_B3, NOTE_FS3, NOTE_GS3, NOTE_B3, NOTE_E4, NOTE_DS4, NOTE_E4, NOTE_FS4, NOTE_B3, NOTE_AS3,
  NOTE_B3, NOTE_FS3, NOTE_GS3, NOTE_B3, NOTE_FS3, NOTE_GS3, NOTE_B3, NOTE_CS4, NOTE_DS4, NOTE_B3, NOTE_E4, NOTE_DS4, NOTE_E4, NOTE_FS4,
  NOTE_B3, NOTE_B3, NOTE_FS3, NOTE_GS3, NOTE_B3, NOTE_FS3, NOTE_E4, NOTE_DS4, NOTE_CS4, NOTE_B3, NOTE_E3, NOTE_DS3, NOTE_E3, NOTE_FS3,
  NOTE_B3, NOTE_FS3, NOTE_GS3, NOTE_B3, NOTE_FS3, NOTE_GS3, NOTE_B3, NOTE_B3, NOTE_CS4, NOTE_DS4, NOTE_B3, NOTE_FS3, NOTE_GS3, NOTE_FS3,
  NOTE_B3, NOTE_B3, NOTE_AS3, NOTE_B3, NOTE_FS3, NOTE_GS3, NOTE_B3, NOTE_E4, NOTE_DS4, NOTE_E4, NOTE_FS4, NOTE_B3, NOTE_CS4,
  NOTE_FS4, NOTE_GS4, NOTE_D4, NOTE_DS4, NOTE_FS2, NOTE_CS4, NOTE_D4, NOTE_CS4, NOTE_B3, NOTE_B3, NOTE_CS4,
  NOTE_D4, NOTE_D4, NOTE_CS4, NOTE_B3, NOTE_CS4, NOTE_DS4, NOTE_FS4, NOTE_GS4, NOTE_DS4, NOTE_FS4, NOTE_CS4, NOTE_DS4, NOTE_B3, NOTE_CS4, NOTE_B3,
  NOTE_DS4, NOTE_FS4, NOTE_GS4, NOTE_DS4, NOTE_FS4, NOTE_CS4, NOTE_DS4, NOTE_B3, NOTE_D4, NOTE_DS4, NOTE_D4, NOTE_CS4, NOTE_B3, NOTE_CS4,
  NOTE_D4, NOTE_B3, NOTE_CS4, NOTE_DS4, NOTE_FS4, NOTE_CS4, NOTE_D4, NOTE_CS4, NOTE_B3, NOTE_CS4, NOTE_B3, NOTE_CS4,
  NOTE_FS4, NOTE_GS4, NOTE_D4, NOTE_DS4, NOTE_FS2, NOTE_CS4, NOTE_D4, NOTE_CS4, NOTE_B3, NOTE_B3, NOTE_CS4,
  NOTE_D4, NOTE_D4, NOTE_CS4, NOTE_B3, NOTE_CS4, NOTE_DS4, NOTE_FS4, NOTE_GS4, NOTE_DS4, NOTE_FS4, NOTE_CS4, NOTE_DS4, NOTE_B3, NOTE_CS4, NOTE_B3,
  NOTE_DS4, NOTE_FS4, NOTE_GS4, NOTE_DS4, NOTE_FS4, NOTE_CS4, NOTE_DS4, NOTE_B3, NOTE_D4, NOTE_DS4, NOTE_D4, NOTE_CS4, NOTE_B3, NOTE_CS4,
  NOTE_D4, NOTE_B3, NOTE_CS4, NOTE_DS4, NOTE_FS4, NOTE_CS4, NOTE_D4, NOTE_CS4, NOTE_B3, NOTE_CS4, NOTE_B3, NOTE_B3,
  NOTE_B3, NOTE_FS3, NOTE_GS3, NOTE_B3, NOTE_FS3, NOTE_GS3, NOTE_B3, NOTE_CS4, NOTE_DS4, NOTE_B3, NOTE_E4, NOTE_DS4, NOTE_E4, NOTE_FS4,
  NOTE_B3, NOTE_B3, NOTE_FS3, NOTE_GS3, NOTE_B3, NOTE_FS3, NOTE_E4, NOTE_DS4, NOTE_CS4, NOTE_B3, NOTE_E3, NOTE_DS3, NOTE_E3, NOTE_FS3,
  NOTE_B3, NOTE_FS3, NOTE_GS3, NOTE_B3, NOTE_FS3, NOTE_GS3, NOTE_B3, NOTE_B3, NOTE_CS4, NOTE_DS4, NOTE_B3, NOTE_FS3, NOTE_GS3, NOTE_FS3,
  NOTE_B3, NOTE_B3, NOTE_AS3, NOTE_B3, NOTE_FS3, NOTE_GS3, NOTE_B3, NOTE_E4, NOTE_DS4, NOTE_E4, NOTE_FS4, NOTE_B3, NOTE_AS3,
  NOTE_B3, NOTE_FS3, NOTE_GS3, NOTE_B3, NOTE_FS3, NOTE_GS3, NOTE_B3, NOTE_CS4, NOTE_DS4, NOTE_B3, NOTE_E4, NOTE_DS4, NOTE_E4, NOTE_FS4,
  NOTE_B3, NOTE_B3, NOTE_FS3, NOTE_GS3, NOTE_B3, NOTE_FS3, NOTE_E4, NOTE_DS4, NOTE_CS4, NOTE_B3, NOTE_E3, NOTE_DS3, NOTE_E3, NOTE_FS3,
  NOTE_B3, NOTE_FS3, NOTE_GS3, NOTE_B3, NOTE_FS3, NOTE_GS3, NOTE_B3, NOTE_B3, NOTE_CS4, NOTE_DS4, NOTE_B3, NOTE_FS3, NOTE_GS3, NOTE_FS3,
  NOTE_B3, NOTE_B3, NOTE_AS3, NOTE_B3, NOTE_FS3, NOTE_GS3, NOTE_B3, NOTE_E4, NOTE_DS4, NOTE_E4, NOTE_FS4, NOTE_B3, NOTE_CS4
};
const PROGMEM  uint16_t nyanCatTempo []  = {
  16,16,16,16,16,16,16,16,16,16,
  16,16,16,16,16,16,16,16,16,16,
  16,16, 8,16,16,16,16,16,16,16,
  16, 8, 8,16,16,16,16,16,16, 8,
   8, 8, 8,16,16,16,16,16,16,16,
  16,16,16,16,16,16,16, 8, 8,16,
  16,16,16,16,16,16,16,16,16,16,
  16, 8,16,16,16,16,16,16,16,16,
   8, 8, 8, 8, 8,16,16,16,16,16,
  16, 8, 8, 8, 8,16,16,16,16,16,
  // 100
  16,16,16,16,16,16,16,16,16, 8,
   8,16,16,16,16,16,16,16,16,16,
  16,16,16, 8,16,16,16,16,16,16,
  16,16, 8, 8, 8, 8,16,16, 8,16,
  16,16,16,16,16,16,16,16,16, 8,
   8,16,16,16,16,16,16,16,16,16,
  16,16,16, 8,16,16, 8,16,16,16,
  16,16,16,16,16,16,16, 8,16,16,
  16,16,16,16,16,16,16,16, 8, 8,
   8,16,16, 8,16,16,16,16,16,16,
  //200 
  16,16,16,16, 8, 8,16,16,16,16,
  16,16,16,16,16,16,16,16, 8,16,
  16, 8,16,16,16,16,16,16,16,16,
  16,16, 8,16,16,16,16,16,16,16,
  16,16,16, 8, 8, 8, 8,16,16,16,
  16,16,16, 8, 8, 8, 8,16,16,16,
  16,16,16,16,16,16,16,16,16,16,
  16, 8, 8,16,16,16,16,16,16,16,
  16,16,16,16,16, 8,16,16,16,16,
  16,16,16,16, 8, 8, 8, 8, 8,16,
  //300
  16,16,16,16,16, 8, 8, 8, 8,16,
  16,16,16,16,16,16,16,16,16,16,
  16,16,16, 8, 8,16,16,16,16,16,
  16,16,16,16,16,16,16, 8,16,16,
  16,16,16,16,16,16, 8, 8, 8, 8,
  16,16, 8,16,16,16,16,16,16,16,
  16,16,16, 8, 8,16,16,16,16,16,
  16,16,16,16,16,16,16, 8,16,16,
   8,16,16,16,16,16,16,16,16,16,
  16, 8,16,16,16,16,16,16,16,16,
  //400
  16,16, 8, 8, 8,16,16, 8,16,16,
  16,16,16,16,16,16,16,16, 8, 8,
  16,16,16,16,16,16,16,16,16,16,
  16,16, 8,16,16, 8,16,16,16,16,
  16,16,16,16,16,16, 8,16,16,16,
  16,16,16,16,16,16,16,8,8
}; 
// Santa Claus is coming to town 
const PROGMEM  uint16_t jeopardyMelody []  = {
NOTE_C2, NOTE_F3, NOTE_C3, NOTE_A2,
	NOTE_C3, NOTE_F3, NOTE_C3,
	NOTE_C3, NOTE_F3, NOTE_C3, NOTE_F3,
	NOTE_AS3, NOTE_G3, NOTE_F3, NOTE_E3, NOTE_D3, NOTE_CS3,
	NOTE_C3, NOTE_F3, NOTE_C3, NOTE_A2, // the same again
	NOTE_C3, NOTE_F3, NOTE_C3,
	NOTE_AS3, 0, NOTE_G3, NOTE_F3,
	NOTE_E3, NOTE_D3, NOTE_CS3, NOTE_C3
};

const PROGMEM  uint16_t jeopardyTempo []  = {
 4,    4,    4,    4,
	4,    4,          2,
	4,    4,    4,    4,
	3,   8, 8, 8, 8, 8,
	4,    4,    4,    4, // the same again
	4,    4,          2,
	4, 8, 8,    4,    4,
	4,    4,    4,    4,
	0
};

// Santa Claus is coming to town 
const PROGMEM  uint16_t santaMelody []  = {
  NOTE_G4,
  NOTE_E4, NOTE_F4, NOTE_G4, NOTE_G4, NOTE_G4,
  NOTE_A4, NOTE_B4, NOTE_C5, NOTE_C5, NOTE_C5,
  NOTE_E4, NOTE_F4, NOTE_G4, NOTE_G4, NOTE_G4,
  NOTE_A4, NOTE_G4, NOTE_F4, NOTE_F4,
  NOTE_E4, NOTE_G4, NOTE_C4, NOTE_E4,
  NOTE_D4, NOTE_F4, NOTE_B3,
  NOTE_C4
};

const PROGMEM  uint16_t santaTempo []  = {
  8,
  8, 8, 4, 4, 4,
  8, 8, 4, 4, 4,
  8, 8, 4, 4, 4,
  8, 8, 4, 2,
  4, 4, 4, 4,
  4, 2, 4,
  1
};

// We wish you a merry Christmas
const PROGMEM  uint16_t merryMelody []  = {
  NOTE_B3, 
  NOTE_F4, NOTE_F4, NOTE_G4, NOTE_F4, NOTE_E4,
  NOTE_D4, NOTE_D4, NOTE_D4,
  NOTE_G4, NOTE_G4, NOTE_A4, NOTE_G4, NOTE_F4,
  NOTE_E4, NOTE_E4, NOTE_E4,
  NOTE_A4, NOTE_A4, NOTE_B4, NOTE_A4, NOTE_G4,
  NOTE_F4, NOTE_D4, NOTE_B3, NOTE_B3,
  NOTE_D4, NOTE_G4, NOTE_E4,
  NOTE_F4
};

const PROGMEM  uint16_t merryTempo []  = {
  4,
  4, 8, 8, 8, 8,
  4, 4, 4,
  4, 8, 8, 8, 8,
  4, 4, 4,
  4, 8, 8, 8, 8,
  4, 4, 8, 8,
  4, 4, 4,
  2
};

// jingle bells 
const PROGMEM  uint16_t jingleMelody []  = 
  {   
  NOTE_E5, NOTE_E5, NOTE_E5,
  NOTE_E5, NOTE_E5, NOTE_E5,
  NOTE_E5, NOTE_G5, NOTE_C5, NOTE_D5,
  NOTE_E5,
  NOTE_F5, NOTE_F5, NOTE_F5, NOTE_F5,
  NOTE_F5, NOTE_E5, NOTE_E5, NOTE_E5, NOTE_E5,
  NOTE_E5, NOTE_D5, NOTE_D5, NOTE_E5,
  NOTE_D5, NOTE_G5};   
const PROGMEM  uint16_t jingleTempo []  = 
  {   
  8, 8, 4, 8, 8, 4, 8, 8,  8,  8, 
  2, 8, 8, 8, 8, 8, 8, 8, 16, 16, 
  8, 8, 8, 8, 4, 4};

const PROGMEM  uint16_t shaveMelody []  = 
  { NOTE_C4, NOTE_G3, NOTE_G3, NOTE_A3, NOTE_G3, 0, NOTE_B3, NOTE_C4};   
  
const PROGMEM  uint16_t shaveTempo []  = 
  {8, 16, 16, 8, 8, 4, 8, 8};
  
const PROGMEM  uint16_t chargeMelody []  = 
  { NOTE_C3, NOTE_E3, NOTE_G3, NOTE_G3, 0, NOTE_E3, NOTE_G3};   
  
const PROGMEM  uint16_t chargeTempo []  = 
  {     16,    16,     16,       16,     16,  16,      4}; 
  
	 // Melody 1: Star Wars Imperial March
 const PROGMEM uint16_t starWarsMelody[] = {  
		NOTE_A4, 0,  NOTE_A4, 0,  NOTE_A4, 0, NOTE_F4, 0, NOTE_C5, 0,  NOTE_A4, 0,  
		NOTE_F4, 0, NOTE_C5, 0, NOTE_A4, 0,  NOTE_E5, 0, NOTE_E5, 0,  NOTE_E5, 0,  
		NOTE_F5, 0, NOTE_C5, 0,  NOTE_A4, 0, NOTE_F4, 0, NOTE_C5, 0, NOTE_A4, 0
	};
const PROGMEM uint16_t starWarsTempo[]  = {  
		6,  10,  6,  10, 6,  10,  10, 10, 20, 10, 6, 10, 
		10, 10, 20,  10, 3,  10,   6, 10,  6, 10, 6, 10, 
		10, 10, 20,  10, 6,  10, 	10, 10, 20, 10, 3, 10
	};
  
const PROGMEM uint16_t marioMelody [] =  { 
  NOTE_E7, NOTE_E7, 0, NOTE_E7, 0, NOTE_C7, NOTE_E7, 0,
  NOTE_G7, 0, 0,  0, NOTE_G6, 0, 0, 0, 
  NOTE_C7, 0, 0, NOTE_G6, 0, 0, NOTE_E6, 0, 
  0, NOTE_A6, 0, NOTE_B6, 0, NOTE_AS6, NOTE_A6, 0, 

  NOTE_G6, NOTE_E7, NOTE_G7, NOTE_A7, 0, NOTE_F7, NOTE_G7, 
  0, NOTE_E7, 0,NOTE_C7, NOTE_D7, NOTE_B6, 0, 0,
  NOTE_C7, 0, 0, NOTE_G6, 0, 0, NOTE_E6, 0, 
  0, NOTE_A6, 0, NOTE_B6, 0, NOTE_AS6, NOTE_A6, 0, 

  NOTE_G6, NOTE_E7, NOTE_G7, NOTE_A7, 0, NOTE_F7, NOTE_G7, 
  0, NOTE_E7, 0,NOTE_C7, NOTE_D7, NOTE_B6, 0, 0,
  NOTE_E7, NOTE_E7, 0, NOTE_E7, 0, NOTE_C7, NOTE_E7, 0, NOTE_G7
};   
     
//Mario main them tempo
const PROGMEM  uint16_t marioTempo []  = {
  12, 12, 12, 12, 12, 12, 12, 12,
  12, 12, 12, 12, 12, 12, 12, 12, 
  12, 12, 12, 12, 12, 12, 12, 12, 
  12, 12, 12, 12, 12, 12, 12, 12, 

  9, 9, 9,
  12, 12, 12, 12, 12, 12, 12, 12,
  12, 12, 12, 12, 12, 12, 12, 12,
  12, 12, 12, 12, 12, 12, 12, 12,
  12, 12, 12, 12,

  9, 9, 9,
  12, 12, 12, 12, 12, 12, 12, 12,
  12, 12, 12, 12, 12, 12, 12, 12, 
  12, 12, 12, 12, 12
};  
   

class Piezo {
public:
  // _piezoPin   = digital output pin that the "+" end of piezo is connected to
  // _msDuration = number of milliseconds that tone should continue (-1 = forever)
  Piezo (int _piezoPin, int _msDuration = 5000) {
    piezoPin = _piezoPin;   
    msDuration = millis() + _msDuration;  
    changeFrequency = millis() + 1;   
    pinMode(piezoPin, OUTPUT);//buzzer    
  }; // constructor
  
  void stop() {
    state = 0;
    noTone (piezoPin);
    msDuration = -1;
  }
  
  void siren () {
    state = 1;
    frequency = minFrequency;
    changeFrequency = 1;
  };
  
  void buzz(int targetPin, long frequency, long length) {
    long delayValue = 1000000/frequency/2; // calculate the delay value between transitions
    //// 1 second's worth of microseconds, divided by the frequency, then split in half since
    //// there are two phases to each cycle
    long numCycles = frequency * length/ 1000; // calculate the number of cycles for proper timing
    //// multiply frequency, which is really cycles per second, by the number of seconds to 
    //// get the total number of cycles to produce
    for (long i=0; i < numCycles; i++){ // for the calculated length of time...    
      digitalWrite(targetPin,HIGH); // write the buzzer pin high to push out the diaphram
      delayMicroseconds(delayValue); // wait for the calculated delay value
      digitalWrite(targetPin,LOW); // write the buzzer pin low to pull back the diaphram
      delayMicroseconds(delayValue); // wait again or the calculated delay value
    }
  }
  
  void upTone() { 
     if (currentTone < maxFrequency) { 
        currentTone = currentTone + 250;
     }   
     buzz (piezoPin, currentTone, 100 ); 
  }
  
  void downTone() { 
     if (currentTone > minFrequency) { 
       currentTone = currentTone - 250;
     }  
     buzz (piezoPin, currentTone, 100 ); 
  }
  
  void fireSound () {
    frequency = 1000;
    state = 2;
    msDuration = millis() + 400;
    changeFrequency = 1;
  };  
  
  void hitSound() {
    state = 5;
    frequency = maxFrequency;
    changeFrequency = 1;
    msDuration = millis() + 300;
  };
  
  void startSong (int whichSong ) {
    state = whichSong;
    noteCount = 0;
    msDuration = -1;
  } 

  // PLAY TONE  //
  // Pulse the speaker to play a tone for a particular duration
  void playTone(int toneM, long duration) {
    long elapsed_time = 0;
    int rest_count = 50; // Loop variable to increase Rest length (BLETCHEROUS HACK; See NOTES)  
    
    if (toneM > 0) { // if this isn't a Rest beat, while the tone has 
      //  played less long than 'duration', pulse speaker HIGH and LOW
      while (elapsed_time < duration) {
        if (Serial.available()) 
           break;
   
        digitalWrite(2,HIGH);
        delayMicroseconds(toneM / 2);
   
        // DOWN
        digitalWrite(2, LOW);
        delayMicroseconds(toneM / 2);
   
        // Keep track of how long we pulsed
        elapsed_time += (toneM);
      } 
    }
    else { // Rest beat; loop times delay
      for (int j = 0; j < rest_count; j++) { // See NOTE on rest_count
        delayMicroseconds(duration);  
      }                                
    }                                 
  }
  
  void noSong() {
     Serial.print ( "Done with Song" );
     Serial.println ( state );
     state = 0; // Done
     noTone (piezoPin);
  }  
  
  void playNote () {    
     unsigned int tempo;
     int noteDuration;
     tempo = getTempo (noteCount ); // pgm_read_word_near (shaveTempo + noteCount );    
     noteDuration = 1000 / tempo; 
     buzz(piezoPin, getNote(noteCount) ,noteDuration);            
     changeFrequency = millis() + (noteDuration * 1.3 );        
     noteCount = noteCount + 1;
  }
  
  void computing() {
    state = 3;
    msDuration = millis() + 1500;
    changeFrequency = 1;
  };
  
  void update (void) {
     switch (state) {
        case 1: // Police Siren
          tone(piezoPin, frequency);
          if (frequency == maxFrequency) {
            step = -1; // Go down
          } else if (frequency ==  minFrequency) {
            step = 1; // Go up    
          }                   
          if (millis() > changeFrequency) {
            changeFrequency = millis() + 1;
            frequency = frequency + step;
          }
          break;
          
        case 2: // fireSound
          if (millis() > changeFrequency) { 
            frequency = frequency + 40;
            tone(piezoPin, frequency);
            changeFrequency = millis() + 4;
          } 
          break;          
          
        case 3: // Computing
          if (millis() > changeFrequency) { 
            frequency = random (6000, 9000);
            tone(piezoPin, frequency);
            changeFrequency = millis() + 50;
          }  
          break;
                    
        case 4: // Movement
          if (millis() > changeFrequency) { 
            frequency = random (3000, 4000);
            tone(piezoPin, frequency);
            changeFrequency = millis() + 15;
          }  
          break;
          
        case 5: // HitSound
          tone(piezoPin, frequency);
          if (frequency >= maxFrequency) {
            step = -1; // Go down
          } else if (frequency <=  minFrequency) {
            step = 1; // Go up    
          }                   
          if (millis() > changeFrequency) {
            changeFrequency = millis() + 5;
            frequency = frequency + (step * 15);
          }
          break;
          
        case 6: // Mario Theme
          if (millis() > changeFrequency) {
             if (noteCount == 87) { // Last note has been played
                noSong ();
             } else {
                playNote ();
             }                    
          } 
          break;
          
        case 7: // Star Wars Theme
          if (millis() > changeFrequency) {
             if (noteCount == 36) { 
                noSong ();
             } else {
                playNote ();
             }                    
          }   
          break;          
       
        case 8: // Shave and a haircut 2 bits
          if (millis() > changeFrequency) {
             if (noteCount == 8) {
                noSong ();
             } else {
                playNote ();
             }                    
          }  
          break;
          
        case 9: // Jingle Bells
          if (millis() > changeFrequency) {
             if (noteCount == 26) { 
                noSong ();
             } else {
                playNote ();
             }                    
          }  
          break;
          
        case 10: // We wish you a merry christmas
          if (millis() > changeFrequency) {
             if (noteCount == 30) { 
                noSong ();
             } else {
                playNote ();
             }                    
          }  
          break;
          
        case 11: // Santa claus is coming to town
          if (millis() > changeFrequency) {
             if (noteCount == 28) { 
                noSong ();
             } else {
                playNote ();
             }                    
          }  
          break; 

        case 12: // Jeopardy
          if (millis() > changeFrequency) {
             if (noteCount == 32) { 
                noSong ();
             } else {
                playNote ();
             }                    
          }  
          break;         

        case 13: // nyan Cat
          if (millis() > changeFrequency) {
             if (noteCount == 459) { 
                noSong ();
             } else {
                playNote ();
             }                    
          }  
          break; 
          
        case 14: // tetris
          if (millis() > changeFrequency) {
             if (noteCount == 459) { 
                noSong ();
             } else {
                playNote ();
             }                    
          }  
          break;
          
        case 15: // James Bond
          if (millis() > changeFrequency) {
             if (noteCount == 97) { 
                noSong ();
             } else {
                playNote ();
             }                    
          }  
          break;         
          
        case 16: // Charge
          if (millis() > changeFrequency) {
             if (noteCount == 7) { 
                noSong ();
             } else {
                playNote ();
             }                    
          }  
          break;         
        default:        
           break;
     }

     if (msDuration != -1) {
       if (millis() > msDuration) {
         stop();               
       }
     } else {
       noTone (piezoPin);
     }
     
  };

  // Change these values for a different sound  0
  int minFrequency =  700; // Frequency of low tone
  int maxFrequency = 1100; // Frequency of high tone
  int state = 0;

private:
  int noteCount = 0;
  // Values set in the constructor
  int piezoPin;
  int timeout;
  unsigned long msDuration = -1;

  int frequency = minFrequency;
  int currentTone = minFrequency;
  int step = 1;
  unsigned long changeFrequency = 0;
  
  unsigned int getNote (int noteCount) { 
     unsigned int value = 0;

     switch (state) {
        case 6: // Mario Theme
           value = pgm_read_word_near (marioMelody + noteCount );
           break;
        case 7: // Star wars theme
           value = pgm_read_word_near (starWarsMelody + noteCount );
           break;
        case 8: // Shave and a haircut 
           value = pgm_read_word_near (shaveMelody + noteCount );
           break;
        case 9: // Jingle Bells
           value = pgm_read_word_near (jingleMelody + noteCount );
           break;
        case 10: // We wish you a merry christmas
           value = pgm_read_word_near (merryMelody + noteCount );
           break;
        case 11: // Santa claus is coming to town
           value = pgm_read_word_near (santaMelody + noteCount );
           break;           
        case 12: // Jeopardy
           value = pgm_read_word_near (jeopardyMelody + noteCount );
           break;           
        case 13: // Nyan Cat
           value = pgm_read_word_near (nyanCatMelody + noteCount );
           break;            
        case 14: // Tetris
           value = pgm_read_word_near (tetrisMelody + noteCount );
           break;            
        case 15: // James Bond
           value = pgm_read_word_near (jamesMelody + noteCount );
           break;            
        case 16: // Charge
           value = pgm_read_word_near (chargeMelody + noteCount );
           break;            
        default:
           break;
     }  
     
     return value;
  } 
  
  unsigned int getTempo (int noteCount) { 
     unsigned int value = 0;
  
     switch (state) {
        case 6: // Mario Theme 
           value = pgm_read_word_near (marioTempo + noteCount );
           break;
        case 7: // Star wars theme
           value = pgm_read_word_near (starWarsTempo + noteCount );
           break;
        case 8: // Shave and a haircut 
           value = pgm_read_word_near (shaveTempo + noteCount );
           break;
        case 9: // Jingle Bells 
           value = pgm_read_word_near (jingleTempo + noteCount );
           break;
        case 10: // We wish you a merry christmas
           value = pgm_read_word_near (merryTempo + noteCount );
           break;
        case 11: // Santa claus is coming to town
           value = pgm_read_word_near (santaTempo + noteCount );
           break;           
        case 12: // Jeopardy
           value = pgm_read_word_near (jeopardyTempo + noteCount );
           break;           
        case 13: // Nyan Cat
           value = pgm_read_word_near (nyanCatTempo + noteCount );
           break;           
        case 14: // Tetris
           value = pgm_read_word_near (tetrisTempo + noteCount );
           break;           
        case 15: // James Bond
           value = pgm_read_word_near (jamesTempo + noteCount );
           break;  
        case 16: // Charge
           value = pgm_read_word_near (chargeTempo + noteCount );
           break;           
        default:
           break;
     } 
     
     return value;
  } 
 
 
     
    // Melody 2: Star Wars Theme
	/*
    int swmelody2[19] = {  f4,  f4, f4,  a4s,   f5,  d5s,  d5,  c5, a5s, f5, d5s,  d5,  c5, a5s, f5, d5s, d5, d5s,   c5};
    int swbeats2[19]  = {  21,  21, 21,  128,  128,   21,  21,  21, 128, 64,  21,  21,  21, 128, 64,  21, 21,  21, 128 }; 
	*/
};
#endif