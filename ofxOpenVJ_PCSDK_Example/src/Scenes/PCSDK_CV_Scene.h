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

class PCSDK_CV_Scene : public BaseScene {
public:
    PCSDK_CV_Scene();
    PCSDK_CV_Scene( int a_index, string a_name ):BaseScene( a_index, a_name ) {}
    ~PCSDK_CV_Scene();
    
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
    float extrudeDepth ;
    float extrudeNoiseStrength ;
    
//    float zOffset ;
//    float pointCloudMinZ , pointCloudMaxZ ;

    float meshHueTimeMultiplier ;
    float meshHueRangeMin , meshHueRangeMax ;
    
    float triangleSizeMax ;
    float triangleSizeMin ;
    ofShader shader ; 
};
