#include "ofxBarcodeReader.h"



ofxBarcodeReader::ofxBarcodeReader(ofxBarcodeReaderType _type, string _comPort, int _baudRate):
type(_type), comPort(_comPort) , baudRate(_baudRate){
    switch(type) {
        case HIDKeyboardDevice:
            ofAddListener(ofEvents().keyPressed, this, &ofxBarcodeReader::keyPressed);
            break;
        
        case SerialDevice:
            // if no port, auto select
            if (comPort == "") {
                for (auto d : serial.getDeviceList()) {
                    comPort = d.getDevicePath();
                    break;
                }
            }
            
            serial.setup(comPort, baudRate);
            
            ofAddListener(ofEvents().update, this, &ofxBarcodeReader::update);
            break;
        default:
            break;
    }
	initialized = true;
	pastKeyPressedSec = pastSerialReceiveSec = 0;
}


ofxBarcodeReader::~ofxBarcodeReader() {
	if (initialized) {
        switch(type) {
            case HIDKeyboardDevice:
                ofRemoveListener(ofEvents().keyPressed, this, &ofxBarcodeReader::keyPressed);
                break;
            case SerialDevice:
                serial.close();
                break;
            default:
                break;
        }
	}
}

void ofxBarcodeReader::addCharactor(char c) {
    if (c == OF_KEY_RETURN) {
        if (data != "") {
            barcodeReaded();
            data = "";
        }
    }
    
    // ascii charactor
    else if (33 <= c && c <= 126) {
        data += c;
    }
}

void ofxBarcodeReader::keyPressed(ofKeyEventArgs & key) {
	float now = ofGetElapsedTimef();
	float timeoutSec = 0.2;
	if (now - pastKeyPressedSec > timeoutSec) {
		data = "";
	}
    
    addCharactor(key.key);
    pastKeyPressedSec = now;
}

void ofxBarcodeReader::update(ofEventArgs &args) {
    float now = ofGetElapsedTimef();
    
    while (serial.available()) {
        addCharactor(serial.readByte());
        pastSerialReceiveSec = now;
    }
    
    if (data != "" && now - pastSerialReceiveSec > 0.1) {
        addCharactor(OF_KEY_RETURN);
    }
}

void ofxBarcodeReader::barcodeReaded() {
	ofxBarcodeEventArgs args;
	args.data = data;
	ofNotifyEvent(barcodeEvents, args);
}
