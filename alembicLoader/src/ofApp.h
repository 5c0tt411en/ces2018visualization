#pragma once

#include "ofMain.h"
#include "ofxAlembic.h"
#define W 1920
#define H 1080

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
    
    float easeOutCubic(float t, float b, float c, float d);
		
    ofxAlembic::Reader loader;
    float   time,
            timeStamp;
    bool start;
    ofCamera cam;
    int mode = 1;
    ofVec3f randomPos[50];
    int randomNum;
    ofImage sphereImg;
};
