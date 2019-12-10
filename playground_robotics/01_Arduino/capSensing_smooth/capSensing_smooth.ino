// libraries
#include <CapacitiveSensor.h> // https://github.com/PaulStoffregen/CapacitiveSensor

const int numReadings = 5;

int readings[numReadings];      // the readings from the analog input
int readIndex = 0;              // the index of the current reading
int total = 0;                  // the running total
int average = 0;

// cap senssor
CapacitiveSensor cs1 = CapacitiveSensor(7, 6);

// this block is executed one time when programm starts
void setup() {
  // init serial connection
  Serial.begin(9600);

  // initialize all the readings to 0:
  for (int thisReading = 0; thisReading < numReadings; thisReading++) {
    readings[thisReading] = 0;
  }

}

// this block is executed in a loop after setup is called one time
void loop() {

  int total1 =  cs1.capacitiveSensor(30);

  // subtract the last reading:
  total = total - readings[readIndex];

  // read from the sensor:
  readings[readIndex] = total1;
  // add the reading to the total:
  total = total + readings[readIndex];
  // advance to the next position in the array:
  readIndex = readIndex + 1;

  // if we're at the end of the array...
  if (readIndex >= numReadings) {
    // ...wrap around to the beginning:
    readIndex = 0;
  }

  // calculate the average:
  average = total / numReadings;

  Serial.println(average);

  delay(1);

}
