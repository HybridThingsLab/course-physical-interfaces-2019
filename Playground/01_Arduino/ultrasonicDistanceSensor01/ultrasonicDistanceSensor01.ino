// libraries
#include <NewPing.h> // via "Bibliothek verwalten"
#include <Chrono.h> // INCLUDE CHRONO LIBRARY : http://github.com/SofaPirate/Chrono

#define TRIGGER_PIN  11  // Arduino pin tied to trigger pin on the ultrasonic sensor.
#define ECHO_PIN     12  // Arduino pin tied to echo pin on the ultrasonic sensor.
#define MAX_DISTANCE 300 // Maximum distance we want to ping for (in centimeters). Maximum sensor distance is rated at 400-500cm.

NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE); // NewPing setup of pins and maximum distance.

// Instanciate a Chrono object.
Chrono sensorChrono;
int timerSensor = 50; // after how many ms measurement

// Smoothing
const int numReadings = 25; // je mehr, desto mehr Glättung
int readings[numReadings];      // the readings from the analog input
int readIndex = 0;              // the index of the current reading
int total = 0;                  // the running total
int average = 0;                // the average

void setup() {
  Serial.begin(9600);
}

void loop() {

  if (sensorChrono.hasPassed(timerSensor) ) { // returns true if it passed 100 ms since it was started
    sensorChrono.restart();  // restart the crono so that it triggers again later

    /*
      // smooth value
      // subtract the last reading:
      total = total - readings[readIndex];
      // read from the sensor:
      readings[readIndex] = sonar.ping_cm();
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
      average = total / numReadings;*/

    // hinweis
    // zuerst constrain und dann erst mapping funktion

    Serial.print("Ping: ");
    Serial.print(sonar.ping_cm()); // Send ping, get distance in cm and print result (0 = outside set distance range)
    Serial.println("cm");
  }

}
