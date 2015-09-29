//
//  ColorOutlineScene
//  KinectPerformanceV01
//
//
//

#pragma once
#include "BaseScene.h"
#include "Utils.h"
#include "ofxParticle2D.h"

class ColorOutlineScene : public BaseScene {
public:
    ColorOutlineScene();
    ColorOutlineScene( int a_index, string a_name ):BaseScene( a_index, a_name ) {}
    ~ColorOutlineScene();
    
    void setup();
    void setupGui(float a_x=0, float a_y=0);
//    void guiEvent(ofxUIEventArgs &e);
    
    void addContour();
    
    void update();
    void draw();
    void drawDebug();
    
    vector< ofPath > lines;
    vector<ofVec3f> offsets ; 
    vector<ofxParticle2D> particles;
    vector<ofColor> colors; 
    
    int lastAddTime;
    float hue;
    float hueDir;
    float alpha ; 
    bool bOdd;
    
    float millisDelay ;
    float contourSoundThreshold ;
    
    float hueIncrement ;
    float hueNoiseOffset ;
    float radiusTime ; 
    float zForce ; 
    float radius ;
    float spiralFactor ;
    float specialZOffset ;
    float noiseZMultiplier ;
    
    int resampleLineAmount ;
    int numTooManyOffset ;
    
    bool transitionIn( float delay , float transitionTime );
    bool transitionOut( float delay , float transitionTime ) ;
    void debugDraw ( ) ;
    
    
    ofPoint offset ; 
};
