//
//  KinectßManager.h
//  ofxOpenVJ
//
//  Created by Ben McChesney on 6/12/14 @ #eyeo2014
//
//

#pragma once
#include "ofMain.h"
#include "ofxOpenVJConstants.h"
#include "DepthCameraManager.h"

#include "ofxKinectCommonBridge.h"
#include "ofxUI.h"
#include "ofxOpenCv.h"

class KinectV2Manager : public DepthCameraManager
{
public:
	KinectV2Manager() { } 
    
    //void open();
    //void close();
    //bool isConnected();
    void setup ( ) ; 
    void update();
    void draw();
	void setupGui(float a_x, float a_y) ;
	void guiEvent(ofxUIEventArgs &e) ; 
	bool isConnected( ) ; 
	void calculateCVOperations();
	ofxKinectCommonBridge kinect;
	ofShader yuvRGBShader;
	ofPlanePrimitive plane;

    //void drawDebug();
    
    //bool isFrameNew();
    //float* getDistancePixels();
    //ofVec3f getWorldCoordAt( int x, int y );
    //void setWorldCoord( int x, int y, ofVec3f& inVec );
    
    //ofPoint cvPointToScreen( ofPoint p , float width = ofGetWidth() , float height = ofGetHeight() );
    //ofPoint cvPointToScreen( float x , float y , float width = ofGetWidth() , float height = ofGetHeight() ) { return cvPointToScreen( ofPoint ( x , y ) , width , height  ) ; }
    
	//virtual ofVec3f getWorldCoordAt( int x, int y );
	//virtual ofColor getColorAt( int x , int y ) ; 


	/*
    void setupMesh();
    void calculateMesh( ofVec3f mesh_offset );
    void calculatePoints( ofVec3f a_meshOffset );
    void calculateTriangleMesh( ofVec3f mesh_offset, bool bCalcNormals=true );
    void calculateTriangleStripMesh( ofVec3f mesh_offset, bool bCalcNormals=true );
    ofVec3f getMeshCenter();
    
    ofVec3f& getOffsetVector();
    
    void calculateCVOperations();
    vector<ofPolyline> getScaledContourPolyline( float x, float y, float w, float h );
    vector<ofRectangle> getScaledContourBoundingBoxes( float x, float y, float w, float h );
    
    void guiEvent(ofxUIEventArgs &e);
    void setupGui(float a_x=0, float a_y=0);
    
    void loadSettings();
    void saveSettings();
    */
    //float getWidth( ) { return kinect.getWidth() ;  }
    //float getHeight( ) { return kinect.getHeight() ; }
    /*
    ofxKinect kinect;

    ofxUIScrollableCanvas* gui;
    
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
    int                 maxBlobs ; 
    
    //In dark rooms the colors don't get picked up as well so we have to adjust
    //the raw RGB color
    unsigned char       minimumPixBrightness ;*/
    
protected:
    ofVec3f inverseAxes;
    // in degrees //
    ofVec3f axesRotation;
    float kinectFOV;

};










