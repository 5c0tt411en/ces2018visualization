//A列はTime Stamp
//B列は0～255のインクリメントデータ
//C列は１が心電、２が加速度センサー、3がRRI、4が電池電圧を表していて、
//D～Lがそのままデータとなります。
//心電データは250Hzサンプリング周期（4ms間隔）です。
//加速度センサーデータは75ms周期で、
//13.333333333333333Hz
//頭からX1、Y1、Z1、X2、Y2、Z2、X3、Y3、Z3の順になります。
//RRIはms単位で、取得データから計算できた場合に送出されます。
//※「RRI」とは、R波とR波のIntervalになります。


#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
//    client.setup();
    string csvPath;
#ifdef DEBUG
    csvPath = "csv/dummyData.csv";
#else
    csvPath = "csv/dummyData.csv";
    ofSetWindowPosition(-1920, 0);
#endif
    ofSetVerticalSync(true);
    ofBackground(0);
    cdFont.load("fonts/HelveticaNeue-UltraLight.otf", 500);
    st = WAIT;
    
    mg.load("movies/hamon_.mov");
    
    //scv buffering
    ofBuffer buffer = ofBufferFromFile(csvPath);
    string sp = buffer.getText();
    ofStringReplace(sp, "\r", ",");
    splitString = ofSplitString(sp, ",", true, true);
    
    //GUI
    gPanel1.setup();
    gPanel1.setPosition(20, 20);
    gPanel1.add(ptclTF.setup("particles tf", false));
    gPanel1.add(ptSz1.set("point size", 1.0f, 1.0f, 10.0f));
    gPanel1.add(ptSz1.set("point size", 1.0f, 1.0f, 10.0f));
    gPanel1.add(ptEmNoise1.set("point noise", 30.0, 0.0, 500.0));
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
    
    gPanel1.add(ppLabel.setup("Effects", "post processing"));
    gPanel1.add(fxaa.setup("fxaa", false));
    gPanel1.add(bloom.setup("bloom", false));
    gPanel1.add(dof.setup("depth of field", false));
    gPanel1.add(noiseW.setup("noise warp", false));
    gPanel1.add(pixelate.setup("pixelate", false));
    gPanel1.add(rgb.setup("rgb shift", false));
    gPanel1.add(vts.setup("vertival tilt shift", false));
    gPanel1.add(hts.setup("horizontal tilt shift", false));
    gPanel1.add(godRays.setup("god rays", false));
    gPanel1.add(toon.setup("toon", false));
    gPanel1.add(zoomBl.setup("zoom blur", false));
    gPanel1.add(rhl.setup("rim highlighting", false));
    gPanel1.add(bbp.setup("bleach bypass", false));
    gPanel1.add(sss.setup("fake sss", false));
    
    
    //__________Post Processing__________//
    ofSetCoordHandedness(OF_RIGHT_HANDED);
    // Setup post-processing chain
    post.init(ofGetWidth(), ofGetHeight());
    post.createPass<FxaaPass>()->setEnabled(false);
    post.createPass<BloomPass>()->setEnabled(false);
    post.createPass<DofPass>()->setEnabled(false);
    post.createPass<NoiseWarpPass>()->setEnabled(false);
    post.createPass<PixelatePass>()->setEnabled(false);
    post.createPass<RGBShiftPass>()->setEnabled(false);
    post.createPass<VerticalTiltShifPass>()->setEnabled(false);
    post.createPass<HorizontalTiltShifPass>()->setEnabled(false);
    post.createPass<GodRaysPass>()->setEnabled(false);
    post.createPass<ToonPass>()->setEnabled(false);
    post.createPass<ZoomBlurPass>()->setEnabled(false);
    post.createPass<RimHighlightingPass>()->setEnabled(false);
    post.createPass<BleachBypassPass>()->setEnabled(false);
    post.createPass<FakeSSSPass>()->setEnabled(false);
    
    
    wave_->setup();
    particles_->setup();

    
    fbo.allocate(W, H, GL_RGBA);
}

