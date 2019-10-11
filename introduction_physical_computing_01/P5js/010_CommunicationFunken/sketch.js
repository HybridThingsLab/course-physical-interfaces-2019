var serial;
var latestData = "waiting for data";

function setup() {
    createCanvas(400, 400);

    serial = new p5.SerialPort();

    serial.list();
    
    var options = { baudrate: 9600}; // change the data rate to whatever you wish
    serial.open('/dev/tty.usbmodem144101', options);

    serial.on('connected', serverConnected);
    serial.on('list', gotList);
    serial.on('data', gotData);
    serial.on('error', gotError);
    serial.on('open', gotOpen);
    serial.on('close', gotClose);

}

function serverConnected() {
    print("Connected to Server");
}

function gotList(thelist) {
    print("List of Serial Ports:");

    for (let i = 0; i < thelist.length; i++) {
        print(i + " " + thelist[i]);
    }
}

function gotOpen() {
    print("Serial Port is Open");
}

function gotClose() {
    print("Serial Port is Closed");
    latestData = "Serial Port is Closed";
}

function gotError(theerror) {
    print(theerror);
}

function gotData() {
    let currentString = serial.readLine();
    trim(currentString);
    if (!currentString) return;
    //console.log(currentString);
    latestData = currentString;
}

function draw() {
    background(200);
    fill(0, 0, 0);
    text(latestData, 10, 10);


    // speak via FUNKEN protocoll
    serial.write("WHATEVER");
    serial.write(" ");
    serial.write(str(int(random(100)))); // send integer as string
    serial.write(" ");
    serial.write("YEAH"); // send string
    serial.write(" ");
    serial.write(str(int(random(100)))); // send integer as string
    serial.write(10); // line feed

}