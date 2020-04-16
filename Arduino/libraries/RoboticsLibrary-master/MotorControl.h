#ifndef Motor_Control_h
#define Motor_Control_h
#include <Arduino.h>

class MotorControl  {
public:
  MotorControl ( int _leftForward, int _leftReverse, int _rightForward, int _rightReverse ) {
    leftForward  = _leftForward;
    leftReverse  = _leftReverse;
    rightForward = _rightForward;
    rightReverse = _rightReverse;
    
    // Set the lines connected to the H-Bridge to outputs.
    // These lines control the motors and are PWM capable outputs.
    pinMode (leftForward, OUTPUT); 
    pinMode (leftReverse, OUTPUT);
    pinMode (rightForward,OUTPUT);
    pinMode (rightReverse,OUTPUT);     
  };
  
  void goForward (int speed); 
  void goReverse (int speed);
  void goLeft(int speed);
  void goRight(int speed);
  void clearPins ();
  void forward (int speed );
  void reverse (int speed );
  
private:
  int leftForward;
  int leftReverse;
  int rightForward;
  int rightReverse;
};

class SingleMotor {
public:
  SingleMotor ( int _forward, int _reverse) {
    forwardPin  = _forward;
    reversePin  = _reverse;
    
    // Set the lines connected to the H-Bridge to outputs.
    // These lines control the motors and are PWM capable outputs.
    pinMode (forwardPin, OUTPUT); 
    pinMode (reversePin, OUTPUT);
    analogWrite (forwardPin, 0);
    analogWrite (reversePin, 0);
  };
  
  void clearPins () {
    analogWrite (forwardPin, 0);
    analogWrite (reversePin, 0);
  };
  void forward (int speed ) {
    analogWrite (reversePin, 0);   
    analogWrite (forwardPin, speed);
  };
  void reverse (int speed ) {
    analogWrite (forwardPin, 0);
    analogWrite (reversePin, speed);
  };
  void motorMove (String direction, String speed ) {
     int spd = 0;
     if (speed == "fast") {
       spd = 255;
     } else if (speed == "medium") {
       spd = 100;
     }
     if (spd == 0) {
       clearPins();
     } else { 
       if ((direction == "reverse") || (direction == "right")){ 
         reverse (spd);
       } else { // forward or left
         forward (spd);
       }  
     }
  };
  
private:
  int forwardPin;
  int reversePin;
};
#endif