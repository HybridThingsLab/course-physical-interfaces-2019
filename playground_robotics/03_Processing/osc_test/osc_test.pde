// libraries
import oscP5.*; // http://www.sojamo.de/oscP5
import netP5.*;

OscP5 oscP5;
NetAddress remoteLocation;
OscMessage message;
int receivedData;
int ledState = 0;
int counter;

void setup() {
  size(400, 400);
  frameRate(60);
  /* start oscP5, listening for incoming messages at port 8888 */
  oscP5 = new OscP5(this, 8888);

  /* myRemoteLocation is a NetAddress. a NetAddress takes 2 parameters,
   * an ip address and a port number. myRemoteLocation is used as parameter in
   * oscP5.send() when sending osc packets to another computer, device, 
   * application. usage see below. for testing purposes the listening port
   * and the port of the remote location address are the same, hence you will
   * send messages back to this sketch.
   */
  remoteLocation = new NetAddress("192.168.1.200", 9999);
}


void draw() {
  background(0);

  // turn led on/off
  // counter (just every 10 frames)
  counter++;
  if (counter>=10) {
    if (ledState==0) {
      message = new OscMessage("/led");
      message.add(1); // ID
      oscP5.send(message, remoteLocation);
      ledState = 1;
    } else {
      message = new OscMessage("/led");
      message.add(0); // ID
      oscP5.send(message, remoteLocation);
      ledState = 0;
    }
    counter = 0;
  }

  // show values received via osc
  fill(255);
  text("some random data: "+receivedData, 100, height/2);
}
/* incoming osc message are forwarded to the oscEvent method. */
void oscEvent(OscMessage theOscMessage) {
  if (theOscMessage.checkAddrPattern("/send")==true) {
    receivedData = theOscMessage.get(0).intValue();
  }
}
