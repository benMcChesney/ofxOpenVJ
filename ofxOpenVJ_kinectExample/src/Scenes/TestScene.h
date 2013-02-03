//
//  TestScene.h
//  KinectPerformanceV01
//
//  Created by Nick Hardeman on 11/6/12.
//
//  Base Scene
//

#pragma once 
#include "BaseScene.h"

class TestScene : public BaseScene {
public:
    TestScene();
    TestScene( int a_index, string a_name ):BaseScene( a_index, a_name ) {}
    ~TestScene();
    
    void setup();
    void setupGui(float a_x=0, float a_y=0);
    void guiEvent(ofxUIEventArgs &e);
    
    void update();
    void draw();
    
    void activate();
    void deactivate();
    
};
