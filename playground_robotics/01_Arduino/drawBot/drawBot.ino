// pins motorshield
int pinDir1 = 12;
int pinDir2 = 13;
int pinSpeed1 = 3;
int pinSpeed2 = 11;


void setup() {

  // pin modes
  pinMode(pinDir1, OUTPUT);
  pinMode(pinDir2, OUTPUT);

}

void loop() {

  // dir
  digitalWrite(pinDir1, HIGH);
  digitalWrite(pinDir2, HIGH);

  analogWrite(6, 100);

  // speedramp
  for (int i = 0; i < 255; i++) {
    analogWrite(pinSpeed1, i);
    analogWrite(pinSpeed2, i);
    delay(20);
  }

  // dir
  digitalWrite(pinDir1, LOW);
  digitalWrite(pinDir2, LOW);

  analogWrite(6, 255);

  // speedramp
  for (int i = 0; i < 255; i++) {
    analogWrite(pinSpeed1, i);
    analogWrite(pinSpeed2, i);
    delay(20);
  }

}
