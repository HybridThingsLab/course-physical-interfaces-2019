
#include <Arduino.h>
#include "ServoEasing.h" // This file is part of ServoEasing https://github.com/ArminJo/ServoEasing.

int SERVO1_PIN = 6;

ServoEasing Servo1;

void setup() {
  Serial.begin(9600);

  // Attach servos to pins
  Servo1.attach(SERVO1_PIN, DEFAULT_MICROSECONDS_FOR_0_DEGREE, DEFAULT_MICROSECONDS_FOR_180_DEGREE);
  Servo1.setEasingType(EASE_CUBIC_IN_OUT);

}

void loop() {

  // Set servos to start position.
  //Servo1.write(160);
  //delay(500);

  Servo1.easeTo(20, 60);
  Serial.println("start");
  while (Servo1.isMovingAndCallYield()) {
    ; // no delays here to avoid break between forth and back movement

  }
  Serial.println("stop");

  delay(5000);

  Servo1.easeTo(160, 60);

  delay(5000);
  
}
