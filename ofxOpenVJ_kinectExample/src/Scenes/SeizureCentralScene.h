//
//  SeizureCentral.h
//  KinectPerformanceV01
//
//  Created by Nick Hardeman on 11/6/12.
//
//

#pragma once
#include "BaseScene.h"
#include "ofxParticle2D.h"

class SeizureCentralScene : public BaseScene {
public:
    SeizureCentralScene();
    SeizureCentralScene( int a_index, string a_name ):BaseScene( a_index, a_name ) {}
    ~SeizureCentralScene();
    
    void setup();
    void setupGui(float a_x=0, float a_y=0);
    void guiEvent(ofxUIEventArgs &e);
    
    void addContour();
    
    void update();
    void draw();
    void drawDebug();
    
    void activate();
    void deactivate();
    
    vector<ofMesh> lines;
    vector<ofVec3f> offsets ; 
    vector<ofxParticle2D> particles;
    vector<ofColor> colors; 
    
    int lastAddTime;
    float hue;
    float hueDir;
    
    bool bOdd;
    
    float millisDelay ;
    float contourSoundThreshold ;
    
    float hueIncrement ;
    float hueNoiseOffset ;
    float radiusTime ; 
    float zForce ; 
    float radius ;
    float spiralFactor ;
    
    int numTooManyOffset ; 
};
