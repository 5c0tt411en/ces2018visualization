#include "ofMain.h"
#include "ofApp.h"

//========================================================================
int main( ){
#ifdef DEBUG
	ofSetupOpenGL(1920,1080,OF_WINDOW);			// <-------- setup the GL context

	ofRunApp(new ofApp());
#else
    ofGLFWWindowSettings settings;

    settings.width = 1920;
    settings.height = 1080;
    
    settings.decorated = false;
    
    shared_ptr<ofAppBaseWindow> mainWindow = ofCreateWindow(settings);
    shared_ptr<ofApp> mainApp(new ofApp);
    
    ofRunApp(mainWindow, mainApp);
    ofRunMainLoop();
#endif
}
