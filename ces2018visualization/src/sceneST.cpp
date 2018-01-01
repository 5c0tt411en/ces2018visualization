//
//  sceneST.cpp
//  OOPARTS2017
//
//  Created by scott on 2017/08/31.
//
//

#include "sceneST.hpp"

sceneST::sceneST() {
    
}

void sceneST::setup() {
    shader.load("shaders/sceneST/shader");
    float planeScale = 1.0;
    int planeWidth = W * planeScale;
    int planeHeight = H * planeScale;
    int planeGridSize = 5;
    int planeColums = planeWidth / planeGridSize;
    int planeRows = planeHeight / planeGridSize;
    
    cone.set(10, 2, 10, 10);
    
    offset = ofVec3f(W / 2, H / 2, 0);
    
    for (int i = 0; i < NUMST; i++) {
        points[i] = ofVec3f(
                            offset.x + ofRandom(-6000, 6000),
                            offset.y + ofRandom(-H / 2, H / 2),
                            offset.z + ofRandom(-6000, 6000)
                            );
        stCol[i] = ofColor(
                           120 + ofRandom(134),
                           120 + ofRandom(134),
                           120 + ofRandom(134)
                           );
        noiseRate[i] = ofRandom(10);
    }
}

void sceneST::update() {
    for (int i = 0; i < NUMST; i++) {
        points[i].x += (1 - ofNoise((ofGetElapsedTimef() + noiseRate[i])) * 2.0) * 10;
        points[i].z += (1 - ofNoise((ofGetElapsedTimef() + noiseRate[i])) * 2.0) * 10;
        points[i].y++;
        if (points[i].y >= H) {
            points[i].y -= H;
        }
    }
}

void sceneST::draw() {
    ofPushStyle();
    {
//        ofEnableBlendMode(OF_BLENDMODE_ADD);
        ofSetLineWidth(5);
        glPointSize(1 + seaPS);
        
        shader.begin();
        nFreq = 100.0;
        dHeight = 100.0;
        speedY = 0.0001;
        shader.setUniform1f("time", ofGetElapsedTimef() / 15.0);
        shader.setUniform1f("noise freqency", nFreq);
        shader.setUniform1f("speedY", speedY);
        shader.setUniform1f("dHeight", dHeight + audio * 500);
        
        for (int i = 0; i < NUMST; i++) {
            ofPushMatrix();
            // translate plane into center screen.
            ofTranslate(points[i]);
            switch (drawMode) {
                case 1:
                    cone.drawWireframe();
                    break;
                case 2:
                    ofSetColor(stCol[i]);
                    cone.drawFaces();
                    break;
                case 3:
                    cone.drawVertices();
                    break;
                    
                default:
                    break;
            }
            ofPopMatrix();
        }
        shader.end();
    }
    ofPopStyle();
    
}
