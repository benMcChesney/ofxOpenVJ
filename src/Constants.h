//
//  Constants.h
//  KinectPerformanceV01
//
//  Created by Nick Hardeman on 11/6/12.
//
//
#include "ofMain.h"
#pragma once

#define USE_KINECT 3

//--------------------------------------------------------------
static ofPoint getNoiseForce( const ofPoint& a_loc, float a_mult, float a_off ) {
	ofPoint frc(
				ofSignedNoise(a_loc.x * a_mult, a_loc.z * a_mult, a_off),
				ofSignedNoise(a_loc.y * a_mult, a_loc.x * a_mult, a_off),
				ofSignedNoise(a_loc.x * a_mult, a_loc.y * a_mult, a_off)
				);
	return frc;
}

class Constants {
public:
    
};
