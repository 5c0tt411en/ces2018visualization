#pragma once

#include "ofMain.h"

//#define DEBUG

#define W 1920
#define H 1080

#include "ofxGui.h"
#include "ofxPostProcessing.h"
#include "particles.h"
#include "wave.h"
#include "ofxSyphon.h"

class ofApp : public ofBaseApp{
    
public:
    void setup();
    void update();
    void draw();
    
    void keyPressed(int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y );
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void mouseEntered(int x, int y);
    void mouseExited(int x, int y);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);
    string getData(int row, int column);
    
    float time, timeStamp;
    
    enum State{
        WAIT,
        CDOWN,
        MOTION,
        VIS
    };
    
    State st;
    
    ofTrueTypeFont cdFont;
    int     countDown,
            cdMAX = 15,
            heartCount,
            acceCount,
            rriCount,
            rowMAX = 14,
            columnMAX = 2730,
            startHeart = 0,
            startAcce = 0,
            startRri = 0;
    bool    trigger;
    float   heart,
            acce,
            rri;
    
    string debLOG, cdFS;
    
    vector <string> splitString;
    
    ofxPanel gPanel1, gPanel2;
    ofParameter<float> ptSz1,
    ptEmNoise1,
    ptTS1,
    ptSc1,
    ptSpXY1,
    ptSpZ1,
    ptSz2,
    ptEmNoise2,
    ptTS2,
    ptSc2,
    ptSpXY2,
    ptSpZ2;
    
    particles* particles_ = new particles();
    wave* wave_ = new wave();
    ofFbo fbo;
    
    
    ofParameter<float> geoTh, geoY, geoWi, geoSp, camNz, easeEnd, ptSz, ptEmNoise, ptTS, ptSc, ptSpXY, ptSpZ, param01, param02, param03, param04, param05, param06, fNF, fNT, nFreq, spY, dHeight, tFreq, spT, tHeight, audioThreshold, audioPeakDecay, audioMaxDecay, audioLevel;
    ofParameter<ofColor> parCol01, geoCol, vertCol, jetCol, seaCol, logoCol, tunnelCol, mistCol, ribbonCol;
    ofParameter<int> funcNum, mistSz, jetSz, seaPS, tunnelPS;
    ofxToggle fxaa, bloom, dof, noiseW, pixelate, rgb, vts, hts, godRays, toon, zoomBl, rhl, bbp, sss, tScene01, tScene02, tScene03, tScene04, tScene05, tScene06, tScene07, tScene08, tScene09, tDebug, nodeCh, pp, tCam, egoLOGO, ptAu, geoAu, vertShapeAu, vertModeAu, vertAu, seaModeAu, tunnelModeAu, seaAu, tunnelAu, mistAu;
    ofxButton camMove, funcCh, modeCh, seaDM, tunnelDM;
    ofxLabel ppLabel, camLabel;
    
    ofxPostProcessing post;
    
    ofxToggle wvTF, ptclTF;
    
    ofVideoPlayer mg;
    
//    ofxSyphonClient client;
    
};

