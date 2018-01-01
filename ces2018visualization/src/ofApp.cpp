
//___________________________________//

#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
#ifdef PROTO
    string csvPath;
    csvPath = "csv/dummyData.csv";
    //csv buffering
    ofBuffer buffer = ofBufferFromFile(csvPath);
    string sp = buffer.getText();
    ofStringReplace(sp, "\r", ",");
    splitString = ofSplitString(sp, ",", true, true);
#endif
    ofSetVerticalSync(true);
    ofBackground(0);
    cdFont.load("fonts/HelveticaNeue-UltraLight.otf", 500);
    st = WAIT;

//______________MEDIAS________________//
    mg.load("movies/hamon.mov");
    hb.load("movies/heartBeat.mov");
    testP.load("images/testPattern.jpg");
    
//________________OSC_________________//
    receiver.setup(8000);
    sender.setup(SHOST, SPORT);
    
//_______________CAMERA_______________//
    cam.setupPerspective();
    cam.setPosition(camDefault);
    pointToView.set(pointToViewDefault);
    node.setPosition(pointToView);
    cam.lookAt(node.getPosition());
    
//________________GUI_________________//
    gPanel1.setup();
    gPanel1.setPosition(20, 20);
    gPanel1.add(tGrid.setup("grid for DEBUG", true));
    gPanel1.add(ptclTF.setup("particles tf", false));
    gPanel1.add(ptSz1.set("point size", 1.0f, 1.0f, 10.0f));
    gPanel1.add(ptEmNoise1.set("point noise", 1000.0, 0.0, 1000.0));
    gPanel1.add(ptTS1.set("point time step", 0.5, 0.0, 1.0));
    gPanel1.add(ptSc1.set("point scale", 0.005, 0.0, 0.1));
    gPanel1.add(ptSpXY1.set("point speed X, Y", 0.0, 0.0, 1.0));
    gPanel1.add(ptSpZ1.set("point speed Z", 0.05, 0.0, 1.0));
    
    gPanel1.add(wvTF.setup("wave tf", false));
    gPanel1.add(seaCol.set("sea color", ofColor(58, 153, 255, 40)));
    gPanel1.add(seaDM.setup("sea draw mode", false));
    gPanel1.add(seaPS.set("sea point size", 1, 1, 30));
    gPanel1.add(nFreq.set("noise freqency", 0, 0, 100.0));
    gPanel1.add(spY.set("speed", 0, 0, 10.0));
    gPanel1.add(dHeight.set("wave height", 100.0, 0, 300.0));
    gPanel1.add(seaModeAu.setup("mode audio reactive", false));
    gPanel1.add(seaAu.setup("audio reactive", false));
    
    gPanel1.add(abcTF.setup("abc tf", false));
    gPanel1.add(shape.set("shape", 0, 0, 6));
    gPanel1.add(vel.set("velocity", 0., 0., 30.));
    gPanel1.add(ptSzABC.set("point size abc", 1, 1, 100));
    
    gPanel1.add(tSceneST.setup("scene star", false));
    
    gPanel1.add(tScene06.setup("scene geometry tunnel", false));
    gPanel1.add(cScene06.set("tunnel color", ofColor(8,29,70)));
    
    gPanel1.add(tScene07.setup("CES LOGO geometry", false));
    gPanel1.add(cScene07.set("LOGO color", ofColor(48,102,145, 255)));
    
    gPanel1.add(tScene02.setup("scene ribbon", true));
    gPanel1.add(cScene02.set("ribbon color: before", ofColor(36, 52, 66, 130)));
    gPanel1.add(cScene02p.set("ribbon color: after", ofColor(67, 29, 145, 255)));
    gPanel1.add(chroma.set("chromakey threshould", 1.01, 0., 1.01));
    
    gPanelP.setup();
    gPanelP.setPosition(240, 20);
    gPanelP.add(ppLabel.setup("Effects", "post processing"));
    gPanelP.add(bb.setup("BleachBypass", false));
    gPanelP.add(bloom.setup("Bloom", true));
    gPanelP.add(cont.setup("Contrast", false));
    gPanelP.add(conv.setup("Convolution", false));
    gPanelP.add(dofa.setup("DofAlt", false));
    gPanelP.add(dof.setup("Dof", false));
    gPanelP.add(edge.setup("Edge", false));
    gPanelP.add(fsss.setup("FakeSSS", false));
    gPanelP.add(fxaa.setup("Fxaa", false));
    gPanelP.add(gr.setup("GodRays", true));
    gPanelP.add(hts.setup("HorizontalTiltShift", false));
    gPanelP.add(kd.setup("Kaleidoscope", false));
    gPanelP.add(ld.setup("LimbDarkening", true));
    gPanelP.add(lut.setup("LUT", false));
    gPanelP.add(nw.setup("NoiseWarp", false));
    gPanelP.add(pixel.setup("Pixelate", false));
    gPanelP.add(rgbs.setup("RGBShift", false));
    gPanelP.add(rh.setup("RimHighlighting", false));
    gPanelP.add(ssao.setup("SSAO", true));
    gPanelP.add(toon.setup("Toon", false));
    gPanelP.add(vts.setup("VerticalTiltShif", false));
    gPanelP.add(zb.setup("ZoomBlur", false));
    
    gPanelFX.setup();
    gPanelFX.setPosition(480, 20);
    gPanelFX.add(fNoise.setup("KSMR_FRAGFX_NOISE", false));
    gPanelFX.add(fEdge.setup("KSMR_FRAGFX_EDGEONTOP", false));
    gPanelFX.add(fFringe.setup("KSMR_FRAGFX_FRINGE", false));
    gPanelFX.add(fInvert.setup("KSMR_FRAGFX_INVERT", false));
    gPanelFX.add(fSShift.setup("KSMR_FRAGFX_SLANTSHIFT", false));
    gPanelFX.add(fTexChip.setup("KSMR_FRAGFX_TEXCHIP", false));
    gPanelFX.add(fVertNoise.setup("KSMR_FRAGFX_VERTNOISE", false));
    gPanelFX.add(fVertSlide.setup("KSMR_FRAGFX_VERTSLIDE", false));
    gPanelFX.add(fWater.setup("KSMR_FRAGFX_WATER", false));
    
