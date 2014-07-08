//
//  SimpleOpenCVScene
//  KinectPerformanceV01
//
//  Created by Ben Mcchesney on 11/6/12.
//
//

#pragma once 
#include "BaseScene.h"
#include "ofxTweenzor.h"

class SimpleOpenCVScene : public BaseScene {
public:
    SimpleOpenCVScene();
    SimpleOpenCVScene( int a_index, string a_name ):BaseScene( a_index, a_name ) {}
    ~SimpleOpenCVScene();
    
    void setup();
    void setupGui(float a_x=0, float a_y=0);
    void guiEvent(ofxUIEventArgs &e);
    
    void update();
    void draw();
    
    float outlineSmoothing ;
    vector< ofPath > paths ;
    
    bool transitionIn( float delay , float transitionTime );
    bool transitionOut( float delay , float transitionTime ) ;
    
    ofRectangle boundingBox ; 
    float completion ; 
};
