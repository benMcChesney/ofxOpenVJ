//
//  KinectManager.h
//  Double_Kinect_Tests
//
//  Created by Nick Hardeman on 11/5/12.
//
//

#pragma once
#include "ofMain.h"
#include "ofxOpenVJConstants.h"
#include "DepthCameraManager.h"
#include "ofxKinect.h"
#include "ofxUI.h"
#include "ofxOpenCv.h"

class KinectManager : public DepthCameraManager
{
public:
    KinectManager();
    
    void open();
    void close();
    bool isConnected();
    
    void update();
    void draw();
    void drawDebug();
    
    bool isFrameNew();
    float* getDistancePixels();
    void setWorldCoord( int x, int y, ofVec3f& inVec );
    
    ofPoint cvPointToScreen( ofPoint p , float width = ofGetWidth() , float height = ofGetHeight() );
    ofPoint cvPointToScreen( float x , float y , float width = ofGetWidth() , float height = ofGetHeight() ) { return cvPointToScreen( ofPoint ( x , y ) , width , height  ) ; }
    
	ofVec3f getWorldCoordAt( int x, int y );
	ofColor getColorAt( int x , int y ) ; 

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
    
    float getWidth( ) { return kinect.getWidth() ;  }
    float getHeight( ) { return kinect.getHeight() ; }
    float getDistanceAt( int x , int y ) { return kinect.getDistanceAt( x ,y ) ; } 
    ofxKinect kinect;
    
protected:
    ofVec3f inverseAxes;
    // in degrees //
    ofVec3f axesRotation;
    float kinectFOV;

};










