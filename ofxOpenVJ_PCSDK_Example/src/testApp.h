#pragma once

#define INTEL_PCSDK 3

#include "ofMain.h"
#include "Constants.h"
#include "Scenes/Scenes.h"

#ifdef INTEL_PCSDK
#include "PCSDKManager.h"
#endif 

#ifndef INTEL_PCSDK
#inlclude "KinectManager.h"
#endif

#include "CameraManager.h"
#include "Tweenzor.h"
#include "FftManager.h"

#define INTEL_PCSDK 3

class testApp : public ofBaseApp{

  public:
	void setup();
    void exit();

	void update();
	void draw();
    
    void setupMainGui();
    void guiEvent( ofxUIEventArgs& e );
    
    void setDrawGuis( bool bDraw );
    void setSceneBounds();

	void keyPressed  (int key);
	void keyReleased(int key);
	void mouseMoved(int x, int y );
	void mouseDragged(int x, int y, int button);
	void mousePressed(int x, int y, int button);
	void mouseReleased(int x, int y, int button);
	void windowResized(int w, int h);
	void dragEvent(ofDragInfo dragInfo);
	void gotMessage(ofMessage msg);
    
    float zOffset ; 
    PCSDKManager   pcsdkMan;
    CameraManager   cameraManager ;
    FftManager      fftManager ;
    
    vector<BaseScene*> scenes;

    float lastSceneChangedTime ;
    float sceneDelayTime ; 
    int activeSceneIndex;
    // main gui vars - FPS, shove render FBO over, etc. //
    ofxUICanvas* gui;
    
    float fboShoveX;
    bool bShoveOver;
    bool bDrawGui;
    bool bAutoSceneSwitch;
    bool bKinectCamGui;
    
    ofFbo fbo;
    
    ofImage bug;

	int pixelStep ; 


	
};
