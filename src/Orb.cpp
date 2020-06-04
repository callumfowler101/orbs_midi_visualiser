//
//  Orb.cpp
//  orcaVisualiser
//
//  Created by Callum Fowler on 16/05/2020.
//

#include "Orb.h"
void Orb::setup(int vel, int chan, vector<int> _randomCellPos){
    //chan-=1;
    outerAlpha = 255;
    
    if(vel>0) innerAlpha = ofMap(vel, 0, 127, 100, 255, true);
    else innerAlpha = 0;
    
    randPos = vec2(ofRandom(ofGetWidth()), ofRandom(ofGetHeight()));
    groupRandPos = createRows(_randomCellPos[chan]);
    groupPos = createRows(chan);
    
    
    size = int(ofRandom(25,45));
    color = determineColor(chan);
}
vec2 Orb::createRows(int _chan){
    vec2 position, rowOffset;
    if(_chan<4) rowOffset = vec2(0, ofGetHeight()*0.5);
    else rowOffset = vec2(ofGetHeight()*0.5, ofGetHeight());
    
    int modChan = _chan%4;
    float groupX = ofMap(modChan, 0, 4, 0, ofGetWidth())+(150+ofRandom(-125,125));
    position = vec2(groupX, ofRandom(rowOffset.x, rowOffset.y));
    return position;
}


void Orb::update(){
    innerAlpha-=ofRandom(5);
    outerAlpha-=ofRandom(3);
}

void Orb::draw(bool scatter, bool _randomCells){
    if(scatter) drawOrb(randPos);
    else if(_randomCells) drawOrb(groupRandPos);
    else drawOrb(groupPos);
}

void Orb::drawOrb(vec2 pos){
    ofSetColor(color,outerAlpha);
    ofDrawCircle(pos, size);
    ofSetColor(0,innerAlpha);
    ofDrawCircle(pos, size*0.9);
}

ofColor Orb::determineColor(int _chan){
    ofColor _color;
    switch(_chan){
        case 0:
            _color = ofColor(102, 153, 255);
            break;
        case 1:
            _color = ofColor(255, 102, 204);
            break;
        case 2:
            _color = ofColor(153, 255, 102);
            break;
        case 3:
            _color = ofColor(255, 255, 102);
            break;
        case 4:
            _color = ofColor(255, 80, 80);
            break;
        case 5:
            _color = ofColor(204, 153, 255);
            break;
        case 6:
            _color = ofColor(26, 255, 209);
            break;
        case 7:
            _color = ofColor(128, 204, 255);
            break;
        default:
            break;
    }
    return _color;
}


