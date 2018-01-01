//
//  hamonMov.cpp
//  ces2018visualization
//
//  Created by scott on 2018/01/01.
//

#include "hamonMov.h"

hamonMov::hamonMov(int _movIndex) {
    switch (_movIndex) {
        case 1:
            hamon.load("movies/01_camera.mov");
            break;
        case 2:
            hamon.load("movies/01_front_720p.mov");
            break;
        case 3:
            hamon.load("movies/02_camera.mov");
            break;
        case 4:
            hamon.load("movies/02_front.mov");
            break;
    }
}

void hamonMov::setup() {
    hamon.play();
}

void hamonMov::update(float _frame) {
    hamon.update();
    hamon.setPaused(true);
    hamon.nextFrame();
    
    frame = int(_frame);
    
    ofLog() << "video frame number: " << frame << endl;

    if (frame == prevFrame + 1) {
        ofLog() << "frame = prevFrame + 1: " << frame << endl;
        
        prevFrame = frame;
    }
    else if (frame == prevFrame) {
        ofLog() << "frame = prevFrame: " << frame << endl;
//        hamon.nextFrame();
        prevFrame = frame + 1;
    }
    else {
        ofLog() << "else: " << frame << endl;
//        hamon.setFrame(frame);
        prevFrame = frame;
    }

}

void hamonMov::draw() {
    ofPushStyle();
    {
        ofEnableBlendMode(OF_BLENDMODE_ADD);
        hamon.draw(0, 0, W, H);
    }
    ofPopStyle();
}
