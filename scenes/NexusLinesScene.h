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
#include "NexusLine.h"


class NexusLinesScene : public BaseScene {
public:
    NexusLinesScene();
    NexusLinesScene( int a_index, string a_name ):BaseScene( a_index, a_name ) {}
    ~NexusLinesScene();
    
    void setup();
    void setupGui(float a_x=0, float a_y=0);
    void guiEvent(ofxUIEventArgs &e);
    void drawDebug( ) ; 
    
    void update();
    void draw();
    
    bool transitionIn( float delay , float transitionTime );
    bool transitionOut( float delay , float transitionTime ) ;
    
    float completion ;
    
    vector< NexusLine* > lines;
    void addNewLine() ;
    
    float minTravelTime, maxTravelTime ;
    
    ofImage logo ; 

};
