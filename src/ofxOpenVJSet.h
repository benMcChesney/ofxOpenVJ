//
//  ofxOpenVJSet.h
//  simpleExample
//
//  Created by Ben McChesney on 6/1/14.
//
//

#pragma once

#include "ofxOpenVJ.h"
#include "ofxSimpleTimer.h"
#include "ofxOpenVJEvents.h"
#include "SoundManager.h"

class ofxOpenVJSet
{
    public :
    ofxOpenVJSet() { }
    ~ofxOpenVJSet( ) { }
    
    void setup( int bufferSize );           //Defaults and other calls
    void initialize() ;     //This is called after the scenes have been added
    void addScene( BaseScene * scene ) ;
    
    void exit();
    
	void update();
	void draw();
    
    void setupMainGui();
   // void guiEvent( ofxUIEventArgs& e );
    
    void setDrawGuis( bool bDraw );
    void setSceneBounds();
    void keyPressed ( int key ) ; 
    

	void initKinectV1( ); 
	void initKinectV2( ) ; 
       
    // main gui vars - FPS, shove render FBO over, etc. //
    ofxPanel gui;

   // bool bDrawGui;
    bool bKinectCamGui;
    
    void audioReceived(float* input, int bufferSize, int nChannels);
    
    ofxSimpleTimer sceneTimer ;
    void sceneTimerComplete( int & args ) ;
    
    int getNumScenes( ) { return scenes.size() ; }
    
    void sceneTransitionInHandler( ofxOpenVJEventArgs &args ) ;
    void sceneTransitionOutHandler( ofxOpenVJEventArgs &args ) ;
    
    void transitionToRelativeIndex ( int indexOffset ) ;

	SoundManager* getSoundManager() { return &soundManager;  }
    
protected :
#ifdef USE_KINECT
    DepthCameraManager    *    depthCameraManager;
#endif
    
#ifdef USE_KINECT_V2
	DepthCameraManager	* depthCameraManager ; 
#endif

    //CameraManager        cameraManager ;
    SoundManager        soundManager ;
    
    vector<BaseScene*> scenes;
    
    int activeSceneIndex;
    
    //float setTransitionTime , setDelayTime ; 

	//Gui
	ofxIntSlider projectorWidth;
	ofxIntSlider projectorHeight; 
	
	ofxToggle bDrawDebug;
	bool bDrawGui; 
	ofxToggle bAutoSceneSwitch;
	ofxFloatSlider setTransitionTime;
	ofxFloatSlider setDelayTime;

	
};
