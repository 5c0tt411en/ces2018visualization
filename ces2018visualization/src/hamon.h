//
//  hamon.hpp
//  ces2018visualization
//
//  Created by scott on 2017/12/25.
//

#ifndef hamon_h
#define hamon_h

#include "ofMain.h"
#include "ofxPDF.h"

#define W 1920
#define H 1080

class hamon {
    public:
        hamon(string _type, float _drawP, float _stay, float _erase);
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
};

#endif /* hamon_h */
