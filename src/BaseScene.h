//
//  BaseScene.h
//  KinectPerformanceV01
//
//  Created by Nick Hardeman on 11/6/12.
//
//

#pragma once
#include "ofMain.h"
#include "ofxUI.h"
#include "ofxOpenVJConstants.h"
#include "CameraManager.h"
#include "ofxBeatDetector.h"


#ifdef USE_KINECT
#include "KinectManager.h"
#endif

class BaseScene {
public:
    BaseScene() ;
    BaseScene( int a_index, string a_name ) ; 
    virtual ~BaseScene() ;
    
    virtual void setup() {};
    virtual void setupGui(float a_x=0, float a_y=0) ;
    
    virtual void update() = 0;
    virtual void draw() = 0;
    virtual void drawDebug() {};

    virtual void activate() {  };
    virtual void deactivate() { if(gui != NULL) { gui->setVisible(false); } };
    
    void toggleGui() { if(gui!=NULL) {gui->toggleVisible();} };
    virtual void guiEvent(ofxUIEventArgs &e) ; 
    
    void loadSettings() ; 
    void saveSettings() ;
    
    float getWidth() { return _width; }
    float getHeight() { return _height; }
    void setBounds( float w, float h) { _width = w; _height = h; }
    
    string getXMLSettingsName() { return "GUI/guiSettings_scene_"+name+"_.xml"; }
    
    int index = -1;
    string name;
    
    ofxUIScrollableCanvas* gui;
    
    #ifdef USE_KINECT
    KinectManager* kinectMan;
    #endif
    
    ofxBeatDetector * beatDetector ;
    CameraManager* cameraMan;
    
protected:
    float _width, _height;
};













