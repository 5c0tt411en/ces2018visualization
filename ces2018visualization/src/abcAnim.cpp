//
//  abcAmin.cpp
//  ces2018visualization
//
//  Created by scott on 2017/12/24.
//

#include "abcAnim.h"

abcAnim::abcAnim() {
    
}

//--------------------------------------------------------------
void abcAnim::setup(){
    particleNum = 200000;
    texRes = ceil(sqrt(particleNum));
    
    // Frag, Vert and Geo shaders for the rendering process of the spark image
    render.setGeometryInputType(GL_POINTS);
    render.setGeometryOutputType(GL_TRIANGLE_STRIP);
    render.setGeometryOutputCount(6);
    render.load("shaders/abcAnim/render");
    updatePos.load("","shaders/abcAnim/update.frag");
    
    //position fbo
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
    pingPong.src->getTexture(0).loadData(posAndAge, texRes, texRes, GL_RGBA);
    pingPong.dst->getTexture(0).loadData(posAndAge, texRes, texRes, GL_RGBA);
    delete [] posAndAge;
    
    // velocity fbo
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
    pingPong.src->getTexture(1).loadData(velAndMaxAge, texRes, texRes, GL_RGBA);
    pingPong.dst->getTexture(1).loadData(velAndMaxAge, texRes, texRes, GL_RGBA);
    delete [] velAndMaxAge;
    
    showTex = false;
    
    startShape = 1;
    
    // Loading and setings of the variables of the textures of the particles
    ofDisableArbTex();
    sparkImg.load("images/sphere5_14.png");
    imgWidth = sparkImg.getWidth();
    imgHeight = sparkImg.getHeight();
    // Allocate the final
    renderFBO.allocate(W, H, GL_RGB32F);
    renderFBO.begin();
    ofClear(0, 0, 0, 255);
    renderFBO.end();
    
    particles.setMode(OF_PRIMITIVE_POINTS);
    for(int i=0;i<texRes;i++){
        for(int j=0;j<texRes;j++){
            int index = i * texRes + j;
            if(index < particleNum){
                particles.addVertex(ofVec3f(i, j));
                particles.addTexCoord(ofVec2f(i, j));
                //particles.addColor(ofFloatColor(1.0,1.0,1.0,0.5));
                particles.addColor(
                                   ofFloatColor(
                                                1.,
                                                1.,
                                                1.,
                                                float(index) / float(particleNum)
                                                )
                                   );
                
            }
        }
    }
    //alembic
    loader.open("alembics/2017-12-31-03-02-35-740.abc");
}

//--------------------------------------------------------------
void abcAnim::update(int _startShape, float _vel){
    startShape = _startShape;
    vel = _vel;
    
    prevEmitterPos = emitterPos;
    emitterPos = 200 * ofVec3f(ofSignedNoise(time, 0, 0),ofSignedNoise(0, time, 0),ofSignedNoise(0, 0, time));
    
    pingPong.dst->begin();
    pingPong.dst->activateAllDrawBuffers();
    ofClear(0);
    updatePos.begin();
    
    updatePos.setUniformTexture("u_posAndAgeTex", pingPong.src->getTexture(0), 0);
    
    updatePos.setUniformTexture("u_velAndMaxAgeTex", pingPong.src->getTexture(1), 1);
    updatePos.setUniform1f("u_time", time);
    updatePos.setUniform1f("u_timestep", 0.01);
    updatePos.setUniform1f("u_scale", vel);
    updatePos.setUniform3f("u_emitterPos", emitterPos.x, emitterPos.y, emitterPos.z);
    updatePos.setUniform3f("u_prevEmitterPos", prevEmitterPos.x, prevEmitterPos.y, prevEmitterPos.z);
    updatePos.setUniform2f("u_resolution", texRes, texRes);
    updatePos.setUniform1i("u_startShape", startShape);
    updatePos.setUniform1i("u_rotatePattern", rotatePattern);
    pingPong.src->draw(0, 0);
    updatePos.end();
    pingPong.dst->end();
    pingPong.swap();
    
    time = ofGetElapsedTimef() - timeStamp;
    loader.setTime(time + 130);
    vector <ofVec3f> pt;
    loader.get("/points", pt);
    if (startShape == 0) {
        particles.getVertices().resize(pt.size(),ofVec3f(0));
        particles.getColors().resize(pt.size(), ofFloatColor(
                                                             1.,
                                                             1.,
                                                             1.,
                                                             1.
                                                             )
                                     );
        for (int i=0; i<pt.size(); i++) {
                particles.getVertices()[i].set(ofVec3f(
                                                       5 * pt[i].x - 150,
                                                       - 5 * pt[i].y - 200,
                                                       5 * pt[i].z - 1500
                                                       )
                                               );
                particles.getColors()[i].set(
                                   ofFloatColor(
                                                1.,
                                                1.,
                                                1.,
                                                1
                                                )
                                   );
        }
//        for (int i=pt.size() - 1; i<particleNum; i++) {
//            particles.getVertices()[i].set(particles.getVertices()[i]);
//            particles.getColors()[i].set(
//                                         ofFloatColor(
//                                                      1.,
//                                                      1.,
//                                                      1.,
//                                                      pt.size() * ofNoise(i + time)
//                                                      )
//                                         );
//        }
    }
    else {
        particles.getVertices().resize(particleNum);
        particles.getColors().resize(particleNum);
    }
}

//--------------------------------------------------------------
void abcAnim::draw(int _ptSz){
    ptSz = _ptSz;

    render.begin();
    ofPushStyle();
    {
        ofPushMatrix();
        ofTranslate(W / 2, H / 2);
        render.setUniformTexture("u_posAndAgeTex", pingPong.dst->getTexture(0), 0);
        render.setUniformTexture("sparkTex", sparkImg.getTexture(), 1);
        render.setUniform1f("u_time", time);
        render.setUniform1i("u_startShape", startShape);
        render.setUniform1f("size", (float)ptSz*2);
        render.setUniform1i("resolution", (float)texRes);
        render.setUniform2f("screen", (float)W, (float)H);
        render.setUniform1f("imgWidth", (float)sparkImg.getWidth());
        render.setUniform1f("imgHeight", (float)sparkImg.getHeight());

        ofEnableBlendMode(OF_BLENDMODE_ALPHA);
        ofSetColor(255);
        ofEnablePointSprites();
        particles.draw();
        ofDisablePointSprites();
    
        ofPopMatrix();
    }
    ofPopStyle();
    render.end();
    
    if(showTex){
        ofPushStyle();
        ofEnableBlendMode(OF_BLENDMODE_ALPHA);
        pingPong.dst->getTexture(0).draw(0,0);
        //ofDrawBitmapStringHighlight("Position", 0,14);
        pingPong.dst->getTexture(1).draw(texRes,0);
        //ofDrawBitmapStringHighlight("Velocity", texRes,14);
        ofPopStyle();
    }
}
