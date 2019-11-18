var isConnected;
var socket;

var dataReceived;
var generalSpeed = 300;

// Global variable to store the classifier
var classifier;

// Label
var label = 'listening...';
var confidence = 0.0;

var soundModel = 'http://127.0.0.1:8080/tm-my-audio-model/';

function preload() {
	// Load the model
	classifier = ml5.soundClassifier(soundModel + 'model.json');
}

function setup() {
	createCanvas(500, 500);
	setupOsc(8888, 9999);

	console.log("start");
	// Start classifying
	// The sound model will continuously listen to the microphone
	classifier.classify(gotResult);

}

function draw() {
	background(0);
	fill(255);
	text("some random data: " + dataReceived, 100, height / 2);

}

// custom function motor
function controlMotor(ID, dir, speed) {
	socket.emit('message', ['/motor', ID, dir, speed]);
}


// keyboard interaction
function keyPressed() {
	switch (keyCode) {
		case 38:
			// forward
			// motor 1 + 2
			controlMotor(0, 0, generalSpeed);
			controlMotor(1, 1, generalSpeed);
			break;
		case 40:
			// backward
			// motor 1 + 2
			controlMotor(0, 1, generalSpeed);
			controlMotor(1, 0, generalSpeed);
			break;
		case 37:
			// left
			// motor 2
			controlMotor(1, 1, generalSpeed);
			break;
		case 39:
			// right
			// motor 1
			controlMotor(0, 0, generalSpeed);
			break;
	}
}
function keyReleased() {
	// stop
	// motor 1 + 2
	controlMotor(0, 0, 0);
	controlMotor(1, 0, 0);
}

// The model recognizing a sound will trigger this event
function gotResult(error, results) {
	if (error) {
		console.error(error);
		return;
	}
	// The results are in an array ordered by confidence.
	console.log(results[0]);
	label = results[0].label;
	confidence = results[0].condfidence;
	console.log(label);
	console.log(confidence); // maybe useful
	if(label == "hoch"){
		controlMotor(0, 0, generalSpeed);
		controlMotor(1, 1, generalSpeed);
	}
	if(label == "runter"){
		controlMotor(0, 1, generalSpeed);
		controlMotor(1, 0, generalSpeed);
	}
	if(label == "stop"){
		controlMotor(0, 0, 0);
		controlMotor(1, 0, 0);
	}
}

function receiveOsc(address, value) {
	//console.log("received OSC: " + address + ", " + value);

	if (address == '/send') {
		dataReceived = value[0];
	}
}

function setupOsc(oscPortIn, oscPortOut) {
	socket = io.connect('http://127.0.0.1:8081', { port: 8081, rememberTransport: false });
	socket.on('connect', function () {
		socket.emit('config', {
			server: { port: oscPortIn, host: '127.0.0.1' },
			client: { port: oscPortOut, host: '192.168.1.200' }
		});
	});
	socket.on('connect', function () {
		isConnected = true;
	});
	socket.on('message', function (msg) {
		if (msg[0] == '#bundle') {
			for (var i = 2; i < msg.length; i++) {
				receiveOsc(msg[i][0], msg[i].splice(1));
			}
		} else {
			receiveOsc(msg[0], msg.splice(1));
		}
	});
}


