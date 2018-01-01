//
//  scene02.cpp
//  OOPARTS2017
//
//  Created by scott on 2017/08/31.
//
//

#include "scene02.hpp"

scene02::scene02(float _x, float _fromY, float _z, float _toY) {
    x = _x;
    fromY = _fromY;
    z = _z;
    toY = _toY;
}

void scene02::setup() {
    ribbon = new ofxTwistedRibbon();
    distance = toY - fromY;
    noiseRate = ofRandom(200, 300.0);
    ico.set(10, 1);
    easeEnd = abs(distance) / 100;
}

void scene02::update(ofColor _cScene02, ofColor _cScene02p) {
    cScene02 = _cScene02;
    cScene02p = _cScene02p;
    time = ofGetElapsedTimef() - timeStamp;
    if (time <= easeEnd) {
        cbCChange = false;
        y = easeOutCubic(time, fromY, toY - fromY, easeEnd);
        r = easeOutCubic(time, 0, 360, easeEnd);
        sp = 1 - (time / easeEnd);
    }
    else {
        y = toY;
        sp = 0;
    }
    
    float radius = sin(ofGetElapsedTimef()) * 80 + 50;
    float speed = distance / 400;
    position.x  = sp * cos((ofGetElapsedTimef() / easeEnd  + noiseRate) * speed) * radius + sp * ofNoise((ofGetElapsedTimef() / easeEnd  + noiseRate) * speed) * radius + x;
    position.y  = y;
    position.z = sp * sin((ofGetElapsedTimef() / easeEnd  + noiseRate) * speed) * radius + sp * ofNoise((ofGetElapsedTimef() / easeEnd  + noiseRate) * speed) * radius / 10 + z;
    if (time <= easeEnd) ribbon->update(position, cScene02);
    
    if (time > easeEnd) {
        if (ribbon->points.size()) {
            ofColor tmpCol = cScene02p;
            for (int i = 0; i < ribbon->points.size(); i++) {
                if (i > bri - 20 && i < bri + 20) cPass(cScene02p, &ribbon->colors[i]);
                else cPass(cScene02, &ribbon->colors[i]);
            }
            bri++;
            if (bri > ribbon->points.size()) {
                bri = 0;
                cbCChange = true;
            }
        }
    }
}

void scene02::draw() {
//    ofPushStyle();
//    {
        ofEnableBlendMode(OF_BLENDMODE_ADD);
        ribbon->draw(cScene02);
//    }
//    ofPopStyle();
//
//    ofPushStyle();
//    {
        ofEnableBlendMode(OF_BLENDMODE_ALPHA);
        ofPushMatrix();
        if (time <= easeEnd) {
            ofTranslate(position);
            stopPos = position;
        }
        else ofTranslate(stopPos);
        ico.drawFaces();
        ofPopMatrix();
//    }
//    ofPopStyle();
}

void scene02::resetTimer() {
    timeStamp = ofGetElapsedTimef();
}

float scene02::easeOutCubic(float t, float b, float c, float d) {
    t /= d ;
    t-- ;
    return (c*(t*t*t + 1) + b) ;
}

//--------------------------------------------------------------
ofColor scene02::cPass(ofColor c, ofColor* p) {
    *p = c;
    return *p;
}

float scene02::easeLinear(float t, float b, float c, float d) {
    return (c*t/d + b) ;
}
