//
//  scene06.hpp
//  OOPARTS2017
//
//  Created by scott on 2017/09/04.
//
//

#ifndef scene06_hpp
#define scene06_hpp

#include "ofMain.h"

class scene06 {
public:
    scene06();
    void setup();
    void update();
    void draw(ofColor _cScene06);
    
    ofShader shader;
    ofPlanePrimitive plane;
    ofColor cScene06;
    int drawMode = 2, tunnelPS;
    bool tDrawM = false;
    float nFreq = 0.1, speedY = 0.5, dHeight = 1200, audio;
};

#endif /* scene06_hpp */
