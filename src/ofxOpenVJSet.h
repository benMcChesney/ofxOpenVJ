//
//  ofxOpenVJSet.h
//  simpleExample
//
//  Created by Ben McChesney on 6/1/14.
//
//

#pragma once

#include "ofxOpenVJ.h"

class ofxOpenVJSet
{
    public :
    ofxOpenVJSet() { }
    ~ofxOpenVJSet( ) { }
    
    void setup();           //Defaults and other calls
    void initialize() ;     //This is called after the scenes have been added
    
    void exit();
    
	void update();
	void draw();
    
    void setupMainGui();
    void guiEvent( ofxUIEventArgs& e );
    
    void setDrawGuis( bool bDraw );
    void setSceneBounds();
    void keyPressed ( int key ) ; 

#ifdef USE_KINECT
    KinectManager        kinectMan;
#endif
    
    CameraManager        cameraManager ;
    ofxBeatDetector      beatDetector ;
    
    vector<BaseScene*> scenes;
    int activeSceneIndex;
    
    // main gui vars - FPS, shove render FBO over, etc. //
    ofxUICanvas* gui;

    bool bDrawGui;
    bool bAutoSceneSwitch;
    bool bKinectCamGui;
    
    void audioReceived(float* input, int bufferSize, int nChannels);
    float beatValue ;

};
