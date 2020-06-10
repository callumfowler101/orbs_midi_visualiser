//
//  Orb.hpp
//  orcaVisualiser
//
//  Created by Callum Fowler on 16/05/2020.
//
#pragma once
#include "ofMain.h"

using namespace glm;

class Orb {
public:
    void setup(int vel, int chan, vector<int> _randomCellPos, int rowLength);
    void update();
    void draw(bool scatter, bool _randomCells);
    void drawOrb(vec2 pos);
    vec2 createRows(int _chan, int _rowLength);
    ofColor determineColor(int _chan);
    
private:
    int size;
    float innerAlpha, outerAlpha;
    vec2 randPos, groupPos, groupRandPos;
    ofColor color;
};

