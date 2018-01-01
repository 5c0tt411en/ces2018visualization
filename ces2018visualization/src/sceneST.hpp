//
//  sceneST.hpp
//  OOPARTS2017
//
//  Created by scott on 2017/08/31.
//
//

#ifndef sceneST_hpp
#define sceneST_hpp

#include "ofMain.h"

#define NUMST 2000

#define W 1920
#define H 1080

class sceneST {
public:
    sceneST();
    void setup();
    void update();
    void draw();
    
    ofShader shader;
    ofColor cSceneST;
    int drawMode = 2, seaPS;
    bool tDrawM;
    float nFreq, speedY, dHeight, audio;
    ofConePrimitive cone;
    ofVec3f points[NUMST];
    ofVec3f offset;
    ofColor stCol[NUMST];
    float noiseRate[NUMST];
};

#endif /* sceneST_hpp */
