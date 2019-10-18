#include <Encoder.h> // https://www.arduinolibraries.info/libraries/encoder

// Change these pin numbers to the pins connected to your encoder.
//   Best Performance: both pins have interrupt capability
//   Good Performance: only the first pin has interrupt capability
//   Low Performance:  neither pin has interrupt capability
Encoder knob(6, 7);
//   avoid using pins with LEDs attached

void setup() {
  Serial.begin(9600);
  Serial.println("TwoKnobs Encoder Test:");
  knob.write(0);
}

long positionKnob = -999;

void loop() {
  long newValue;
  newValue = knob.read();
  if (newValue != positionKnob) {
    Serial.print("value = ");
    Serial.println(newValue);
    positionKnob = newValue;
  }
}
