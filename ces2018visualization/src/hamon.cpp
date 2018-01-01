//
//  hamon.cpp
//  ces2018visualization
//
//  Created by scott on 2017/12/25.
//

#include "hamon.h"

hamon::hamon(string _type, float _drawP, float _stay, float _erase) {
    type = _type;
    drawP = _drawP;
    stay = _stay;
    erase = _erase;
}

void hamon::setup() {
    string path = "pdfs/" + type + ofToString(int(ofRandom(1, 20))) + ".pdf";
    pdf.load(path);
    
    for (int i = 0; i < pdf.getNumPath(); i++){
        ofPath p = pdf.getPathAt(i);
        // pdf defaults to non zero winding which doesn't look so good as contours
        p.setPolyWindingMode(OF_POLY_WINDING_ODD);
        vector<ofPolyline>& lines = const_cast<vector<ofPolyline>&>(p.getOutline());
        for(int j=0;j<(int)lines.size();j++){
            outlines.push_back(lines[j].getResampledBySpacing(1));
        }
    }
    
    ofLog() << path << " loaded. size: " << pdf.getWidth() << ", " << pdf.getHeight() << endl;
}

void hamon::update() {
    time = ofGetElapsedTimef() - timeStamp;
    
    switch (stat) {
        case DRAW:
            if (time < drawP) step = easeOutCubic(time, 0., 1., drawP);
            if (time >= drawP) {
                stat = STAY;
                resetTimer();
            }
            break;
        case STAY:
            if (time >= stay) {
                stat = ERASE;
                resetTimer();
            }
            break;
        case ERASE:
            if (time < erase) step = easeOutCubic(time, 1., -1., erase);
            if (time >= erase) {
                stat = END;
                resetTimer();
            }
            break;
        case END:
            break;
    }
}

void hamon::draw() {
    ofSetColor(255);
    time = ofGetElapsedTimef() - timeStamp;
    
    ofPushMatrix();
    ofTranslate(W / 2, H / 2);
//    ofRotate(time * 360);
    float scale;
    if (type == "rr") scale = 10;
    else if (type == "r") scale = 9.5;
    else if (type == "s") scale = 3;
    else if (type == "p") scale = 2;
    ofScale(scale / 1.4, scale / 1.4, scale / 1.4);
    ofTranslate(-pdf.getWidth() / 2, -pdf.getHeight() / 2);
    if(true) {
        ofNoFill();
        for (int i = 0; i < (int)outlines.size(); i++){
            ofPolyline & line = outlines[i];
            
            int num = step * line.size();
            
            ofBeginShape();
            for (int j = 0; j < num; j++){
                ofVertex(line[j]);
            }
            ofEndShape();
        }
    } else {
        pdf.draw();
    }
    
    ofPopMatrix();
}

void hamon::resetTimer() {
    timeStamp = ofGetElapsedTimef();
}

float hamon::easeOutCubic(float t, float b, float c, float d) {
    t /= d ;
    t-- ;
    return (c*(t*t*t + 1) + b) ;
}
