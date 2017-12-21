#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetVerticalSync(true);
    ofSetFrameRate(60);
    
    loader.open("2017-12-21-13-30-00-769.abc");
    cam.setPosition(W / 2, H / 2, - 2000);
    
    for (int  i = 0; i < 50; i++) {
        randomPos[i] = ofVec3f(
                               ofRandom(W * 3 / 8,  W * 5 / 8),
                               ofRandom(H * 3 / 8,  H * 5 / 8),
                               ofRandom(- W / 8,  W / 8)
        );
    }
    
    ofDisableArbTex();
    sphereImg.load("images/glowSphere.png");
}

//--------------------------------------------------------------
void ofApp::update(){
    time = ofGetElapsedTimef() - timeStamp;
    loader.setTime(time);
    
    cam.lookAt(ofVec3f(W / 2, H / 2, 0.));
    ofVec3f pos;
    switch (mode) {
        case 1:
            pos = ofVec3f(
                          (4 + sin(time / 8)) * W /8,
                          H / 2 + 200,
                          (-1 * cos(time / 8)) * W / 8
                          );
            break;
        case 2:
            pos = ofVec3f(
                          W /2,
                          H / 2,
                          - W / 4
                          );
            break;
        case 3:
            pos = ofVec3f(
                          W /2,
                          H / 2  + 200,
                          0.
                          );
            break;
        case 4:
            pos = ofVec3f(
                          W / 2 - 250,
                          H / 2,
                          0.
                          );
            break;
        case 5:
            if (int(time * 100) % 200 == 0)
                randomNum = int(ofRandom(50));
            pos = ofVec3f(randomPos[randomNum]);
            break;
        default:
            break;
    }
    cam.setPosition(pos);
    
    ofSetWindowTitle(ofToString(ofGetFrameRate()));
    
    if (time >= loader.getMaxTime()) timeStamp = ofGetElapsedTimef();
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofBackgroundGradient(ofColor(10), ofColor(100));
    cam.begin();
    
    ofPushStyle();
        ofPushMatrix();
        ofTranslate(ofGetWidth() / 2, ofGetHeight() / 2);
        ofDrawGrid(100.0f, 100.0f, true, true, true, true);
        ofPopMatrix();
    ofPopStyle();
    
    
    
    ofPushStyle();
        ofPushMatrix();
        ofTranslate(ofGetWidth() / 2, ofGetHeight() / 2, - 300);
        ofSetColor(255);
        ofNoFill();
        ofDrawBox(0, 0, 0, 100, 30, 30);
        glEnable(GL_DEPTH_TEST);
        ofNoFill();
        vector<ofVec3f> pt;
        loader.get("/points", pt);
        glPointSize(1);
        glBegin(GL_POINTS);
        for (int i = 0; i < pt.size(); i++)
            glVertex3fv(pt[i].getPtr());
        glEnd();
        glDisable(GL_DEPTH_TEST);
        ofPopMatrix();
        ofPopStyle();
    
    cam.end();
    
    string s;
    s += "              name: " + ofToString(loader.getNames()) + '\n';
    s += "              time: " + ofToString(loader.getTime()) + '\n';
    s += "total point number: " + ofToString(pt.size()) + '\n';
    s += "        total time: " + ofToString(loader.getMaxTime()) + '\n';
    s += "          min time: " + ofToString(loader.getMinTime()) + '\n';
    
    ofDrawBitmapStringHighlight(s, 20, 20);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if (key == ' ') timeStamp = ofGetElapsedTimef();
    if (key == '1') mode = 1;
    if (key == '2') mode = 2;
    if (key == '3') mode = 3;
    if (key == '4') mode = 4;
    if (key == '5') mode = 5;
}

float ofApp::easeOutCubic(float t, float b, float c, float d) {
    t /= d ;
    t-- ;
    return (c*(t*t*t + 1) + b) ;
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
