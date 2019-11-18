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
OscWiFi osc;
const char* host = "192.168.1.100";
const int recv_port = 9999;
const int send_port = 8888;

// Instanciate a chrono object.
Chrono replyChrono; 
int timer = 25;


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

  // ArduinoOSC
  osc.begin(recv_port);

  // pin modes
  pinMode(pinDir1, OUTPUT);
  pinMode(pinDir2, OUTPUT);

  // stop motor
  analogWrite(pinSpeed1, 0);
  analogWrite(pinSpeed2, 0);

  // osc messages
  osc.subscribe("/motor", [](OscMessage & m) {
    Serial.print("motor : ");
    Serial.print(m.ip()); Serial.print(" ");
    Serial.print(m.port()); Serial.print(" ");
    Serial.print(m.size()); Serial.print(" ");
    Serial.print(m.address()); Serial.print(" ");
    Serial.print(m.arg<int>(0)); Serial.print(" ");
    Serial.print(m.arg<int>(1)); Serial.print(" ");
    Serial.println(m.arg<int>(2));

    int IDmotor = m.arg<int>(0);

    // control motors
    if (IDmotor == 0) {
      digitalWrite(pinDir1, m.arg<int>(1));
      analogWrite(pinSpeed1, m.arg<int>(2)); // on ESP PWM = 0-1023 instead of 0-255
    } else {
      digitalWrite(pinDir2, m.arg<int>(1));
      analogWrite(pinSpeed2, m.arg<int>(2)); // on ESP PWM = 0-1023 instead of 0-255
    }


  });

}

void loop() {

  osc.parse(); // should be called

  
  // check if chrono and send back whatever date via osc
  if (replyChrono.hasPassed(timer) ) {
    replyChrono.restart();
    osc.send(host, send_port, "/send", (int)random(1000));
  }

}
