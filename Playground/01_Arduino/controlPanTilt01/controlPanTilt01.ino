#include <Servo.h>

Servo servo1;
Servo servo2;

int poti1 = 0;
int poti2 = 1;
int value1, value2;

void setup() {

  Serial.begin(9600);
  
  // init servos
  servo1.attach(6);
  servo2.attach(7);
}

void loop() {

  // read potis
  value1 = analogRead(poti1);  
  value2 = analogRead(poti2);    

  // map values potis (0-1023) to servo (0,180)
  value1 = map(value1, 0, 1023, 0, 180);   
  value2 = map(value2, 0, 1023, 0, 180);  

  // drive servos
  servo1.write(value1); 
  servo2.write(value2);   

  delay(15);

  Serial.print(value1);
  Serial.print(" ");
  Serial.println(value2);
                        
}
