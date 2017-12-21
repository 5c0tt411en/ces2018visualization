//
//  particles.hpp
//  ces2018visualization
//
//  Created by scott on 2017/12/13.
//

#ifndef particles_h
#define particles_h


#include "pingPongBuffer.h"
#include "ofMain.h"

#define W 1920
#define H 1080

class particles {
public:
    particles();
    void setup();
    void draw(int ptSz);
    void update(float ptEmNoise, ofVec2f v, ofColor c, ofVec2f p, float ptTS, float ptSc, float ptSpXY, float ptSpZ);
    
    ofVboMesh particle;
    ofShader render, updatePos;
    pingPongBuffer pingPong;
    ofVec3f emitterPos, prevEmitterPos;
    int particleNum, texRes;
    bool showTex;
    ofColor parCol;
    float ptSz, audio, ptEmNoise, ptTS, ptSc, ptSpXY, ptSpZ;
    
    ofImage sparkImg;
    int     imgWidth, imgHeight;
};

#endif /* particles_hpp */

