//
//  BaseScene.h
//  KinectPerformanceV01
//
//  Created by Nick Hardeman on 11/6/12.
//
//

#pragma once
#include "ofMain.h"
#include "ofxOpenVJEvents.h"
#include "ofxOpenVJConstants.h"
//#include "CameraManager.h"
//#include "ofxBeatDetector.h"
#include "DepthCameraManager.h"
#include "Tweenzor.h"
#include "ofxSimpleTimer.h"
#include "SoundManager.h"
#include "CompositorManager.h"
#include "ofxGui.h"
#include "ofxOpenVJUtils.h"
#include "ofxAlphaStackItem.h"

#ifdef USE_KINECT
#include "KinectManager.h"
#endif

class BaseScene : public ofxAlphaStackItem {
public:
    BaseScene() ;
    BaseScene( int a_index, string a_name ) ; 
    virtual ~BaseScene() ;
    
    virtual void setup() {};
    virtual void setupGui(float a_x=0, float a_y=0) ;
    
	virtual void update();
    
    virtual void draw() = 0;
    virtual void drawDebug() ; 

    virtual void activate();
    virtual void deactivate(); 
	virtual void newBeatHandler(); 
    
    void toggleGui()  { bDrawGui = !bDrawGui; }
    //virtual void guiEvent(ofxGui &e) ; 
    
    void loadSettings() ; 
    void saveSettings() ;
	string getSettingsPath(); 

    float getWidth() { return _width; }
    float getHeight() { return _height; }
    void setBounds( float w, float h) { _width = w; _height = h; }
    
    string getXMLSettingsName() { return "GUI/guiSettings_scene_"+name+"_.xml"; }
    string getDefaultShaderDirectory() { return ofToDataPath( "../../../../ofxOpenVJ/shaders/" , true ) ; }

    int index ;
    string name;
    
	bool bDrawGui;
	ofxPanel gui;
    
	
    #ifdef USE_KINECT
    DepthCameraManager* depthCameraManager;
    #endif

    bool bTransitionIn , bTransitionOut ;
    float tweenArgs ;
    //float baseTweenArgs ;
    virtual bool transitionIn( float delay , float transitionTime ) ;
    virtual void transitionInComplete ( ) ; 
    virtual bool transitionOut( float delay , float transitionTime ) ;
    virtual void transitionOutComplete( ) ;
	virtual void drawGui(); 
    
#ifdef USE_KINECT_V2
	DepthCameraManager * depthCameraManager ; 
#endif
    
    SoundManager * soundManager ; 
	CompositorManager * compositorManager;
	ofFbo fbo; 
	void setupCompositor(); 

    bool bVisible ;
    
    void sceneTransitionTimerComplete ( int & args ) ;
    ofxSimpleTimer sceneTransitionTimer ;
    
protected:
    
    float _width, _height;

};













