#include <Servo.h>
#include <Funken.h> // find library here: https://github.com/astefas/Funken


Servo servo1;
Servo servo2;

int value1, value2;

// instantiation of Funken
Funken fnk;

void setup() {

  // init funken
  fnk.begin(57600, 0, 0); // higher baudrate for better performance
  fnk.listenTo("CONTROL", control);

  // init servos
  servo1.attach(6);
  servo2.attach(7);
}

void loop() {

  // needed to make FUNKEN work
  fnk.hark();

}


void control(char *c) {

    // get first argument
  char *token = fnk.getToken(c); // is needed for library to work properly, but can be ignored


  // read values
  value1 = atoi(fnk.getArgument(c));
  value2 = atoi(fnk.getArgument(c));

  // drive servos
  servo1.write(value1);
  servo2.write(value2);

}
