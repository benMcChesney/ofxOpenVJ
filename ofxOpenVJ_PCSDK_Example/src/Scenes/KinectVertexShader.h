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

class KinectVertexShader : public BaseScene {
public:
    KinectVertexShader();
    KinectVertexShader( int a_index, string a_name ):BaseScene( a_index, a_name ) {}
    ~KinectVertexShader();
    
    void setup();
    void setupGui(float a_x=0, float a_y=0);
    void guiEvent(ofxUIEventArgs &e);
         
    void update();
    void draw();
    void drawPointCloud( ) ;
    
    void activate();
    void deactivate();

    ofShader shader ;
    bool bDrawShader ;
    
    float boxSize ;
    float pixelSampling ;
    float hueTimeMultiplier ;
    float rotationTimeMultiplier ;
    
     float shaderVar1 , shaderVar2 , shaderVar3 , shaderVar4 ;
    
    float boxStep ; 
};
