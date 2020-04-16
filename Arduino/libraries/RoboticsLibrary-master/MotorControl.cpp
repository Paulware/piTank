#include "MotorControl.h"

#define HTIMEOUT 200 

// Stop both motors 
void MotorControl::clearPins () {
  analogWrite (leftForward, 0);
  analogWrite (leftReverse, 0);
  analogWrite (rightForward,0);
  analogWrite (rightReverse,0);
  delay (HTIMEOUT);
}

// 
// Move the robot forward
void MotorControl::goForward (int speed) {
  clearPins();
  if (speed > 255) {
    speed = 255;
  }
  analogWrite (leftForward, speed);
  analogWrite (rightForward, speed);
}

void MotorControl::goReverse(int speed) {
  clearPins();
  if (speed > 255) { 
    speed = 255;
  }
  analogWrite (leftReverse, speed);
  analogWrite (rightReverse, speed);
}

void MotorControl::goLeft (int speed) {
  clearPins();
  if (speed > 255) {
    speed = 255;
  }
  analogWrite (leftReverse,speed);
  analogWrite (rightForward,speed);
}

void MotorControl::goRight (int speed) {
  clearPins();
  if (speed > 255) {
    speed = 255;
  }
  analogWrite (leftForward,speed);
  analogWrite (rightReverse,speed);
}
