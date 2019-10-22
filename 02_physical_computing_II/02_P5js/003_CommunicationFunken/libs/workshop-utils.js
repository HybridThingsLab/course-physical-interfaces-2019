
/*

Global variables to make our life easier

*/

var ctracker;
var videoInput;
var positions = [];
var canvas;

/*

Load & align the canvas to match the underlying html5 video element

*/

function loadCanvas(w, h) {
    canvas = createCanvas(w, h);
    canvas.position(0, 0);
}

/*

Load the capture device, align under the canvas & mute it to avoid audiofeedback

*/

function loadCamera() {
    // setup camera capture

    var device = {
        video: {
            deviceId: "e44ff24c96816ee76abdd516004266489c3c76545dfb8c8201c6ecd5968a9d05",
            groupId: "bcabff390e3e9049d70c309bacb9d0a318b35fc8e5db2807598572e6d5bc7219",
            kind: "videoinput",
            label: "HD Pro Webcam C920 (046d:082d)"
        }
    }

    videoInput = createCapture(VIDEO); // "device" Change this to video if external webcam not connected
    videoInput.size(400, 300);
    videoInput.position(0, 0);
    videoInput.id("v");
    var mv = document.getElementById("v");
    mv.muted = true;
}

/*

Load ClmTracker, apply to the video element

*/

function loadTracker() {
    // setup tracker
    ctracker = new clm.tracker();
    ctracker.init(pModel);
    ctracker.start(videoInput.elt);
}

/*

Get current face feature point positions. Should go into the draw() function

*/

function getPositions() {
    // get array of face marker positions [x, y] format
    positions = ctracker.getCurrentPosition();
}


/* 

Get current emotion predictions. Should go into the draw() function

*/

function getEmotions() {
    var cp = ctracker.getCurrentParameters();
    predictedEmotions = emotions.meanPredict(cp);
}

/*

Emotion-specific global variables

*/

delete emotionModel['disgusted'];
delete emotionModel['fear'];
var emotions = new emotionClassifier();
var predictedEmotions;
emotions.init(emotionModel);
var emotionData = emotions.getBlank();

