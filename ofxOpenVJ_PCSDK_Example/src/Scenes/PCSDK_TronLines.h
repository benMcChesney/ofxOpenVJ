//
//  PCSDK_TronLines.cpp
//  KinectPerformanceV01
//
//  Created by Ben McChesney on 7/25/2013.
//
//
#pragma once 
#include "BaseScene.h"
#include "ofxTweenzor.h"

class PCSDK_TronLines : public BaseScene {
public:
    PCSDK_TronLines();
    PCSDK_TronLines( int a_index, string a_name ):BaseScene( a_index, a_name ) {}
    ~PCSDK_TronLines();
    
    void setup();
    void setupGui(float a_x=0, float a_y=0);
    void guiEvent(ofxUIEventArgs &e);
    
    void update();
    void draw();
    void drawPointCloud( ) ;
    
    void activate();
    void deactivate();

    float extrudeDepth ; 
	float lineRowSkip ; 
};
