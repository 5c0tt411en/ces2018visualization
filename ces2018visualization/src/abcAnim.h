//
//  abcAmin.hpp
//  ces2018visualization
//
//  Created by scott on 2017/12/24.
//

#ifndef abcAmin_h
#define abcAmin_h

#include "ofMain.h"
#include "pingPongBuffer.h"
#include "ofxAlembic.h"

#define W 1920
#define H 1080

class abcAnim {
    
public:
    abcAnim();
    void setup();
    void update(int _startShape, float _vel);
    void draw(int _ptSz);
    
    ofVboMesh particles;
    ofShader render, updatePos;
    ofEasyCam cam;
    pingPongBuffer pingPong;
    ofVec3f emitterPos, prevEmitterPos;
    int particleNum, texRes;
    int startShape = 1, rotatePattern;
    float rotateAngle;
    bool showTex;
    
    
    ofImage sparkImg;
    int     imgWidth, imgHeight;
    ofFbo   renderFBO;
    float ptSz = 10.0f;
    int width, height;
    
    ofxAlembic::Reader loader;
    float   time,
            timeStamp,
            vel;
};

#endif /* abcAmin_h */
