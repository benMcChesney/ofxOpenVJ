//
//  CameraManager.h
//  Tribeca_Kinect
//
//  Created by Nick Hardeman on 4/21/12.
//

#pragma once
#include "ofMain.h"
#include "ofxParticle3D.h"
#include "ofxUI.h"
#include "ofxPostProcessing.h"

class CameraManager
{
public:
    
    void setup();
    void update();
    void draw();
    
    bool debug();
    bool isAuto();
    
    float getDistance();
    float getDistanceToTarget();
    void setMinDistance( float a_minDist );
    float getMinDistance();
    void setMaxDistance( float a_maxDist );
    float getMaxDistance();
    ofVec3f getOrbitVec3f(float a_longitude, float a_latitude, float a_radius, const ofVec3f& a_centerPoint);
    void setCenter(float a_x, float a_y, float a_z);
    void setCenter(ofVec3f a_center);
    
    void setLong( float lng) {_longitude = lng;}
    void setLat( float lat) {_latitude = lat;}
    
    void guiEvent( ofxUIEventArgs &e );
    void setupGui( float a_x=0, float a_y=0 );
    
    void loadSettings();
    void saveSettings();
    
    ofxUIScrollableCanvas* gui;
    void updateFft( float _low , float _mid , float _high ) ;
    
    float zOffset ;
    float cameraTargetZ ; 
    float camMovementFactor ;
    
    ofEasyCam cam ;
    
    void begin() ;
    void end() ; 

	 ofxPostProcessing post ;
    
    void disableAllPostProcessing() ; 

    
private:
    
    
    float _distance, _minDistance, _maxDistance;
    bool _bAuto, _bDebug;
    ofVec3f _center;
    ofxParticle3D _camParticle, _target;
    
    float _steer, _targetSpring;
    float _longitude, _latitude, latInc, lngInc;
    float _maxLongitude , _minLongitude , _maxLatitude , _minLatitude ;
    
    float _nextLongitude, _nextLatitude;
    
    int _numBeatHits;
    float _maxBeatHits;
    
    //FFT values
    float low ;
    float mid ;
    float high ;
 
    
};




