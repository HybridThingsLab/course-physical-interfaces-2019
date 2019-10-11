int analogPin = 0; // potentiometer wiper (middle terminal) connected to analog pin 0 (=A0)
// outside leads to ground and +5V
int pwmPin = 9;
int val = 0;  // variable to store the value read
int mappedVal = 0;

void setup() {
}

void loop() {
  
  val = analogRead(analogPin);  // read the input pin
  mappedVal = map(val, 0, 1023, 0, 255); //// map val (0-1023) to PWM (0-255)
  analogWrite(pwmPin, mappedVal); // set brightness LED
  
}



 
