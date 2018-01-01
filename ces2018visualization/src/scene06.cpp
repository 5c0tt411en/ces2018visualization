//
//  scene06.cpp
//  OOPARTS2017
//
//  Created by scott on 2017/09/04.
//
//

#include "scene06.hpp"

scene06::scene06() {
    
}

void scene06::setup() {
    shader.load("shaders/scene06/shader");
    float planeScale = 10.0;
    int planeWidth = ofGetWidth() * planeScale;
    int planeHeight = ofGetHeight() * planeScale * 30;
    int planeGridSize = 20;
    int planeColums = planeWidth / planeGridSize;
    int planeRows = 0.1 * planeHeight / planeGridSize;
    
    plane.set(planeWidth, planeHeight, planeColums, planeRows, OF_PRIMITIVE_TRIANGLES);
}

void scene06::update() {

}

void scene06::draw(ofColor _cScene06) {
//    ofEnableBlendMode(OF_BLENDMODE_ADD);
    glPointSize(1 + tunnelPS);
    ofPushMatrix();
    float percentX = 0.0;
    percentX = ofClamp(percentX, 0, 1);
    
    ofSetColor(_cScene06);
    
    shader.begin();
    
    shader.setUniform1f("time", ofGetElapsedTimef());
    shader.setUniform1f("nFreq", nFreq);
    shader.setUniform1f("speedY", speedY);
    shader.setUniform1f("dHeight", dHeight + audio * 500);
    
    ofPushStyle();
    {
        // translate plane into center screen.
        float tx = ofGetWidth() / 2;
        float ty = 1200;
        ofTranslate(tx, ty);
        
        // the mouse/touch Y position changes the rotation of the plane.
        float percentY = 0.75;
        float rotation = ofMap(percentY, 0, 1, -60, 60, true) + 60;
        ofRotate(80, 1, 0, 0);
        
        if (tDrawM) drawMode = (int)ofRandom(1, 4);
        switch (drawMode) {
            case 1:
                plane.drawWireframe();
                break;
            case 2:
                ofSetColor(_cScene06);
                plane.drawFaces();
                ofSetColor(0,0,0);
                plane.drawWireframe();
                break;
            case 3:
                plane.drawVertices();
                break;
                
            default:
                break;
        }
    }
    ofPopStyle();
    shader.end();
    ofPopMatrix();
}
