#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetWindowPosition(0, 0);
    ofBackground(0);
    ofSetCircleResolution(64);
    
    for(int i=0; i<midi.getInPortList().size(); i++){
        midiDevices.push_back(midi.getInPortName(i));
    }
    
    scatterOrbs = false;
    debug = false;
    randomCells = false;
    visualMidiChanels = 8;
    
    randomiseCells();
    setGui();
    
    setMidiDevice(midiDevices[0]);
}
//--------------------------------------------------------------
void ofApp::setMidiDevice(string midiDevice){
    string device = midiDevice;
    midi.openPort(device);
    midi.addListener(this);
}
//--------------------------------------------------------------
void ofApp::update(){
    updateGui();
    for(int i=0; i<orbs.size(); i++){
        orbs[i].update();
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofPushStyle();
    for(int i=0; i<orbs.size(); i++){
        orbs[i].draw(scatterOrbs, randomCells);
    }
    ofPopStyle();
    
    if(debug){
        drawGui();
    }
    
}
//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if(key=='d'||key=='D') debug=!debug;
}
//--------------------------------------------------------------
void ofApp::randomiseCells(){
    randomCellPos.clear();
    int cellIdx[visualMidiChanels];
    for(int i=0; i<visualMidiChanels; i++){
        cellIdx[i] = i;
    }
    for(int i=0; i<visualMidiChanels; i++){
        int randomIdx = floor(ofRandom(visualMidiChanels));
        swap(cellIdx[i], cellIdx[randomIdx]);
    }
    for(int i=0; i<visualMidiChanels; i++){
        randomCellPos.push_back(cellIdx[i]);
    }
}
//--------------------------------------------------------------
void ofApp::exit() {
    midi.closePort();
    midi.removeListener(this);
}
//--------------------------------------------------------------
void ofApp::newMidiMessage(ofxMidiMessage &message){
    
    message.channel -= 1;
    
    string toFind = "Note On";
    string messageString = message.toString();
    
    if(messageString.find(toFind) != std::string::npos){
        if(message.channel < visualMidiChanels){
            Orb orb;
            orb.setup(message.velocity, message.channel, randomCellPos);
            orbs.push_back(orb);
        }
        else {
            switch(message.channel){
                case 8:
                    randomiseCellsBut->dispatchEvent();
                    break;
                case 9:
                    randomCellsTog->dispatchEvent();
                    if(randomCells) randomCellsTog->setChecked(true);
                    if(!randomCells) randomCellsTog->setChecked(false);
                    break;
                case 10:
                    scatterTog->dispatchEvent();
                    if(scatterOrbs) scatterTog->setChecked(true);
                    if(!scatterOrbs) scatterTog->setChecked(false);
                    break;
                default:
                    break;
            }
        }
    }
    
    if(orbs.size()>50) orbs.erase(orbs.begin());
}
//--------------------------------------------------------------
void ofApp::setGui(){
    fps = new ofxDatGuiFRM(0.5f);
    fps->setWidth(150, 75);
    fps->setPosition(5, 5);
    
    scatterTog = new ofxDatGuiToggle("Scatter", false);
    scatterTog->setWidth(150);
    scatterTog->setPosition(5, 30);
    scatterTog->onButtonEvent(this, &ofApp::onButtonEvent);
    
    randomCellsTog = new ofxDatGuiToggle("Random Cells", false);
    randomCellsTog->setWidth(150);
    randomCellsTog->setPosition(5, 55);
    randomCellsTog->onButtonEvent(this, &ofApp::onButtonEvent);
    
    randomiseCellsBut = new ofxDatGuiButton("Randomise");
    randomiseCellsBut->setWidth(150);
    randomiseCellsBut->setPosition(5, 80);
    randomiseCellsBut->onButtonEvent(this, &ofApp::onButtonEvent);
    
    vector<string> options;
    for(int i=0; i<midi.getInPortList().size(); i++){
        options.push_back(midi.getInPortName(i));
    }
    midiDeviceMenu = new ofxDatGuiDropdown(midiDevices[0], options);
    midiDeviceMenu->setWidth(150);
    midiDeviceMenu->setPosition(5, 105);
    midiDeviceMenu->onDropdownEvent(this, &ofApp::onDropdownEvent);
}
//--------------------------------------------------------------
void ofApp::updateGui(){
    fps->update();
    scatterTog->update();
    randomCellsTog->update();
    randomiseCellsBut->update();
    midiDeviceMenu -> update();
}
//--------------------------------------------------------------
void ofApp::drawGui(){
    fps->draw();
    scatterTog->draw();
    randomCellsTog->draw();
    randomiseCellsBut->draw();
    midiDeviceMenu -> draw();
}
//--------------------------------------------------------------
void ofApp::onButtonEvent(ofxDatGuiButtonEvent e){
    if(e.target == scatterTog){
        scatterOrbs=!scatterOrbs;
    }
    if(e.target == randomCellsTog){
        randomCells=!randomCells;
    }
    if(e.target == randomiseCellsBut){
        randomiseCells();
    }
}
//--------------------------------------------------------------
void ofApp:: onDropdownEvent(ofxDatGuiDropdownEvent e){
    setMidiDevice(midiDevices[e.child]);
}
