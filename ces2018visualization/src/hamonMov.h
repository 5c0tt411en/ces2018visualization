//
//  hamonMov.h
//  ces2018visualization
//
//  Created by scott on 2018/01/01.
//

#ifndef hamonMov_h
#define hamonMov_h

#include "ofMain.h"

#define W 1920
#define H 1080
#define TOTAL_FRAME 18780

class hamonMov {
    public:
        hamonMov(int _movIndex);
        void setup();
        void update(float _frame);
        void draw();
    
    ofVideoPlayer hamon;
    int prevFrame,
        frame;
};

#endif /* hamonMov_h */