//__________Post Processing__________//
    ofSetCoordHandedness(OF_RIGHT_HANDED);
    post.init(W, H);
    post.createPass<BleachBypassPass>()->setEnabled(false);
    post.createPass<BloomPass>()->setEnabled(false);
    post.createPass<ContrastPass>()->setEnabled(false);
    post.createPass<ConvolutionPass>()->setEnabled(false);
    post.createPass<DofAltPass>()->setEnabled(false);
    post.createPass<DofPass>()->setEnabled(false);
    post.createPass<EdgePass>()->setEnabled(false);
    post.createPass<FakeSSSPass>()->setEnabled(false);
    post.createPass<FxaaPass>()->setEnabled(false);
    post.createPass<GodRaysPass>()->setEnabled(false);
    post.createPass<HorizontalTiltShifPass>()->setEnabled(false);
    post.createPass<KaleidoscopePass>()->setEnabled(false);
    post.createPass<LimbDarkeningPass>()->setEnabled(false);
    post.createPass<LUTPass>()->setEnabled(false);
    post.createPass<NoiseWarpPass>()->setEnabled(false);
    post.createPass<PixelatePass>()->setEnabled(false);
    post.createPass<RGBShiftPass>()->setEnabled(false);
    post.createPass<RimHighlightingPass>()->setEnabled(true);
    post.createPass<SSAOPass>()->setEnabled(false);
    post.createPass<ToonPass>()->setEnabled(false);
    post.createPass<VerticalTiltShifPass>()->setEnabled(false);
    post.createPass<ZoomBlurPass>()->setEnabled(false);
    
//______________classes______________//
    wave_->setup();
    particles_->setup();
    abcAnim_->setup();
    sceneST_->setup();
    scene06_->setup();
    scene07_->setup();
    
//________________FBO_______________//
//    fbo.allocate(W, H, GL_RGBA);
    
//______________ksmrFX______________//
    setting.width  = W;
    setting.height = H;
    fbo.allocate(setting);
    fx.setup(&fbo, setting);
    
