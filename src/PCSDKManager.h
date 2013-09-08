//
//  PCSDKManager.h
//  ofxOpenVJ
//
//  Created by Ben McChesney on 6/5/12.
//
//

#pragma once

#define INTEL_PCSDK 3
#include "ofMain.h"
#include "Constants.h"


#ifdef INTEL_PCSDK
#include "pxcupipeline.h"
#endif

//
#include "ofxUI.h"
#include "ofxOpenCv.h"
#include "DepthCameraManager.h"

class PCSDKManager : public DepthCameraManager {
public:
    PCSDKManager();
    
    virtual void open();
    virtual void close();
    virtual bool isConnected();
    
    virtual void update();
    virtual void draw();
    virtual void drawDebug();
    
    bool isFrameNew();
    //float* getDistancePixels();
    virtual ofVec3f getWorldCoordAt( int x, int y );

	virtual ofColor getColorAt( int x , int y ) ; 
    
	virtual void calculateCVOperations( ) ; 
	virtual void calculatePointCloud( ) ; 
    
    virtual void guiEvent(ofxUIEventArgs &e);
    virtual void setupGui(float a_x=0, float a_y=0);
    
    virtual void loadSettings();
    virtual void saveSettings();
    
   


    

	/* PCSDK Stuff... */
	bool mColor;
	int mDW, mDH, mCW, mCH, mSkip, mTotal;
	float mScale, mXOffset, mYOffset;
	short *mDepthMap;

	float *mUVMap;
	unsigned char *mRGBMap;
	vector<ofVec3f> mVerts;
	vector<ofFloatColor> mColors;
//	vector<string> mSteps;

	PXCUPipeline_Instance mSession;


    
protected:
    ofVec3f inverseAxes;
    // in degrees //
    ofVec3f axesRotation;
    float kinectFOV;
    bool bThreshWithOpenCV;
};










