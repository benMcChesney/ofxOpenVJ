#pragma once

#include "ofMain.h"
#include "Constants.h"
#include "Scenes/Scenes.h"
#include "KinectManager.h"
#include "CameraManager.h"
#include "Tweenzor.h"
#include "FftManager.h"
#include "ofxSyphon.h"

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
    KinectManager   kinectMan;
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
    
    ofxSyphonServer outputSyphonServer ;
};
