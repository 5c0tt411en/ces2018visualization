//
//  scene07.cpp
//  OOPARTS2017
//
//  Created by scott on 2017/09/09.
//
//

#include "scene07.hpp"

scene07::scene07() {
    
}

void scene07::setup() {
    // initialize variables:
    
    isShaderDirty = true;  // this flag will tell us whether to reload our shader from disk.
    // this allows you to change your shaders without having to restart
    // your app. we'll set it up so that pressing the SPACE key on your
    // keyboard will reload the shader.
    
    // initialize screen, lock framerate to vsync:
    
//    ofSetFrameRate(0);
//    ofSetVerticalSync(true);
    
    
    // generate a box vboMesh from a primitive.
    
    ofBoxPrimitive tmpBox;
    // set the size to be 2 units.
    tmpBox.set(2);
    
    mVboBox = tmpBox.getMesh();
    
    // load depth image
    ofDisableArbTex();
    // note that we disable arb tex, meaning we will use normalized texture coordinates,
    // where a texture's x and y coordinate are each expressed as a normalized float.
    // this makes things slightly easier in the shader.
    
    // load the depth image into our texture
    ofLoadImage(mTexDepth, "images/ces2018.png");
    ofEnableArbTex();

}

void scene07::update() {
    if (isShaderDirty){
        
        // only reload the shader if it is 'dirty', i.e. the user has either requested reloading
        // or the 'isShaderDirty' flag has been initialized to true in setup()
        
        // Since we are using a shared_ptr around the shader, the old shader will get destroyed
        // automatically as soon as we assign a new shader object to our mShdInstanced.
        
        ofLogNotice() << "Reloading Shader.";
        mShdInstanced = shared_ptr<ofShader>(new ofShader());
        // most of the instanced drawing magic happens in the shaders:
#ifdef USE_PROGRAMMABLE_GL
        // if we are using programmable GL, we load the GLSL version 150 shader pair.
        mShdInstanced->load("shaders/scene07/instanced.vert", "shaders/scene07/instanced.frag");
#else
        // if we are using fixed function GL, we load the GLSL version 120 shader pair.
        mShdInstanced->load("shaders/scene07/instanced_120.vert", "shaders/scene07/instanced_120.frag");
#endif
        GLint err = glGetError();
        if (err != GL_NO_ERROR){
            ofLogNotice() << "Load Shader came back with GL error:	" << err;
        }
        
        isShaderDirty = false;
    }
}

void scene07::draw(ofColor _cScene07) {
    ofPushStyle();
    {
        ofEnableDepthTest();
        // we don't care about alpha blending in this example, and by default alpha blending is on in openFrameworks > 0.8.0
        // so we de-activate it for now.
//        ofDisableAlphaBlending();
        ofEnableBlendMode(OF_BLENDMODE_ALPHA);
        ofSetColor(_cScene07);
        
        // bind the shader
        mShdInstanced->begin();
        // give the shader access to our texture
        mShdInstanced->setUniformTexture("tex0", mTexDepth, 0);
        // feed the shader a normalized float value that changes over time, to animate things a little
        mShdInstanced->setUniform1f("timeValue", (ofGetElapsedTimeMillis() % 30000) / 30000.0f);
        mShdInstanced->setUniform4f("col", _cScene07.r/255.0, _cScene07.g/255.0, _cScene07.b/255.0, _cScene07.a/255.0);
        // we only want to see triangles facing the camera.
        glEnable(GL_CULL_FACE);
        glCullFace(GL_BACK);
        
        ofPushMatrix();
        ofRotate(90, 1, 0, 0);
        ofTranslate(128 * 15 / 2, 0, -128 * 15 / 4);
        // let's draw 128 * 128 == 16384 boxes !
        mVboBox.drawInstanced(OF_MESH_FILL, 128*128);
        
        ofPopMatrix();
        
        glDisable(GL_CULL_FACE);
        mShdInstanced->end();
        
        
        ofDisableDepthTest();
        //    ofDrawBitmapString("Use mouse to move camera.\nPress 'f' to toggle fullscreen;\nSPACEBAR to reload shader.", 10, 20);
        
        ofEnableAlphaBlending();
    }
    ofPopStyle();
}
