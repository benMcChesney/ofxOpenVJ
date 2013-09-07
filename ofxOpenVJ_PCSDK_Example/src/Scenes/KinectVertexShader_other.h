//
//  TestScene.h
//  KinectPerformanceV01
//
//  Created by Ben Mcchesney on 11/6/12.
//
//

#pragma once 
#include "BaseScene.h"
#include "ofxTweenzor.h"

class KinectVertexShader_other : public BaseScene {
public:
    KinectVertexShader_other();
    KinectVertexShader_other( int a_index, string a_name ):BaseScene( a_index, a_name ) {}
    ~KinectVertexShader_other();
    
    void setup();
    void setupGui(float a_x=0, float a_y=0);
    void guiEvent(ofxUIEventArgs &e);
    
    float redrawAlpha ; 
    
    void update();
    void draw();
    void drawPointCloud( ) ;
    
    void activate();
    void deactivate();

    bool bToggleTrails ;
    float fadeAmount ;

    ofFbo trailFbo ;
    float fboFadeAmount ;
    ofShader shader ;
    bool bDrawShader ;
    
    float boxSize ;
    float pixelSampling ;
    float hueTimeMultiplier ;
    float rotationTimeMultiplier ;
    
     float shaderVar1 , shaderVar2 , shaderVar3 , shaderVar4 ;
    
    float boxStep ; 
};