#ifdef DEBUG
    ofSetWindowPosition(0, 0);
#else
//    ofSetWindowPosition(-W, 0);
    trigger = false;
#endif
}

//--------------------------------------------------------------
void ofApp::update(){
    time = ofGetElapsedTimef() - timeStamp;
    ofSetWindowTitle(ofToString(ofGetFrameRate()));
    
    
    //___________OSC____________//
    while (receiver.hasWaitingMessages()) {
        ofxOscMessage m;
        receiver.getNextMessage(m);
        if (m.getNumArgs())
            v.set(
                  m.getArgAsFloat(0),
                  m.getArgAsFloat(1),
                  m.getArgAsFloat(2),
                  m.getArgAsFloat(3)
                  );
        items = ofSplitString(m.getAddress(), "/");
        
//______________classes______________//
        if (items[1] == "begin") {
            trigger = true;
        }
        if (items[1] == "frame") {
            frame = v.x;
        }
        if (items[1] == "reset") {
            ptclTF = false;
            tScene07 = false;
            tSceneST = false;
            wvTF = false;
            camPos.set(camDefault);
            pointToView.set(pointToViewDefault);
            node.setPosition(pointToView);
            cam.lookAt(node.getPosition());
            scene02_.clear();
            tScene06 = false;
            abcTF = false;
            timeStamp = ofGetElapsedTimef();
        }
        if (items[1] == "0") {
            if (items[2] == "cone") {
                circle_.push_back(new circle(ofVec3f(v)));
                circle_.back()->resetTimer();
                circle_.back()->setup();
            }
            else if (items[2] == "heartBeat") {
                hb.play();
                st = HBEAT;
                timeStamp = ofGetElapsedTimef();
//                heartBeat_.push_back(new heartBeat());
//                heartBeat_.back()->resetTimer();
//                heartBeat_.back()->setup();
            }
        }
        if (items[1] == "1") {
            if (items[2] == "mov") {
                st = MOTION;
                timeStamp = ofGetElapsedTimef();
                mg.play();
            }
            else {
                hamon_.push_back(new hamon(items[2], v.x, v.y, v.z));
                hamon_.back()->resetTimer();
                hamon_.back()->setup();
            }
        }
        if (items[1] == "2") {
                hamonObj_.push_back(new hamonObj(items[2], v.x, v.y, v.z));
                hamonObj_.back()->resetTimer();
                hamonObj_.back()->setup();
        }
        if (items[1] == "ny") {
            scene02_.push_back(new scene02(v.x, v.y, v.z, v.w));
            scene02_.back()->resetTimer();
            scene02_.back()->setup();
        }
        if (items[1] == "nyAll") {
            for (int i = 0; i < 20; i++) {
                scene02_.push_back(new scene02(
                                               v.x + ofRandom(-500, 500),
                                               v.y + ofRandom(-100, 100),
                                               v.z + ofRandom(-500, 500),
                                               v.w + ofRandom(-500, 500)
                                               )
                                   );
                scene02_.back()->resetTimer();
                scene02_.back()->setup();
            }
        }
        if (items[1] == "hmov") {
            if (v.x){
                hamonMov_.push_back(new hamonMov(ofToInt(items[2])));
                hamonMov_.back()->setup();
            }
        }
        
//_______________CAMERA_______________//
        if (items[1] == "nd") {
            pointToView.set(v);
        }
        if (items[1] == "cm") {
            camPos.set(v);
            timeStamp = ofGetElapsedTimef();
        }
        if (items[1] == "cmL") {
            camShiftFrom.set(camPos);
            camState = CMEASE_L;
            camShiftTo.set(v);
            easeEnd = v.w;
            timeStamp = ofGetElapsedTimef();
        }
        if (items[1] == "cmEIO") {
            camShiftFrom.set(camPos);
            camState = CMEASE_IO;
            camShiftTo.set(v);
            easeEnd = v.w;
            timeStamp = ofGetElapsedTimef();
        }
        if (items[1] == "cmEI") {
            camState = CMEASE_I;
            camShiftFrom.set(camPos);
            camShiftTo.set(v);
            easeEnd = v.w;
            timeStamp = ofGetElapsedTimef();
        }
        if (items[1] == "cmEO") {
            camState = CMEASE_O;
            camShiftFrom.set(camPos);
            camShiftTo.set(v);
            easeEnd = v.w;
            timeStamp = ofGetElapsedTimef();
        }
        if (items[1] == "ndL") {
            nodeShiftFrom.set(pointToView);
            ndState = NDEASE_L;
            nodeShiftTo.set(v);
            easeEnd = v.w;
            timeStamp = ofGetElapsedTimef();
        }
        if (items[1] == "ndEIO") {
            nodeShiftFrom.set(pointToView);
            ndState = NDEASE_IO;
            nodeShiftTo.set(v);
            easeEnd = v.w;
            timeStamp = ofGetElapsedTimef();
        }
        if (items[1] == "ndEI") {
            ndState = NDEASE_I;
            nodeShiftFrom.set(pointToView);
            nodeShiftTo.set(v);
            easeEnd = v.w;
            timeStamp = ofGetElapsedTimef();
        }
        if (items[1] == "ndEO") {
            ndState = NDEASE_O;
            nodeShiftFrom.set(pointToView);
            nodeShiftTo.set(v);
            easeEnd = v.w;
            timeStamp = ofGetElapsedTimef();
        }
        if (items[1] == "ptcl") ptclTF =  v.x;
        if (items[1] == "wave") wvTF =  v.x;
        if (items[1] == "abc") {
            abcTF   = v.x;
            shape   = v.y;
            vel     = v.z;
            ptSzABC = v.w;
        }
        if (items[1] == "star") tSceneST =  v.x;
        if (items[1] == "tunnel") {
            tScene06 =  v.x;
//            shape   = v.y;
//            vel     = v.z;
//            ptSzABC = v.w;
        }
        if (items[1] == "build") tScene07 =  v.x;
//        if (items[1] == "sc07") tScene07 =  v.x;
//        if (items[1] == "scG") tSceneG =  v.x;
//        if (items[1] == "scST") tSceneST =  v.x;
        
        if (items[1] == "bb") bb =  v.x;
        if (items[1] == "bloom") bloom =  v.x;
        if (items[1] == "cont") cont =  v.x;
        if (items[1] == "conv") conv =  v.x;
        if (items[1] == "dofa") dofa =  v.x;
        if (items[1] == "dof") dof =  v.x;
        if (items[1] == "edge") edge =  v.x;
        if (items[1] == "fsss") fsss =  v.x;
        if (items[1] == "fxaa") fxaa =  v.x;
        if (items[1] == "gr") gr =  v.x;
        if (items[1] == "hts") hts =  v.x;
        if (items[1] == "kd") kd =  v.x;
        if (items[1] == "ld") ld =  v.x;
        if (items[1] == "lut") lut =  v.x;
        if (items[1] == "nw") nw =  v.x;
        if (items[1] == "pixel") pixel =  v.x;
        if (items[1] == "rgbs") rgbs =  v.x;
        if (items[1] == "rh") rh =  v.x;
        if (items[1] == "ssao") ssao =  v.x;
        if (items[1] == "toon") toon =  v.x;
        if (items[1] == "vts") vts =  v.x;
        if (items[1] == "zb") zb =  v.x;
    }
    
    switch (camState) {
        case CMEASE_IO:
            if (time <= easeEnd) {
                camPos = ofVec3f(
                                 easeInOutCubic(time, camShiftFrom.x, camShiftTo.x - camShiftFrom.x, easeEnd),
                                 easeInOutCubic(time, camShiftFrom.y, camShiftTo.y - camShiftFrom.y, easeEnd),
                                 easeInOutCubic(time, camShiftFrom.z, camShiftTo.z - camShiftFrom.z, easeEnd)
                                 );
            }
            if (time > easeEnd) {
                camPos.set(camShiftTo);
                timeStamp = ofGetElapsedTimef();
                camState = CMDFT;
            }
            break;
        case CMEASE_I:
            if (time <= easeEnd) {
                camPos = ofVec3f(
                                 easeInCubic(time, camShiftFrom.x, camShiftTo.x - camShiftFrom.x, easeEnd),
                                 easeInCubic(time, camShiftFrom.y, camShiftTo.y - camShiftFrom.y, easeEnd),
                                 easeInCubic(time, camShiftFrom.z, camShiftTo.z - camShiftFrom.z, easeEnd)
                                 );
            }
            if (time > easeEnd) {
                camPos.set(camShiftTo);
                timeStamp = ofGetElapsedTimef();
                camState = CMDFT;
            }
            break;
        case CMEASE_O:
            if (time <= easeEnd) {
                camPos = ofVec3f(
                                 easeOutCubic(time, camShiftFrom.x, camShiftTo.x - camShiftFrom.x, easeEnd),
                                 easeOutCubic(time, camShiftFrom.y, camShiftTo.y - camShiftFrom.y, easeEnd),
                                 easeOutCubic(time, camShiftFrom.z, camShiftTo.z - camShiftFrom.z, easeEnd)
                                 );
            }
            if (time > easeEnd) {
                camPos.set(camShiftTo);
                timeStamp = ofGetElapsedTimef();
                camState = CMDFT;
            }
            break;
        case CMEASE_L:
            if (time <= easeEnd) {
                camPos = ofVec3f(
                                          easeLinear(time, camShiftFrom.x, camShiftTo.x - camShiftFrom.x, easeEnd),
                                          easeLinear(time, camShiftFrom.y, camShiftTo.y - camShiftFrom.y, easeEnd),
                                          easeLinear(time, camShiftFrom.z, camShiftTo.z - camShiftFrom.z, easeEnd)
                                          );
            }
            if (time > easeEnd) {
                camPos.set(camShiftTo);
                timeStamp = ofGetElapsedTimef();
                camState = CMDFT;
            }
        case CMDFT:
            
            break;
        default:
            break;
    }
    
    switch (ndState) {
        case NDEASE_IO:
            if (time <= easeEnd) {
                pointToView = ofVec3f(
                                      easeInOutCubic(time, nodeShiftFrom.x, nodeShiftTo.x - nodeShiftFrom.x, easeEnd),
                                      easeInOutCubic(time, nodeShiftFrom.y, nodeShiftTo.y - nodeShiftFrom.y, easeEnd),
                                      easeInOutCubic(time, nodeShiftFrom.z, nodeShiftTo.z - nodeShiftFrom.z, easeEnd)
                                      );
            }
            if (time > easeEnd) {
                pointToView.set(nodeShiftTo);
                timeStamp = ofGetElapsedTimef();
                ndState = NDDFT;
            }
            break;
        case NDEASE_I:
            if (time <= easeEnd) {
                pointToView = ofVec3f(
                                      easeInCubic(time, nodeShiftFrom.x, nodeShiftTo.x - nodeShiftFrom.x, easeEnd),
                                      easeInCubic(time, nodeShiftFrom.y, nodeShiftTo.y - nodeShiftFrom.y, easeEnd),
                                      easeInCubic(time, nodeShiftFrom.z, nodeShiftTo.z - nodeShiftFrom.z, easeEnd)
                                      );
            }
            if (time > easeEnd) {
                pointToView.set(nodeShiftTo);
                timeStamp = ofGetElapsedTimef();
                ndState = NDDFT;
            }
            break;
        case NDEASE_O:
            if (time <= easeEnd) {
                pointToView = ofVec3f(
                                      easeOutCubic(time, nodeShiftFrom.x, nodeShiftTo.x - nodeShiftFrom.x, easeEnd),
                                      easeOutCubic(time, nodeShiftFrom.y, nodeShiftTo.y - nodeShiftFrom.y, easeEnd),
                                      easeOutCubic(time, nodeShiftFrom.z, nodeShiftTo.z - nodeShiftFrom.z, easeEnd)
                                      );
            }
            if (time > easeEnd) {
                pointToView.set(nodeShiftTo);
                timeStamp = ofGetElapsedTimef();
                ndState = NDDFT;
            }
            break;
        case NDEASE_L:
            if (time <= easeEnd) {
                pointToView = ofVec3f(
                                      easeLinear(time, nodeShiftFrom.x, nodeShiftTo.x - nodeShiftFrom.x, easeEnd),
                                      easeLinear(time, nodeShiftFrom.y, nodeShiftTo.y - nodeShiftFrom.y, easeEnd),
                                      easeLinear(time, nodeShiftFrom.z, nodeShiftTo.z - nodeShiftFrom.z, easeEnd)
                                      );
            }
            if (time > easeEnd) {
                pointToView.set(nodeShiftTo);
                timeStamp = ofGetElapsedTimef();
                ndState = NDDFT;
            }
        case NDDFT:
            
            break;
        default:
            break;
    }
    
//    ptEmNoise1 = ofMap(acce, -8200, -7500, 0.0, 500.0);
    
//______________classes______________//
    if (wvTF) wave_->update();
    if (ptclTF) particles_->update(ptEmNoise1, ofVec2f(W / 2, H / 2), ofColor(245, 135, 58), ofVec2f(0,0), ptTS1, ptSc1, ptSpXY1, ptSpZ1);
    if (abcTF) abcAnim_->update(shape, vel);
    if (tSceneST) sceneST_->update();
    if (tScene06) scene06_->update();
    if (tScene07) scene07_->update();
    for (int i = 0; i < circle_.size(); i++) {
        circle_[i]->update();
    }
    for (int i = 0; i < heartBeat_.size(); i++) {
        heartBeat_[i]->update();
    }
    for (int i = 0; i < hamon_.size(); i++) {
        hamon_[i]->update();
    }
    for (int i = 0; i < hamonObj_.size(); i++) {
        hamonObj_[i]->update();
    }
    if (tScene02) {
        if (scene02_.size()) {
            for (int i = 0; i < scene02_.size(); i++) {
                scene02_[i]->update(cScene02, cScene02p);
            }
        }
    }
    
    switch (st) {
        case WAIT:

            break;
        case CDOWN:

            break;
        case HBEAT:
            hb.update();
            break;
        case MOTION:
            mg.update();
            break;
        case VIS:
//            if (time <= 0.1) {
//                wvTF = true;
//                ptclTF = true;
//            }
            break;

        default:
            break;
    }
    for (int i = 0; i < hamonMov_.size(); i++) {
        hamonMov_[i]->update(frame);
    }

    
    
    cam.setPosition(camPos);
    node.setPosition(pointToView);
    cam.lookAt(node.getPosition());
    
    //__________Post Processing__________//
    post[0]->setEnabled(bb);
    post[1]->setEnabled(bloom);
    post[2]->setEnabled(cont);
    post[3]->setEnabled(conv);
    post[4]->setEnabled(dofa);
    post[5]->setEnabled(dof);
    post[6]->setEnabled(edge);
    post[7]->setEnabled(fsss);
    post[8]->setEnabled(fxaa);
    post[9]->setEnabled(gr);
    post[10]->setEnabled(hts);
    post[11]->setEnabled(kd);
    post[12]->setEnabled(ld);
    post[13]->setEnabled(lut);
    post[14]->setEnabled(nw);
    post[15]->setEnabled(pixel);
    post[16]->setEnabled(rgbs);
    post[17]->setEnabled(rh);
    post[18]->setEnabled(ssao);
    post[19]->setEnabled(toon);
    post[20]->setEnabled(vts);
    post[21]->setEnabled(zb);
    bloom = true;
    
    //OSC sender
    ofxOscMessage m;
    m.setAddress("/cam");
    m.addIntArg((int)camPos.x);
    m.addIntArg((int)camPos.y);
    m.addIntArg((int)camPos.z);
    m.addIntArg((int)pointToView.x);
    m.addIntArg((int)pointToView.y);
    m.addIntArg((int)pointToView.z);
    sender.sendMessage(m);
    
//______________ksmrFX______________//
    fx.getfxUnit(KSMR_FRAGFX_NOISE)->bEnable      = fNoise;
    fx.getfxUnit(KSMR_FRAGFX_EDGEONTOP)->bEnable  = fEdge;
    fx.getfxUnit(KSMR_FRAGFX_FRINGE)->bEnable     = fFringe;
    fx.getfxUnit(KSMR_FRAGFX_INVERT)->bEnable     = fInvert;
    fx.getfxUnit(KSMR_FRAGFX_SLANTSHIFT)->bEnable = fSShift;
    fx.getfxUnit(KSMR_FRAGFX_TEXCHIP)->bEnable    = fTexChip;
    fx.getfxUnit(KSMR_FRAGFX_VERTNOISE)->bEnable  = fVertNoise;
    fx.getfxUnit(KSMR_FRAGFX_VERTSLIDE)->bEnable  = fVertSlide;
    fx.getfxUnit(KSMR_FRAGFX_WATER)->bEnable      = fWater;
    fx.getfxUnit(KSMR_FRAGFX_VERTSLIDE)->u_Volume = ofNoise(ofGetElapsedTimef())*5000.0;
}

