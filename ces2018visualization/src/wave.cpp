//
//  wave.cpp
//  ces2018visualization
//
//  Created by scott on 2017/12/13.
//

#include "wave.h"

wave::wave() {
    
}

void wave::setup() {
//    ofEnableBlendMode(OF_BLENDMODE_ADD);
    shader.load("shaders/wave/shader");
    float planeScale = 0.3;
    int planeWidth = ofGetWidth() * planeScale;
    int planeHeight = ofGetHeight() * planeScale / 2;
    int planeGridSize = 20;
    int planeColums = 2 * planeWidth / planeGridSize;
    int planeRows = 2 * planeHeight / planeGridSize;
    
    plane.set(planeWidth, planeHeight, planeColums, planeRows, OF_PRIMITIVE_TRIANGLES);
}

void wave::update() {
    
}

void wave::draw(ofColor seaCol, int seaDM, float seaPS, float nFreq, float spY, float dHeight, bool seaModeAu, bool seaAu) {
//    ofEnableBlendMode(OF_BLENDMODE_ADD);
    tDrawM = 0;
    glPointSize(1 + seaPS);
    ofPushMatrix();
    float percentX = 0.0;
    percentX = ofClamp(percentX, 0, 1);
    
    ofSetColor(seaCol);
    
    shader.begin();
    
    shader.setUniform1f("time", ofGetElapsedTimef());
    shader.setUniform1f("nFreq", nFreq);
    shader.setUniform1f("speedY", speedY);
    shader.setUniform1f("dHeight", dHeight + audio * 500);
    
    // translate plane into center screen.
    float tx = ofGetWidth() / 2;
    float ty = 600;
    ofTranslate(tx, ty);
    
    // the mouse/touch Y position changes the rotation of the plane.
    float percentY = 0.75;
    float rotation = ofMap(percentY, 0, 1, -60, 60, true) + 60;
    ofRotate(80, 1, 0, 0);
    
    drawMode = 2;
    if (tDrawM) drawMode = (int)ofRandom(1, 4);
    switch (drawMode) {
        case 1:
            plane.drawWireframe();
            break;
        case 2:
            plane.drawFaces();
            ofSetColor(255);
//            plane.drawVertices();
            plane.drawWireframe();
            break;
        case 3:
            plane.drawVertices();
            break;
            
        default:
            break;
    }
    
    shader.end();
    ofPopMatrix();
}
