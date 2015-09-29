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

class RippleTunnelScene : public BaseScene {
public:
    RippleTunnelScene();
    RippleTunnelScene( int a_index, string a_name ):BaseScene( a_index, a_name ) {}
    ~RippleTunnelScene();
    
    void setup();
    void setupGui(float a_x=0, float a_y=0);
//    void guiEvent(ofxUIEventArgs &e);
    
    void update();
    void draw();

    
    bool transitionIn( float delay , float transitionTime );
    bool transitionOut( float delay , float transitionTime ) ;

    ofShader shader ; 
    
    float alpha ;
     ofFbo fbo ; 
    
};
