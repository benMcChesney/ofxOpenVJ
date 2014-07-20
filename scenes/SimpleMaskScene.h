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
#include "ofxSimpleMask.h"

class SimpleMaskScene : public BaseScene {
public:
    SimpleMaskScene();
    SimpleMaskScene( int a_index, string a_name ):BaseScene( a_index, a_name ) {}
    ~SimpleMaskScene();
    
    void setup();
    void setupGui(float a_x=0, float a_y=0);
    void guiEvent(ofxUIEventArgs &e);
    
    void update();
    void draw();
    void drawDebug();
    
    ofShader shader ; 
    ofFbo fbo ;
    
    ofFbo maskFbo ;
    ofxSimpleMask simpleMask  ;
    
    float maskFadeAmount ;
    
    float offsetAmount ; 
    float decayAmount ;
    
    bool transitionIn( float delay , float transitionTime );
    bool transitionOut( float delay , float transitionTime ) ;
    
    float timeScale ;
    float maxShaderValue ; 
    float alpha ; 
};


