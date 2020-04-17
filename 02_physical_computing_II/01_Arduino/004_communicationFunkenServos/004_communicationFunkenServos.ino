// import of Funken
#include <Funken.h> // find library here: https://github.com/astefas/Funken
#include <Servo.h>

// instantiation of Funken
Funken fnk;

// servos
Servo servo1;
Servo servo2;

/*
   THE SETUP
*/
void setup() {

  // init funken
  fnk.begin(115200, 0, 0); // higher baudrate for better performance
  fnk.listenTo("CONTROL", control);

  // init servos
  servo1.attach(6);
  servo2.attach(7);

}

/*
   THE LOOP
*/
void loop() {
  // needed to make FUNKEN work
  fnk.hark();
}

void control(char *c) {

  // get first argument
  char *token = fnk.getToken(c); // is needed for library to work properly, but can be ignored

  // drive servos
  int value1 = atoi(fnk.getArgument(c));
  int value2 = atoi(fnk.getArgument(c));

  servo1.write(value1);
  servo2.write(value2);

}
