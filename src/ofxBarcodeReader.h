#pragma once
#include "ofMain.h"

struct ofxBarcodeEventArgs {
	string data;
};

enum ofxBarcodeReaderType {
    HIDKeyboardDevice,
    SerialDevice
};

class ofxBarcodeReader {
public:
	ofxBarcodeReader(ofxBarcodeReaderType _type = HIDKeyboardDevice, string _comPort = "", int _baudRate = 115200);
	~ofxBarcodeReader();

	ofEvent<ofxBarcodeEventArgs> barcodeEvents;
private:
	bool initialized;
    ofxBarcodeReaderType type;
	string data;
    void addCharactor(char c);
    
    // HID keyboard device mode
	void keyPressed(ofKeyEventArgs& key);
	void barcodeReaded();
    float pastKeyPressedSec;

    // serial mode
    void update(ofEventArgs &args);
    string comPort; // use only SerialDevice mode
    ofSerial serial;
    float pastSerialReceiveSec;
    int baudRate;
};

