//
//  wave.hpp
//  ces2018visualization
//
//  Created by scott on 2017/12/13.
//

#ifndef wave_h
#define wave_h

#include "ofMain.h"

class wave {
public:
    wave();
    void setup();
    void update();
    void draw(ofColor seaCol, int seaDM, float seaPS, float nFreq, float spY, float dHeight, bool seaModeAu, bool seaAu);
    
    ofShader shader;
    ofCylinderPrimitive plane;
    ofColor seaCol;
    int drawMode = 1, seaPS;
    bool tDrawM;
    float nFreq, speedY, dHeight, audio;
};

#endif /* wave_h */
