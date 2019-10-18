import org.gamecontrolplus.gui.*;
import org.gamecontrolplus.*;
import net.java.games.input.*;

ControlIO control;
ControlDevice stick;
float px, py;

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
  // Setup a function to trap events for this button
  stick.getButton("SHADOW").plug(this, "dropShadow", ControlIO.ON_RELEASE);
}

// Poll for user input called from the draw() method.
public void getUserInput() {
  px = map(stick.getSlider("rx").getValue(), -1, 1, 0, width);
  py = map(stick.getSlider("ry").getValue(), -1, 1, 0, height);
}

// Event handler for the SHADOW button
public void dropShadow() {
  // Make sure we have the latest position
  getUserInput();
}

public void draw() {
  getUserInput(); // Polling
  background(255, 255, 240);
  // Show position
  noStroke();
  fill(255, 64, 64, 64);
  ellipse(px, py, 20, 20);
}
