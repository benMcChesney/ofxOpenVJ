//
//  BoxOffsetScene.h
//  KinectPerformanceV01
//
//  Created by Nick Hardeman on 11/7/12.
//
//

#pragma once
#include "BaseScene.h"

class BoxOffsetScene : public BaseScene {
public:
    BoxOffsetScene();
    BoxOffsetScene( int a_index, string a_name ):BaseScene( a_index, a_name ) {}
    ~BoxOffsetScene();
    
    void setup();
    void setupGui(float a_x=0, float a_y=0);
    void guiEvent(ofxUIEventArgs &e);
    
    void update();
    void draw();
    void drawDebug();
    
    void activate();
    void deactivate();
    
    float energy;
    ofRectangle targetRect;
    ofRectangle blobRect;
    
    int mode;
    
    int numBeatHits;
    float maxBeatHits;
    float angle;
};


