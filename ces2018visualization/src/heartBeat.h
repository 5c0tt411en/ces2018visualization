//
//  heartBeat.hpp
//  ces2018visualization
//
//  Created by scott on 2017/12/25.
//

#ifndef heartBeat_h
#define heartBeat_h

#include "ofMain.h"

#define W 1920
#define H 1080

class heartBeat {
    public:
        heartBeat();
        void setup();
        void update();
        void draw();
        void resetTimer();
    
    ofFbo   maskFbo;
    ofPath  path;
    float   time,
            timeStamp,
            oneCycle = 2.,
            bWidth = 20.;
    ofImage maskedImage;
};

#endif /* heartBeat_hpp */
