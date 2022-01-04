#pragma once
#include "ofMain.h"

struct ofxBarcodeEventArgs {
	string data;
};

class ofxBarcodeReader {
public:
	ofxBarcodeReader();
	~ofxBarcodeReader();

	ofEvent<ofxBarcodeEventArgs> barcodeEvents;
private:
	bool initialized;
	long int pastKeyPressedFrameNum;
	string data;
	void keyPressed(ofKeyEventArgs& key);
	void barcodeReaded();
};

