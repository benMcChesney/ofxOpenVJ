//
//  SimplePointCloudScene
//  KinectPerformanceV01
//
//  Created by Ben Mcchesney 
//
//

#pragma once 
#include "BaseScene.h"
#include "ofxTweenzor.h"

class SimplePointCloudScene : public BaseScene {
public:
    SimplePointCloudScene();
    SimplePointCloudScene( int a_index, string a_name ):BaseScene( a_index, a_name ) {}
    ~SimplePointCloudScene();
    
    void setup();
    void setupGui(float a_x=0, float a_y=0);
    void guiEvent(ofxUIEventArgs &e);
    
    void update();
    void draw();
    
    void activate();
    void deactivate();
    
    float zTimeMultiplier ;
    float zNoiseAmount ;
    float pixelStep ;
    float pointSize ; 
};