//--------------------------------------------------------------
void ofApp::update(){
    time = ofGetElapsedTimef() - timeStamp;
    ofSetWindowTitle(ofToString(ofGetFrameRate()));
    
    ptEmNoise1 = ofMap(acce, -8200, -7500, 0.0, 500.0);
    
    if (wvTF) wave_->update();
    if (ptclTF) particles_->update(ptEmNoise1, ofVec2f(W / 2, H / 2), ofColor(245, 135, 58), ofVec2f(0,0), ptTS1, ptSc1, ptSpXY1, ptSpZ1);
    
    //__________Post Processing__________//
    post[0]->setEnabled(fxaa);
    post[1]->setEnabled(bloom);
    post[2]->setEnabled(dof);
    post[3]->setEnabled(noiseW);
    post[4]->setEnabled(pixelate);
    post[5]->setEnabled(rgb);
    post[6]->setEnabled(vts);
    post[7]->setEnabled(hts);
    post[8]->setEnabled(godRays);
    post[9]->setEnabled(toon);
    post[10]->setEnabled(zoomBl);
    post[11]->setEnabled(rhl);
    post[12]->setEnabled(bbp);
    post[13]->setEnabled(sss);
    
    switch (st) {
        case WAIT:

            break;
        case CDOWN:

            break;
        case MOTION:
            mg.update();
            break;
        case VIS:
            if (time <= 0.1) {
                wvTF = true;
                ptclTF = true;
            }
            break;

        default:
            break;
    }

}

//--------------------------------------------------------------
void ofApp::draw(){
//                    bloom = true;
    //__________Post Processing__________//
    // copy enable part of gl state
    glPushAttrib(GL_ENABLE_BIT);
    
    // setup gl state
    glEnable(GL_DEPTH_TEST);
    //    light.enable();
    
    // begin scene to post process
    post.begin();
    
    
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
            if (int(time * 10) % 10 == 0) {
                rgb = true;
                sss = true;
                fxaa = true;
                vts = true;
                godRays = true;
                noiseW = true;
            }
            else {
                rgb = false;
                sss = false;
                fxaa = false;
                vts = false;
                godRays = false;
                noiseW = false;
            }
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
                mg.play();
                st = MOTION;
                timeStamp = ofGetElapsedTimef();

            }
            break;
        case MOTION:
            mg.draw(0, 0);
            debLOG = "MOTION";
            if (time >= 6.0) {
                mg.stop();
                st = VIS;
                timeStamp = ofGetElapsedTimef();
            }
            break;
        case VIS:
            debLOG = "VIS";
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
        break;

        default:
            break;
    }
    
    fbo.begin();
    ofClear(0);
    
    ptSz1 = ofMap(heart, 1300, 1600, 1.0, 3.0);
    
   if (ptclTF) particles_->draw(ptSz1);
    ofSetColor(255);
    
    dHeight = ofMap(acce, -8200, -4000, 100.0, 1000.0);
    nFreq = ofMap(heart, 1300, 1600, 10.0, 50.0);
    
    if (wvTF) wave_->draw(seaCol, seaDM, seaPS, nFreq, spY, dHeight, seaModeAu, seaAu);
    fbo.end();
//    ofSetColor(255, 255, 255, 120);
//    client.draw(0, 0, 1920, 1080);
    
    ofSetColor(255);
    fbo.draw(0, 0);
    
    // end scene and draw
    post.end();
    
    
    // set gl state back to original
    glPopAttrib();
    
    
#ifdef DEBUG
    string s;
    s += "state is now " + debLOG + '\n' + '\n';
    s += "heart: " + ofToString(heart) + '\n';
    s += "acce: " + ofToString(acce) + '\n';
    s += "rri: " + ofToString(rri) + '\n';
    ofDrawBitmapStringHighlight(s, W - 200, 20);
    gPanel1.draw();
#endif
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if (key == ' ') {
        trigger = true;
    }
}

string ofApp::getData(int row, int column) {
    string data = splitString[(column - 1) * 12 + (row - 1)];
    
    return data;
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

