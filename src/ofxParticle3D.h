/*
 *  Particle.h
 *  openFrameworks
 *
 *  Created by Nick Hardeman on 11/22/09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */

#pragma once
#include "ofMain.h"

class ofxParticle3D : public ofVec3f {
public:
	//ofVec3f loc;
	ofVec3f vel;
	ofVec3f acc;
	ofVec3f prevLoc;
	
	float MAX_SPEED;
	float MAX_STEER;
	float DAMPING;
	float radius;
	float mass;
	
	bool bRemove;
	
	ofxParticle3D();
	ofxParticle3D(float a_x, float a_y, float a_z);
	
	virtual ~ofxParticle3D();
	
	void xeno(ofVec3f a_target, float a_amt);
	
	void addForce(ofVec3f a_loc);
	void addForce(float a_x, float a_y, float a_z);
	void addForce(ofVec3f a_loc, float a_minDist, float a_scale);
	void addForce(float a_x, float a_y, float a_z, float a_minDist, float a_scale);
	void addForce(ofxParticle3D& a_p, float a_minDist, float a_scale);
	void addForce(ofxParticle3D& a_p, float a_minDist, float a_scale1, float a_scale2);
	
	void steer(ofVec3f target, bool slowdown);
	void steer(ofVec3f a_target, bool a_slowdown, float a_scale);
	void steer(ofVec3f& a_target, bool a_slowdown, float a_scale, float a_minDist );
	void seek(float a_x, float a_y, float a_z = 0.f);
	void seek(ofVec3f a_loc, bool a_slowdown=false);
	void addDamping(float a_damp);
	
	void addClockwiseForce(ofVec3f a_loc, float a_minDist, float a_scale );
	void addClockwiseForce(float a_x, float a_y, float a_z, float a_minDist, float a_scale );
	
	void addCounterClockwiseForce(ofVec3f a_loc, float a_minDist, float a_scale );
	void addCounterClockwiseForce(float a_x, float a_y, float a_z, float a_minDist, float a_scale );
	
	void spring(float a_x, float a_y, float a_z, float a_spring, float a_minDist);
	void spring(ofVec3f &a_loc, float a_spring, float a_minDist);
	void spring(ofVec3f &a_loc, float a_spring);
	
	void fixedSpring(ofxParticle3D &p, float a_spring, float a_len, bool a_add);
	void fixedSpring(ofVec3f &p, float a_spring, float a_len, bool a_add = false);
	void fixedSpring(ofVec3f &p, float a_spring, float a_len, ofVec3f &addVec);
	void fixedSpring(ofxParticle3D &p, float a_spring, float a_len);
	void fixedSpring(float a_x, float a_y, float a_z, float a_spring, float a_len, ofVec3f &addVec);
	
	void drag(ofxParticle3D& a_p, float a_segmentLength);
	void drag(float a_x, float a_y, float a_z, float a_segmentLength);
	
	void bounceOffEdges(bool bDampedOnCollision = false);
	void checkExtendedEdges(float a_buffer = 0.f);
	void elasticEdges( float a_elastic, float a_buffer );
	
private:
	void _setDefaults();
};

