//
//  Constants.h
//  KinectPerformanceV01
//
//  Created by Nick Hardeman on 11/6/12.
//
//

#pragma once

#define USE_KINECT 3

//--------------------------------------------------------------
static ofVec3f getNoiseForce( const ofVec3f& a_loc, float a_mult, float a_off ) {
	ofVec3f frc(
				ofSignedNoise(a_loc.x * a_mult, a_loc.z * a_mult, a_off),
				ofSignedNoise(a_loc.y * a_mult, a_loc.x * a_mult, a_off),
				ofSignedNoise(a_loc.x * a_mult, a_loc.y * a_mult, a_off)
				);
	return frc;
}

class Constants {
public:
    
};
