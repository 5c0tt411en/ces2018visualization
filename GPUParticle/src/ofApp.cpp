#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetVerticalSync(false);
    ofBackground(0, 0, 0);
    ofDisableAlphaBlending();
    
    cam.setupPerspective();
   
    particleNum = 100000;
    texRes = ceil(sqrt(particleNum));
    
    
    render.load("shaders/render");

  
    updatePos.load("","shaders/update.frag");
    
 
    particles.setMode(OF_PRIMITIVE_POINTS);
    for(int i=0;i<texRes;i++){
        for(int j=0;j<texRes;j++){
            int index = i * texRes + j;
            if(index < particleNum){
                particles.addVertex(ofVec3f(0,0,0));
                particles.addTexCoord(ofVec2f(i, j));
                //particles.addColor(ofFloatColor(1.0,1.0,1.0,0.5));
                particles.addColor(ofFloatColor(1.0,1.0,ofRandom(0, 0.8),0.5));
            }
        }
    }
   
    pingPong.allocate(texRes, texRes, GL_RGBA32F, 2);
   	float * posAndAge = new float[texRes * texRes * 4];
    for (int x = 0; x < texRes; x++){
        for (int y = 0; y < texRes; y++){
            int i = texRes * y + x;
            //posAndAge[i*4 + 0] = ofRandom(-0.2,0.2);
            //posAndAge[i*4 + 1] = ofRandom(-0.2,0.2);
            //posAndAge[i*4 + 2] = ofRandom(-0.2,0.2);
            posAndAge[i*4 + 0] = ofRandom(1.0);
            posAndAge[i*4 + 1] = 0.0;
            posAndAge[i*4 + 2] = 0.0;
            posAndAge[i*4 + 3] = 0;
        }
    }
 
    pingPong.src->getTextureReference(0).loadData(posAndAge, texRes, texRes, GL_RGBA);
    delete [] posAndAge;
    
	float * velAndMaxAge = new float[texRes * texRes * 4];
    for (int x = 0; x < texRes; x++){
        for (int y = 0; y < texRes; y++){
            int i = texRes * y + x;
            velAndMaxAge[i*4 + 0] = 0.0;
            velAndMaxAge[i*4 + 1] = 0.0;
            velAndMaxAge[i*4 + 2] = 0.0;
            //velAndMaxAge[i*4 + 3] = ofRandom(1,150);
            velAndMaxAge[i*4 + 3] = 0.0001;
        }
    }
      pingPong.src->getTextureReference(1).loadData(velAndMaxAge, texRes, texRes, GL_RGBA);
    delete [] velAndMaxAge;

	showTex = false;

    startShape = 1;
    rotateAngle = 0.0;
    rotatePattern = 0;
}

//--------------------------------------------------------------
void ofApp::update(){
    ofSetWindowTitle(ofToString(ofGetFrameRate()));
    
    float time = ofGetElapsedTimef();
    
       prevEmitterPos = emitterPos;
    emitterPos = 200 * ofVec3f(ofSignedNoise(time, 0, 0),ofSignedNoise(0, time, 0),ofSignedNoise(0, 0, time));
    
     pingPong.dst->begin();
    pingPong.dst->activateAllDrawBuffers();
    ofClear(0);
    updatePos.begin();

    updatePos.setUniformTexture("u_posAndAgeTex", pingPong.src->getTextureReference(0), 0);

    updatePos.setUniformTexture("u_velAndMaxAgeTex", pingPong.src->getTextureReference(1), 1);
    updatePos.setUniform1f("u_time", time);
    updatePos.setUniform1f("u_timestep", 0.01);
    updatePos.setUniform1f("u_scale", 0.005);
    updatePos.setUniform3f("u_emitterPos", emitterPos.x, emitterPos.y, emitterPos.z);
    updatePos.setUniform3f("u_prevEmitterPos", prevEmitterPos.x, prevEmitterPos.y, prevEmitterPos.z);
    updatePos.setUniform2f("u_resolution", texRes, texRes);
    updatePos.setUniform1i("u_startShape", startShape);
    updatePos.setUniform1i("u_rotatePattern", rotatePattern);
    pingPong.src->draw(0, 0);
    updatePos.end();
    pingPong.dst->end();
    pingPong.swap();
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofPushStyle();
    ofEnableBlendMode(OF_BLENDMODE_ADD);
    ofEnablePointSprites();
    cam.begin();
    render.begin();

    ofPushMatrix();
    //ofRotateY(rotateAngle);
    render.setUniformTexture("u_posAndAgeTex", pingPong.src->getTextureReference(0), 0);
    particles.draw();
    
    ofPopMatrix();
    
    render.end();
    cam.end();
    ofDisablePointSprites();
    ofPopStyle();
    
    if(showTex){
        ofPushStyle();
        ofEnableBlendMode(OF_BLENDMODE_ALPHA);
        pingPong.dst->getTextureReference(0).draw(0,0);
        //ofDrawBitmapStringHighlight("Position", 0,14);
        pingPong.dst->getTextureReference(1).draw(texRes,0);
        //ofDrawBitmapStringHighlight("Velocity", texRes,14);
        ofPopStyle();
    }
    ofDrawBitmapStringHighlight(ofToString(ofGetFrameRate()), 0,ofGetHeight() - 2);
    
    rotateAngle += 0.3;
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    if(key == ' '){
        showTex = !showTex;
    }
    
    if(key == 'f'){
        ofToggleFullscreen();
    }
    
    if(key == '1'){
        startShape = 1;
    }
    
    if(key == '2'){
        startShape = 2;
    }
    
    if(key == '3'){
        startShape = 3;
    }
    
    if(key == 'j'){
        rotatePattern += 1;
    }
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
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
