
#include <Arduino.h>
#include "ServoEasing.h" // This file is part of ServoEasing https://github.com/ArminJo/ServoEasing.
#include <Chrono.h> // https://github.com/SofaPirate/Chrono

// servo
int SERVO1_PIN = 6;
int SERVO2_PIN = 7;
int SERVO3_PIN = 8;
ServoEasing Servo1;
ServoEasing Servo2;
ServoEasing Servo3;

// Instanciate a chrono object.
Chrono controlChrono;
int timer = 2000;

// for testing
int state = 0;

void setup() {
  Serial.begin(9600);

  // Attach servos to pins
  Servo1.attach(SERVO1_PIN, DEFAULT_MICROSECONDS_FOR_0_DEGREE, DEFAULT_MICROSECONDS_FOR_180_DEGREE);
  Servo2.attach(SERVO2_PIN, DEFAULT_MICROSECONDS_FOR_0_DEGREE, DEFAULT_MICROSECONDS_FOR_180_DEGREE);
  Servo3.attach(SERVO3_PIN, DEFAULT_MICROSECONDS_FOR_0_DEGREE, DEFAULT_MICROSECONDS_FOR_180_DEGREE);
  Servo1.setEasingType(EASE_SINE_IN_OUT);
  Servo2.setEasingType(EASE_SINE_IN_OUT);
  Servo3.setEasingType(EASE_SINE_IN_OUT);

  // set initial position here
  Servo1.write(90);
  Servo2.write(90);
  Servo3.write(90);


}

void loop() {

  //Serial.println("running");

  // check if chrono
  if (controlChrono.hasPassed(timer) ) {
    controlChrono.restart();

    // servo easing test
    if (state == 0) {
      Servo1.startEaseTo(20, 60); // position, degrees per second
      Servo2.startEaseTo(20, 90); // position, degrees per second
      Servo3.startEaseTo(0, 30); // position, degrees per second
      // state
      state = 1;
      Serial.println("one");
    } else {
      Servo1.startEaseTo(160, 60);
      Servo2.startEaseTo(160, 90);
      Servo3.startEaseTo(180, 30);
      // state
      state = 0;
      Serial.println("two");
    }

  }

}