//--------------------------------------------------------------
void ofApp::draw(){
    time = ofGetElapsedTimef() - timeStamp;
    
    fbo.begin();
    {
        ofClear(0);
        
        cam.begin();
//__________Post Processing__________//
        post.begin();
        
#ifdef DEBUG
        ofPushStyle();
        ofPushMatrix();
        ofTranslate(W / 2, H / 2);
        if (tGrid)
            ofDrawGrid(100.0f, 100.0f, true, true, true, true);
        ofPopMatrix();
        ofPopStyle();
#endif
        
        switch (st) {
            case WAIT:
                debLOG = "WAIT";
                if (trigger) {
                    st = CDOWN;
                    timeStamp = ofGetElapsedTimef();
                    trigger = false;
                }
                break;
            case CDOWN:
                debLOG = "CDOWN";
                ofSetColor(255);
                countDown = cdMAX - int(time);
                cdFS = ofToString(countDown);
                cdFont.drawString(
                                  cdFS,
                                  W / 2 - cdFont.stringWidth(cdFS) / 2,
                                  H / 2 + cdFont.stringHeight(cdFS) / 2
                                  );
                
                if (time >= cdMAX - 0.05) {
//                    mg.play();
                    st = WAIT;
                    timeStamp = ofGetElapsedTimef();
//
                }
                break;
            case MOTION:
                ofSetColor(255);
                mg.draw(0, 0);
                debLOG = "MOTION";
                if (time >= 7.0) {
                    mg.stop();
                    mg.close();
                    st = VIS;
                    timeStamp = ofGetElapsedTimef();
                }
                break;
            case HBEAT:
                ofSetColor(255);
                hb.draw(0, 0);
                if (time >= 16.) {
                    hb.stop();
                    hb.close();
                    st = VIS;
                    timeStamp = ofGetElapsedTimef();
                }
            case VIS:
                debLOG = "VIS";
#ifdef PROTO
                if (time >= 0.004 * (float)heartCount) {
                    for (int i = 1 + startHeart; i < 1 + columnMAX; i++) {
                        if (ofToInt(getData(3, i)) == 1) {
                            heart = ofToFloat(getData(4, i));
                            startHeart = i;
                            heartCount++;
                            break;
                        }
                    }
                }
                if (time >= 0.075 * float(acceCount + 1)) {
                    for (int i = 1 + startAcce; i < 1 + columnMAX; i++) {
                        if (ofToInt(getData(3, i)) == 2) {
                            acce = ofToFloat(getData(4, i));
                            startAcce = i;
                            acceCount++;
                            break;
                        }
                    }
                }
                if (time >= 0.75 * (float)rriCount) {
                    for (int i = 1 + startRri; i < 1 + columnMAX; i++) {
                        if (ofToInt(getData(3, i)) == 3) {
                            rri = ofToFloat(getData(4, i));
                            startRri = i;
                            rriCount++;
                            break;
                        }
                    }
                }
                ptSz1 = ofMap(heart, 1300, 1600, 1.0, 3.0);
                dHeight = ofMap(acce, -8200, -4000, 100.0, 1000.0);
                nFreq = ofMap(heart, 1300, 1600, 10.0, 50.0);
#endif
                
                break;
                
            default:
                break;
        }

//______________classes______________//
        if (ptclTF) particles_->draw(ptSz1 + 1.);
        ofSetColor(255);
        if (wvTF) wave_->draw(seaCol, seaDM, seaPS, nFreq, spY, dHeight, seaModeAu, seaAu);
        if (tScene06) scene06_->draw(cScene06);
        if (tScene07) scene07_->draw(cScene07);
        if (tSceneST) sceneST_->draw();
        if (abcTF) abcAnim_->draw(ptSzABC);
        for (int i = 0; i < circle_.size(); i++) {
            circle_[i]->draw();
            if (circle_[i]->time >= 1.)
                circle_.erase(circle_.begin() + i);
        }
        for (int i = 0; i < heartBeat_.size(); i++) {
            heartBeat_[i]->draw();
            if (heartBeat_[i]->time >= 2.)
                heartBeat_.erase(heartBeat_.begin() + i);
        }
        for (int i = 0; i < hamon_.size(); i++) {
            hamon_[i]->draw();
            if (
                hamon_[i]->time >=
                hamon_[i]->drawP +
                hamon_[i]->stay +
                hamon_[i]->erase
                )
                hamon_.erase(hamon_.begin() + i);
        }
        for (int i = 0; i < hamonObj_.size(); i++) {
            hamonObj_[i]->draw();
            if (
                hamonObj_[i]->time >=
                hamonObj_[i]->drawP +
                hamonObj_[i]->stay +
                hamonObj_[i]->erase
                )
                hamonObj_.erase(hamonObj_.begin() + i);
        }
        if (tScene02)
            if (scene02_.size()) {
                for (int i = 0; i < scene02_.size(); i++) {
                    scene02_[i]->draw();
                }
            }
        for (int i = 0; i < hamonMov_.size(); i++) {
            hamonMov_[i]->draw();
        }
        cam.end();
        
        post.end();
    }
    fbo.end();

    
    
    
    ofSetColor(255);
    testP.draw(0,0, W, H);

//______________ksmrFX______________//
    fx.applyFx();
//    post.begin();
    fbo.draw(0, 1008, 1872, -1008);
//    post.end();
//    fbo.draw(0, 1080, 1920, -1080);
//    ofSetColor(255, 255, 255, 255);
//    shader.begin();
//    shader.setUniform3f("chromaKeyColor", ofVec3f(0.0, 1.0, 0.0));
//    shader.setUniform1f("threshold", chroma);
//    client.draw(0, 0, 1872, 1008);
//    shader.end();
    ofLog() << frame << endl;
#ifdef DEBUG
    ofDisableDepthTest();
    string s;
    s += "state is now " + debLOG + '\n' + '\n';
    s += "circle size: " + ofToString(circle_.size()) + '\n';
    s += "heartBeat size: " + ofToString(heartBeat_.size()) + '\n';
    s += "hamon size: " + ofToString(hamon_.size()) + '\n';
    s += "OSC frame: " + ofToString(frame) + '\n';
    ofDrawBitmapStringHighlight(s, W - 200, 20);
    gPanel1.draw();
    gPanelP.draw();
    gPanelFX.draw();
#endif
}

string ofApp::getData(int row, int column) {
    string data = splitString[(column - 1) * 12 + (row - 1)];
    
    return data;
}

float ofApp::easeInOutQuadratic(float t, float b, float c, float d) {
    t /= (d/2.0) ;
    ofLogNotice(ofToString(t)) ;
    if (t < 1) {
        return(c/2.0*t*t + b) ;
    } else {
        t-=1.0;
        return(-c/2.0 * (t*(t-2) - 1) + b) ;
    }
}

float ofApp::easeInOutCubic(float t, float b, float c, float d) {
    t /= d/2.0 ;
    if (t < 1) {
        return (c/2.0*t*t*t + b) ;
    }
    t -= 2.0 ;
    return (c/2.0 * (t*t*t + 2) + b) ;
}

float ofApp::easeOutCubic(float t, float b, float c, float d) {
    t /= d ;
    t-- ;
    return (c*(t*t*t + 1) + b) ;
}

float ofApp::easeInCubic(float t, float b, float c, float d) {
    return c * (t/=d) *t*t + b;
}


float ofApp::easeLinear(float t, float b, float c, float d) {
    return (c*t/d + b) ;
}

