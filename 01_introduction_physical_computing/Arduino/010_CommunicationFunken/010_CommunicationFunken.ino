// import of Funken
#include <Funken.h> // find library here: https://github.com/astefas/Funken

// instantiation of Funken
Funken fnk;

/*
   THE SETUP
*/
void setup() {

  // init funken
  fnk.begin(9600, 0, 0); // higher baudrate for better performance
  fnk.listenTo("WHATEVER", whatever);

}

/*
   THE LOOP
*/
void loop() {
  // needed to make FUNKEN work
  fnk.hark();
}

void whatever(char *c) {

  // get first argument
  char *token = fnk.getToken(c); // is needed for library to work properly, but can be ignored

  // send received values back for testing
  Serial.print("Arduino Board received: ");
  Serial.print(atoi(fnk.getArgument(c)));
  Serial.print(" ");
  Serial.print(fnk.getArgument(c));
  Serial.print(" ");
  Serial.println(atoi(fnk.getArgument(c)));

}
