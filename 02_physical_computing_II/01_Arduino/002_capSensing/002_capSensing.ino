// libraries
#include <CapacitiveSensor.h> // https://github.com/PaulStoffregen/CapacitiveSensor

// cap senssor
CapacitiveSensor cs1 = CapacitiveSensor(7, 6);

// this block is executed one time when programm starts
void setup() {
  // init serial connection
  Serial.begin(9600);
}

// this block is executed in a loop after setup is called one time
void loop() {

  int total1 =  cs1.capacitiveSensor(30);

  Serial.println(total1);

  delay(10);

}
