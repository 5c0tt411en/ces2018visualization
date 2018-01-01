//
//  heartBeat.cpp
//  ces2018visualization
//
//  Created by scott on 2017/12/25.
//

#include "heartBeat.h"

heartBeat::heartBeat() {
    
}

void heartBeat::setup() {
    maskFbo.allocate(W, H, GL_RGBA);
    maskedImage.load("images/heartBeat.jpg");
}

void heartBeat::update() {
    time = ofGetElapsedTimef() - timeStamp;
}

void heartBeat::draw() {
    time = ofGetElapsedTimef() - timeStamp;
    
    path.clear();
    path.lineTo(
                time * maskFbo.getWidth() / oneCycle,
                0
                );
    path.lineTo(
                time * maskFbo.getWidth() / oneCycle,
                maskFbo.getHeight()
                );
    path.lineTo(
                bWidth + time * maskFbo.getWidth() / oneCycle,
                maskFbo.getHeight()
                );
    path.lineTo(
                bWidth + time * maskFbo.getWidth() / oneCycle,
                0
                );
    path.lineTo(
                time * maskFbo.getWidth() / oneCycle,
                0
                );
    maskFbo.begin();
    ofClear(0, 0, 0, 0);
    path.draw();
    maskFbo.end();
    maskedImage.getTexture().setAlphaMask(maskFbo.getTexture());
    ofSetColor(255);
    maskedImage.draw(0, 0, W, H);
}

void heartBeat::resetTimer() {
    timeStamp = ofGetElapsedTimef();
}
