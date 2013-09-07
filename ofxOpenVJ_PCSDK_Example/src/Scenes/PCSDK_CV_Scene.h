//
//  PCSDK_CV_Scene.h
//  ofxOpenVJ
//
//  Created by Ben McChesney on 6/6/12.
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
  
    
    void activate();
    void deactivate( ) ; 


};
