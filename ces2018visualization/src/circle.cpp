//
//  circle.cpp
//  ces2018visualization
//
//  Created by scott on 2017/12/25.
//

#include "circle.h"

circle::circle(ofVec3f _v) {
    v.set(_v);
}

void circle::setup() {
    res = (int)ofRandom(3, 6);
}

void circle::update() {
    time = ofGetElapsedTimef() - timeStamp;
}

void circle::draw() {
    ofSetCircleResolution(res);
    time = ofGetElapsedTimef() - timeStamp;

    ofEnableBlendMode(OF_BLENDMODE_ADD);
    ofPushMatrix();
    ofTranslate(v.x, v.y, 0.);
    ofRotate(time * 360);
    ofSetColor(100, 100, 100, 255 * (1 - time));
    ofFill();
    ofDrawCircle(0, 0, 0, radius / 2);
    ofNoFill();
    ofSetLineWidth(3);
    for (int i = 0; i < 100; i++) {
        ofDrawCircle(0, 0, 0, radius * (1. + 0.015 * (i + 1)));
    }
    radius+=30;
    ofPopMatrix();
}

void circle::resetTimer() {
    timeStamp = ofGetElapsedTimef();
}
