#pragma once

#include "ofMain.h"
#include "ofxMidi.h"
#include "ofxDatGui.h"
#include "Orb.h"

class ofApp : public ofBaseApp, public ofxMidiListener {
    public:
		void setup();
		void update();
		void draw();
        void exit();
        void keyPressed(int key);
        void newMidiMessage(ofxMidiMessage &message);
        void randomiseCells();
        void setMidiDevice(string midiDevice);
    
        void onButtonEvent(ofxDatGuiButtonEvent e);
        void onDropdownEvent(ofxDatGuiDropdownEvent e);
        void triggerToggle(ofxDatGuiToggle* toggle);
        void setGui();
        void updateGui();
        void drawGui();
    
        ofxMidiIn midi;
        vector <Orb> orbs;
        bool scatterOrbs, debug, randomCells, singleChannelMode;
        int visualMidiChannels;
        vector<int> randomCellPos;
        vector<string> midiDevices;
    
        //Parameters
        ofxDatGuiToggle* singleModeTog;
        ofxDatGuiToggle* scatterTog;
        ofxDatGuiToggle* randomCellsTog;
        ofxDatGuiButton* randomiseCellsBut;
        ofxDatGuiDropdown* midiDeviceMenu;
        ofxDatGuiFRM* fps;
};
