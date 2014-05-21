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
#include "Utils.h"
#include "CameraManager.h"
#include "Constants.h"
#include "ofxBeatDetector.h"
#include "Constants.h"

#ifdef USE_KINECT
#include "KinectManager.h"
#endif
class BaseScene {
public:
    BaseScene() { gui = NULL; }
    BaseScene( int a_index, string a_name )
    {
        index = a_index;
        name = a_name;
        gui=NULL;
        shaderDirectory = ofToDataPath( "../../../../../addons/ofxOpenVJ/shaders/" ) ;
    }
    virtual ~BaseScene() {
        if(gui != NULL) { delete gui; gui = NULL;}
        cout << "BaseScene " << name << "->deconstructor()" << endl;
    };
    
    virtual void setup() {};
    virtual void setupGui(float a_x=0, float a_y=0) {
        gui = new ofxUIScrollableCanvas( a_x, a_y, 320, ofGetHeight() - 10 - a_y );
        gui->addWidgetDown(new ofxUILabel(name+" Scene Settings", OFX_UI_FONT_LARGE));
        gui->addSpacer(300, 2);
    };
    //virtual void guiEvent( ofxUIEventArgs & e ) { }
    
    virtual void update() = 0;
    virtual void draw() = 0;
    virtual void drawDebug() {};

    
    virtual void activate() {  };
    virtual void deactivate() { if(gui != NULL) { gui->setVisible(false); } };
    
    void toggleGui() { if(gui!=NULL) {gui->toggleVisible();} };
    
    void loadSettings() {
        if(gui!=NULL) {
            gui->loadSettings( getXMLSettingsName() );
        }
    }
    
    void saveSettings() {
        if(gui!=NULL) {
            cout << "BaseScene :: saveSettings() : " << getXMLSettingsName() << endl;
            gui->saveSettings( getXMLSettingsName() );
        }
    };
    
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

    //Global folder where all shaders are
    string shaderDirectory ;
    
protected:
    float _width, _height;
};













