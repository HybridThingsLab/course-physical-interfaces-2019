int dirPin1 = 12;
int dirPin2 = 13;

int speedMotor1 = 3;
int speedMotor2 = 11;

void setup() {
  // put your setup code here, to run once:
  pinMode(dirPin1, OUTPUT);
  pinMode(dirPin2, OUTPUT);

  // set direction
  digitalWrite(dirPin1, HIGH);
  digitalWrite(dirPin2, HIGH);
}

void loop() {

  // test run

  // ramp
  for (int i = 10; i < 255; i++) {
    analogWrite(speedMotor1, i);
    analogWrite(speedMotor2, i);
    delay(5);
  }

  // set direction
  digitalWrite(dirPin1, LOW);
  digitalWrite(dirPin2, HIGH);

  delay(1000);

  // set direction
  digitalWrite(dirPin1, HIGH);
  digitalWrite(dirPin2, HIGH);

}
