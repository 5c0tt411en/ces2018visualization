//
//  circle.hpp
//  ces2018visualization
//
//  Created by scott on 2017/12/25.
//

#ifndef circle_h
#define circle_h

#include "ofMain.h"

class circle {
    public:
        circle(ofVec3f _v);
        void setup();
        void update();
        void draw();
        void resetTimer();
    
        ofVec3f v;
        float   radius,
                time,
                timeStamp;
        int res;
};

#endif /* circle_hpp */
