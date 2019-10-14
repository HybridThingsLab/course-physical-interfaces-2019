import processing.serial.*;

int lf = 10;    // Linefeed in ASCII
String stringReceived = "";
Serial myPort;  // The serial port

void setup() {

  size(800, 600);

  // List all the available serial ports
  printArray(Serial.list());
  // Open the port you are using at the rate you want:
  myPort = new Serial(this, Serial.list()[3], 9600);
  myPort.clear();
  // Throw out the first reading, in case we started reading 
  // in the middle of a string from the sender.
  stringReceived = myPort.readStringUntil(lf);
  // wait a moment to make sure serial connection works
  delay(1000);
}

void draw() {

  // send message
  myPort.write("WHATEVER");
  myPort.write(" ");
  myPort.write(str(int(random(100)))); // send integer as string
  myPort.write(" ");
  myPort.write("YEAH"); // send string
  myPort.write(" ");
  myPort.write(str(int(random(100)))); // send integer as string
  myPort.write(10); // line feed

  // check if message received
  while (myPort.available() > 0) {
    stringReceived = myPort.readStringUntil(lf);
    if (stringReceived != null) {
      stringReceived = trim(stringReceived); // remove line feed
    }
  }

  // draw message
  background(255);
  fill(0);
  
  // use try catch if something unexpected happens
  try {
    text(stringReceived, 32, height/2);
  } 
  catch (NullPointerException e) {

  }
}
