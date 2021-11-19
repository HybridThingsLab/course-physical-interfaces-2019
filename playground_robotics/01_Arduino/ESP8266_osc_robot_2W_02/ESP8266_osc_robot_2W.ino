// documentation ESP8266: https://www.mikrocontroller-elektronik.de/nodemcu-esp8266-tutorial-wlan-board-arduino-ide/
// motorshield used: https://www.pololu.com/product/2511

// libraries
#include <ArduinoOSC.h> // https://github.com/hideakitai/ArduinoOSC
#include <Chrono.h> // https://github.com/SofaPirate/Chrono

// WiFi stuff
const char* ssid = "maschinenraum";
const char* pwd = "maschinenraum";
const IPAddress ip(192, 168, 1, 200);
const IPAddress gateway(192, 168, 1, 1);
const IPAddress subnet(255, 255, 255, 0);

// pins motorshield
int pinDir1 = D8;
int pinDir2 = D7;
int pinSpeed1 = D6;
int pinSpeed2 = D5;

// for ArduinoOSC
const char* host = "192.168.1.100";
const int recv_port = 9999;
const int send_port = 8888;

// Instanciate a chrono object.
Chrono replyChrono;
int timer = 16; // ms

/// drive motor
void driveMotor(int IDmotor, OscMessage m) {

  Serial.print("motor: ");
  Serial.print(IDmotor); Serial.print(" ");
  Serial.print(m.arg<int>(0)); Serial.print(" ");
  Serial.println(m.arg<int>(1));

  // control motors
  if (IDmotor == 0) {
    digitalWrite(pinDir1, m.arg<int>(0)); // direction
    analogWrite(pinSpeed1, m.arg<int>(1)); // on ESP PWM = 0-1023 instead of 0-255
  } else {
    digitalWrite(pinDir2, m.arg<int>(0)); // direction
    analogWrite(pinSpeed2, m.arg<int>(1)); // on ESP PWM = 0-1023 instead of 0-255
  }
}


void setup() {

  Serial.begin(115200);

  // WiFi stuff
  WiFi.begin(ssid, pwd);
  WiFi.config(ip, gateway, subnet);
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.print("WiFi connected, IP = "); Serial.println(WiFi.localIP());

  // pin modes
  pinMode(pinDir1, OUTPUT);
  pinMode(pinDir2, OUTPUT);

  // stop motor
  analogWrite(pinSpeed1, 0);
  analogWrite(pinSpeed2, 0);

  // osc messages
  OscWiFi.subscribe(recv_port,"/motor1", [](OscMessage & m) {
    driveMotor(0, m);
  });
  OscWiFi.subscribe(recv_port, "/motor2", [](OscMessage & m) {
    driveMotor(1, m);
  });

}


void loop() {

  OscWiFi.parse(); // should be called


  // check if chrono and send back whatever date via osc
  if (replyChrono.hasPassed(timer) ) {
    replyChrono.restart();
    //OscWiFi.send(host, send_port, "/send", analogRead(A0)); // all x ms  
  }

}
