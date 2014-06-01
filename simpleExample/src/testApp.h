#pragma once

#include "ofMain.h"
#include "ofxOpenVJ.h"
#include "Tweenzor.h"
#include "SceneList.h"


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
    
    #ifdef USE_KINECT
    KinectManager        kinectMan;
    #endif
    
    CameraManager        cameraManager ;
    ofxBeatDetector      beatDetector ;
    
    vector<BaseScene*> scenes;

    float lastSceneChangedTime ;
    float sceneDelayTime ; 
    int activeSceneIndex;
    // main gui vars - FPS, shove render FBO over, etc. //
    ofxUICanvas* gui;
    
    bool bDrawGui;
    bool bAutoSceneSwitch;
    bool bKinectCamGui;
    
    void audioReceived(float* input, int bufferSize, int nChannels);
    float beatValue ; 
    

#ifdef USE_SYPHON
    //ofxSyphonServer outputSyphonServer ;
#endif

};
