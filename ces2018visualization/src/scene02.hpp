//
//  scene02.hpp
//  OOPARTS2017
//
//  Created by scott on 2017/08/31.
//
//

#ifndef scene02_hpp
#define scene02_hpp

#include "ofMain.h"
#include "ofxTwistedRibbon.h"

class scene02 {
public:
    scene02(float _x, float _y, float _z, float _toY);
    float x, fromY, z, toY, y;
    void setup();
    void draw();
    void update(ofColor _cScene02, ofColor _cScene02p);
    void resetTimer();
    
    float easeOutCubic(float t, float b, float c, float d);
    float time, timeStamp;
    float easeEnd;
    float r;
    float distance;
    float noiseRate;
    float sp;
    ofColor cScene02, cScene02p;
    ofColor cPass(ofColor c, ofColor* p);
    float bri;
    float easeLinear(float t, float b, float c, float d);
    float cChangeEnd = 20;
    bool cbCChange;
    
    ofxTwistedRibbon *ribbon;
    ofVec3f position, stopPos;
    ofIcoSpherePrimitive ico;
};
#endif /* scene02_hpp */
