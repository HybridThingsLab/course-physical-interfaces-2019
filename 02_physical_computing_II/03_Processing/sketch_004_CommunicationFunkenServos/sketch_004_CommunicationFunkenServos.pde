import processing.serial.*;

int lf = 10;    // Linefeed in ASCII
Serial myPort;  // The serial port

void setup() {

  size(800, 600);

  // List all the available serial ports
  printArray(Serial.list());
  // Open the port you are using at the rate you want:
  myPort = new Serial(this, Serial.list()[3], 115200);
  myPort.clear();
  // wait a moment to make sure serial connection works
  delay(1000);
}

void draw() {

  int value1 = mouseX;
  int value2 = mouseY;

  // map values
  value1 = int(map(value1, 0, width, 0, 180));
  value2 = int(map(value2, 0, height, 0, 180));


  // send message
  myPort.write("CONTROL");
  myPort.write(" ");
  myPort.write(str(value1)); // send integer as string
  myPort.write(" ");
  myPort.write(str(value2)); // send integer as string
  myPort.write(lf); // line feed*/


  // draw message
  background(255);
  fill(0);
}
