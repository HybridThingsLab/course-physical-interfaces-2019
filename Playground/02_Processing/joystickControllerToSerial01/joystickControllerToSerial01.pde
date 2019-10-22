import org.gamecontrolplus.gui.*; //http://lagers.org.uk/gamecontrol/download.html
import org.gamecontrolplus.*;
import net.java.games.input.*;
import processing.serial.*;

ControlIO control;
ControlDevice stick;
float px, py;
float px_smooth;
float py_smooth;

int lf = 10;    // Linefeed in ASCII
Serial myPort;  // The serial port

public void setup() {
  size(800, 800);
  // Initialise the ControlIO
  control = ControlIO.getInstance(this);
  // Find a device that matches the configuration file
  stick = control.getMatchedDevice("joystick");
  if (stick == null) {
    println("No suitable device configured");
    System.exit(-1); // End the program NOW!
  }

  // serial
  // List all the available serial ports
  printArray(Serial.list());
  // Open the port you are using at the rate you want:
  myPort = new Serial(this, Serial.list()[3], 9600);
  myPort.clear();
  
  delay(1000); // bugfix if serial not detected
  
}

// Poll for user input called from the draw() method.
public void getUserInput() {
  px = map(stick.getSlider("rx").getValue(), -1, 1, 0, width);
  py = map(stick.getSlider("ry").getValue(), -1, 1, 0, height);
  
  // smooth value
  px_smooth += (px - px_smooth)*1.0;//0.085;
  py_smooth += (py - py_smooth)*1.0;//0.085;
  //px_smooth += (px - px_smooth)*0.05;
  //py_smooth += (py - py_smooth)*0.05;
  
  int servo_x = int(map(px_smooth,0,width,180,0));
  int servo_y = int(map(py_smooth,0,height,0,180));
  
  // send values to serial port
    // send message
  myPort.write("CONTROL");
  myPort.write(" ");
  myPort.write(str(servo_x)); // send integer as string
  myPort.write(" ");
  myPort.write(str(servo_y)); // send integer as string
  myPort.write(lf); // line feed
  
}

public void draw() {
  getUserInput(); // Polling
  background(0);
  // Show position
  noStroke();
  fill(255);
  ellipse(px, py, 20, 20);
  fill(0,255,0);
  ellipse(px_smooth, py_smooth, 20, 20);
}
