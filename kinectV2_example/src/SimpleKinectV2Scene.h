//
//  SimpleOpenCVScene
//  KinectPerformanceV01
//
//  Created by Ben Mcchesney on 11/6/12.
//
//

#pragma once 
#include "BaseScene.h"
#include "ofxTweenzor.h"
#include "KinectV2Manager.h"

class SimpleKinectV2Scene : public BaseScene {
public:
    SimpleKinectV2Scene();
    SimpleKinectV2Scene( int a_index, string a_name ):BaseScene( a_index, a_name ) {}
    ~SimpleKinectV2Scene();
    
    void setup();
    void setupGui(float a_x=0, float a_y=0);
    void guiEvent(ofxUIEventArgs &e);
    
    void update();
    void draw();
    
    void activate();
    void deactivate();
};
