/*
    EmptyScene
    ofxOpenVJ
 
    Created by Ben Mcchesney on 6/1/14.
 
    This class serves as the most basic functionalities a ofxOpenVJ scene should have
    When creating a new scene it's recommended to copy this one and rename it as a starting point
 
*/

#pragma once 
#include "BaseScene.h"
#include "ofxBox2d.h"
#include "Tweenzor.h"
#include "ColorPalette.h"

class Outline2dShatterScene : public BaseScene {
public:
    Outline2dShatterScene();
    Outline2dShatterScene( int a_index, string a_name ):BaseScene( a_index, a_name )
    {
        Outline2dShatterScene() ;
    }
    ~Outline2dShatterScene();
    
    void setup();
    void setupGui(float a_x=0, float a_y=0);
    void guiEvent(ofxUIEventArgs &e);
    
    void update();
    void draw();
    
    void activate();
    void deactivate();

    ofPolyline                          shape;
    ofPath                              path ;
	ofxBox2d                            box2d;
	vector <ofPtr<ofxBox2dCircle> >     circles;
	vector <ofPtr<ofxBox2dPolygon> >	polyShapes;
    vector < ofColor >	polyColors ;
    bool bDrawFeeds ;
    
    ColorPalette set1 ;
    ColorPalette set2 ;
    bool bUseSet1 ;

    bool bDoCreateShapes ;
    void upTweenComplete( float * args ) ;
    float tweenArgs ;
    float tweenLength ;
    
    float flashAlpha ;
    float flashTime ;
    float maxFlash ;
    
    float density ;
    float friction ;
    float bounce ;
    
    float startForce ;
    float decay ;
    float currentForce ;
    ofPoint forceOrigin ;
    float smoothing ;
    
    
    float fboFade ;
    ofFbo fbo ;
};
