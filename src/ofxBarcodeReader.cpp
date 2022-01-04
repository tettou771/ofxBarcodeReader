#include "ofxBarcodeReader.h"



ofxBarcodeReader::ofxBarcodeReader() {
	ofAddListener(ofEvents().keyPressed, this, &ofxBarcodeReader::keyPressed);

	initialized = true;
	pastKeyPressedFrameNum = 0;
}


ofxBarcodeReader::~ofxBarcodeReader() {
	if (initialized) {
		ofRemoveListener(ofEvents().keyPressed, this, &ofxBarcodeReader::keyPressed);
	}
}

void ofxBarcodeReader::keyPressed(ofKeyEventArgs & key) {
	long int now = ofGetFrameNum();
	int timeoutFrameNum = 2;
	if (now - pastKeyPressedFrameNum > timeoutFrameNum) {
		data = "";
	}

	if (key.key == OF_KEY_RETURN) {
		if (data != "") {
			barcodeReaded();
			data = "";
		}
	}
	else {
		data += key.key;
	}

	pastKeyPressedFrameNum = now;
}

void ofxBarcodeReader::barcodeReaded() {
	ofxBarcodeEventArgs args;
	args.data = data;
	ofNotifyEvent(barcodeEvents, args);
}
