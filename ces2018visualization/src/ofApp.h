#pragma once

#include "ofMain.h"

//modes macros
#define DEBUG
//#define PROTO

//WIDTH&HEIGHT
#define W 1920
#define H 1080

#define SHOST "169.254.216.219"
#define SPORT 10001

//classes
#include "particles.h"
#include "wave.h"
#include "abcAnim.h"
#include "circle.h"
#include "heartBeat.h"
#include "hamon.h"
#include "sceneST.hpp"
#include "scene06.hpp"
#include "scene07.hpp"
#include "scene02.hpp"
#include "hamonObj.h"
#include "hamonMov.h"

//addons
#include "ofxSyphon.h"
#include "ofxGui.h"
#include "ofxPostProcessing.h"
#include "ofxOsc.h"
#include "ofxKsmrFragmentFx.h"

class ofApp : public ofBaseApp{
    
public:
    void setup();
    void update();
    void draw();

    string getData(int row, int column);
    float easeInOutQuadratic(float t, float b, float c, float d);
    float easeInOutCubic(float t, float b, float c, float d);
    float easeInCubic(float t, float b, float c, float d);
    float easeOutCubic(float t, float b, float c, float d);
    float easeLinear(float t, float b, float c, float d);
    
    //states
    enum State{
        WAIT,
        CDOWN,
        HBEAT,
        MOTION,
        VIS
    };
    State st;
    
    ofTrueTypeFont cdFont;
    int     countDown,
            cdMAX = 60,
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
            rri,
            time,
            timeStamp,
            frame;
    
    string  debLOG,
            cdFS;
    
    vector <string> splitString,
                    items;
    
    ofVec4f v;
    
    ofImage testP;
    
    ofxPanel    gPanel1,
                gPanel2,
                gPanelP,
                gPanelFX;
    ofParameter <float> ptSz1,
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
    
    //classes
    particles* particles_ = new particles();
    wave* wave_ = new wave();
    abcAnim* abcAnim_ = new abcAnim();
    vector <circle*> circle_;
    vector <heartBeat*> heartBeat_;
    vector <hamon*> hamon_;
    vector <hamonObj*> hamonObj_;
    vector <scene02*> scene02_;
    sceneST* sceneST_ = new sceneST();
    scene06* scene06_ = new scene06();
    scene07* scene07_ = new scene07();
    vector <hamonMov*> hamonMov_;
    
    ofFbo   fbo;
    
    //addons
    ofxPostProcessing   post;
    
    ofFbo::Settings     setting;
    ofxKsmrFragmentFx   fx;
    
    ofxOscReceiver      receiver;
    ofxOscSender        sender;
    
    ofxSyphonClient     client;
    
    
    ofShader shader;
    
    ofVideoPlayer   mg,
                    hb;
    
    //GUI
    ofParameter <float> geoTh,
                        geoY,
                        chroma,
                        geoWi,
                        geoSp,
                        camNz,
                        easeEnd,
                        ptSz,
                        ptEmNoise,
                        ptTS,
                        ptSc,
                        ptSpXY,
                        ptSpZ,
                        param01,
                        param02,
                        param03,
                        param04,
                        param05,
                        param06,
                        fNF,
                        fNT,
                        nFreq,
                        spY,
                        dHeight,
                        tFreq,
                        spT,
                        tHeight,
                        audioThreshold,
                        audioPeakDecay,
                        audioMaxDecay,
                        audioLevel,
                        vel;
    ofParameter <ofColor>   parCol01,
                            geoCol,
                            vertCol,
                            jetCol,
                            seaCol,
                            logoCol,
                            tunnelCol,
                            mistCol,
                            ribbonCol,
                            cSceneST,
                            cScene06,
                            cScene07,
                            cScene02,
                            cScene02p;
    ofParameter <int>   funcNum,
                        mistSz,
                        jetSz,
                        seaPS,
                        tunnelPS,
                        shape,
                        ptSzABC;
    ofxToggle   bb,
                bloom,
                cont,
                conv,
                dofa,
                dof,
                edge,
                fsss,
                fxaa,
                gr,
                hts,
                kd,
                ld,
                lut,
                nw,
                pixel,
                rgbs,
                rh,
                ssao,
                toon,
                vts,
                zb,
                tScene01,
                tScene02,
                tScene03,
                tScene04,
                tScene05,
                tScene06,
                tScene07,
                tScene08,
                tScene09,
                tDebug,
                nodeCh,
                pp,
                tCam,
                egoLOGO,
                ptAu,
                geoAu,
                vertShapeAu,
                vertModeAu,
                vertAu,
                seaModeAu,
                tunnelModeAu,
                seaAu,
                tunnelAu,
                mistAu,
                wvTF,
                ptclTF,
                abcTF,
                tSceneST,
                tGrid,
                fNoise,
                fEdge,
                fFringe,
                fInvert,
                fSShift,
                fTexChip,
                fVertNoise,
                fVertSlide,
                fWater;
    ofxButton   camMove,
                funcCh,
                modeCh,
                seaDM,
                tunnelDM;
    ofxLabel    ppLabel,
                camLabel;
    
    ofCamera cam;
    ofVec3f pointToView, camPos;
    ofVec3f camShiftFrom, camShiftTo, nodeShiftFrom, nodeShiftTo, camNoise, camPass;
    ofVec3f camDefault = ofVec3f(960, 540, 930),
    pointToViewDefault = ofVec3f(960, 540, 0);
    ofNode node;
    enum cmStatus {CMDFT, CMEASE_IO, CMEASE_I, CMEASE_O, CMEASE_L};
    cmStatus camState;
    enum ndStatus {NDDFT, NDEASE_IO, NDEASE_I, NDEASE_O, NDEASE_L};
    ndStatus ndState;
};

