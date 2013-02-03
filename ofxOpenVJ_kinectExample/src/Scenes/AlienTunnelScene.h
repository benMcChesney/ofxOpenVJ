//
//  TestScene.h
//  KinectPerformanceV01
//
//  Created by Ben Mcchesney on 11/6/12.
//
//

#pragma once 
#include "BaseScene.h"
#include "Tweenzor.h"

class AlienTunnelScene : public BaseScene {
public:
    AlienTunnelScene();
    AlienTunnelScene( int a_index, string a_name ):BaseScene( a_index, a_name ) {}
    ~AlienTunnelScene();
    
    void setup();
    void setupGui(float a_x=0, float a_y=0);
    void guiEvent(ofxUIEventArgs &e);
    
    void update();
    void draw();
    void drawDebug();
    
    void activate();
    void deactivate();
    
    ofShader shader;
};
