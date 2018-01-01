//
//  hamonObj.hpp
//  ces2018visualization
//
//  Created by scott on 2017/12/26.
//

#ifndef hamonObj_h
#define hamonObj_h

#include "ofMain.h"
#include "ofxPDF.h"

#define W 1920
#define H 1080

class hamonObj {
    public:
        hamonObj(string _type, float _drawP, float _stay, float _erase);
        void setup();
        void update();
        void draw();
        void resetTimer();
        float easeOutCubic(float t, float b, float c, float d);
    
        enum State {
            DRAW,
            STAY,
            ERASE,
            END
        };
        State stat;
        ofxPDF pdf;
        float step;
        vector<ofPolyline> outlines;
    
        float   time,
        timeStamp,
        drawP,
        stay,
        erase;
        string type;
        ofVec3f rotateRan;
};

#endif /* hamonObj_h */
