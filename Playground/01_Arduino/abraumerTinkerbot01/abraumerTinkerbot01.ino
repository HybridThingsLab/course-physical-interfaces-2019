/**

    To start the Arduino loop, press PLAY on Tinkerbot
*/

// librareis for modules
#include "TBMotor.h"
#include "TBIRSensor.h"
#include "TBPivot.h"
#include "TBTwister.h"

//init motors
TBMotor motor1(BLUE);
TBMotor motor2(MINT);

// init pivots
TBPivot pivot1(BLUE);

// init twister
TBTwister twister1(RED);

// init distance sensors
TBIRSensor sensorIR1(MINT);


void setup() {

  // init serial
  Serial.begin(9600);

  //Initial state of the motor module
  motor1.stop(); //stop the motor module
  motor2.stop(); //stop the motor module

}

void loop() {

  // reset position pivot and twister (could be moving later)
  pivot1.setPosition(130);
  twister1.setPosition(90);

  // read sensors
  int valueDistance1 = sensorIR1.getData(); // in theory: 0-180, but check values serial output for testing

  // output (uncomment for debugging)
  //Serial.println(valueDistance1);

  // drive motor (speed value 0-100)
  int motorSpeed = 30;
  motor1.start(CW, motorSpeed); //begin moving clockwise
  motor2.start(CCW, motorSpeed); //begin moving counter clockwise

  // check border table
  int thresholdBorder = 30; // test it!
  if (valueDistance1 <= thresholdBorder) {
    motor1.stop(); //stop the motor module
    motor2.stop(); //stop the motor module
    // drive backward
    motorSpeed = 60;
    motor1.start(CCW, motorSpeed); //begin moving clockwise
    motor2.start(CW, motorSpeed); //begin moving counter clockwise
    delay(200);
    // turn
    motor2.stop(); //stop the motor module
    motor1.start(CCW, motorSpeed); //begin moving clockwise
    delay(1500);
    motorSpeed = 30;
  }
}
