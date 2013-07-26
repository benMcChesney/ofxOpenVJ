//
//  KinectManager.h
//  Double_Kinect_Tests
//
//  Created by Nick Hardeman on 11/5/12.
//
//

#pragma once

#define INTEL_PCSDK 3
#include "ofMain.h"
#include "Constants.h"


#ifdef INTEL_PCSDK
#include "pxcupipeline.h"
#endif

#ifndef INTEL_PCSDK
#include "ofxKinect.h"
#endif
//
#include "ofxUI.h"
#include "ofxOpenCv.h"
//#include "ofxPostProcessing.h"
class PCSDKManager {
public:
    PCSDKManager();
    
    void open();
    void close();
    bool isConnected();
    
    void update();
    void draw();
    void drawDebug();
    
    bool isFrameNew();
    //float* getDistancePixels();
    ofVec3f getWorldCoordAt( int x, int y );
    void setWorldCoord( int x, int y, ofVec3f& inVec );
	ofColor getColorAt( int x , int y ) ; 
    
    void setupMesh();
    void calculateMesh( ofVec3f mesh_offset );
    void calculatePoints( ofVec3f a_meshOffset );
    void calculateTriangleMesh( ofVec3f mesh_offset, bool bCalcNormals=true );
    void calculateTriangleStripMesh( ofVec3f mesh_offset, bool bCalcNormals=true );
	void calculateCVOpertions( ) ; 
	void calculatePointCloud( ) ; 

    ofVec3f getMeshCenter();
    
    ofVec3f& getOffsetVector();
    
    void calculateCVOperations();
    vector<ofPolyline> getScaledContourPolyline( float x, float y, float w, float h );
    vector<ofRectangle> getScaledContourBoundingBoxes( float x, float y, float w, float h );
    
    void guiEvent(ofxUIEventArgs &e);
    void setupGui(float a_x=0, float a_y=0);
    
    void loadSettings();
    void saveSettings();
    
    //ofxKinect kinect;

    ofxUIScrollableCanvas* gui;

	float getWidth() { return depthImage.getWidth() ; } 
	float getHeight() { return depthImage.getHeight() ; } 
    

    // open cv work, for use with 2D elements //
    ofxCvGrayscaleImage grayImage; // grayscale depth image
    //ofxCvGrayscaleImage grayImageSmall; // we don't need that big ass image //
	ofxCvGrayscaleImage grayThreshNear; // the near thresholded image
	ofxCvGrayscaleImage grayThreshFar; // the far thresholded image
	ofxCvContourFinder contourFinder;
    
    bool* bPointsActive;
    
    int                 nearThreshold, farThreshold;
    int                 nearThreshCV, farThreshCV;
    
    ofMesh              mesh;
    int                 width, height;
    
    float               scale;
    int                 step;
    bool                bUseVideoColor;
    // how far can the pixels be before it is considered fucked? //
    float               maxTriDiff;
    
    ofVec3f             offsetVec;
    
    //Global settings for point clouds
    float               pointCloudMaxZ , pointCloudMinZ ;
    float               pointCloudZOffset ;
    bool                bFindHoles ;
    float               minBlobSize , maxBlobSize ;
    
    //In dark rooms the colors don't get picked up as well so we have to adjust
    //the raw RGB color
    unsigned char       minimumPixBrightness ;
    
    //ofxPostProcessing post ;
    
    void disableAllPostProcessing() ; 

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

	ofImage depthImage ; 
	vector<ofVec3f> pts ; 
	//ofImage colorImage ; 
    
protected:
    ofVec3f inverseAxes;
    // in degrees //
    ofVec3f axesRotation;
    float kinectFOV;
    bool bThreshWithOpenCV;
};










