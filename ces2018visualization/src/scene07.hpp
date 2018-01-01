//
//  scene07.hpp
//  OOPARTS2017
//
//  Created by scott on 2017/09/09.
//
//

#ifndef scene07_hpp
#define scene07_hpp

#include "ofMain.h"

class scene07 {
public:
    scene07();
    void setup();
    void update();
    void draw(ofColor _cScene07);
    
    ofVboMesh	mVboBox;
    shared_ptr<ofShader>	mShdInstanced;
    ofTexture	mTexDepth;
    
    bool isShaderDirty;
    ofColor cScene07;
};

#endif /* scene07_hpp */
