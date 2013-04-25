/*
 *  Particle.h
 *  openFrameworks
 *
 *  Created by Nick Hardeman on 11/22/09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef _OFX_PARTICLE_2D_
#define _OFX_PARTICLE_2D_

#include "ofMain.h"
#include "ofVec2f.h"

class ofxParticle2D : public ofVec2f {
public:
    
	ofVec2f vel;
	ofVec2f acc;
	ofVec2f prevLoc;
	
	float MAX_SPEED;
	float MAX_STEER;
	float DAMPING;
	float radius;
	int		ID;
    ofColor color;
	
	ofxParticle2D();
	ofxParticle2D(float a_x, float a_y);
	
	virtual ~ofxParticle2D();
	
	
	void addForce(ofVec2f a_loc);
	void addForce(float a_x, float a_y);
	void addForce(ofVec2f a_loc, float a_minDist, float a_scale);
	void addForce(float a_x, float a_y, float a_minDist, float a_scale);
	void addForce(ofxParticle2D& a_p, float a_minDist, float a_scale);
	
	void xeno(float a_x, float a_y, float a_pct);
	void xeno(ofVec2f& a_target, float a_pct);
	void ease(float a_x, float a_y, float a_easing);
	void ease(ofVec2f& a_target, float a_easing);
	
	void steer(ofVec2f target, bool slowdown);
	void steer(ofVec2f a_target, bool a_slowdown, float a_scale);
	void seek(float a_x, float a_y);
	void addDamping(float a_damp);
	
	void addClockwiseForce(ofVec2f a_loc, float a_minDist, float a_scale );
	void addClockwiseForce(float a_x, float a_y, float a_minDist, float a_scale );
	
	void addCounterClockwiseForce(ofVec2f a_loc, float a_minDist, float a_scale );
	void addCounterClockwiseForce(float a_x, float a_y, float a_minDist, float a_scale );
	
	void spring(float a_x, float a_y, float a_spring, float a_minDist);
	void spring(ofVec2f &a_loc, float a_spring, float a_minDist);
	void spring(float a_x, float a_y, float a_spring);
	
	void fixedSpring(float a_x, float a_y, float a_spring, float a_len);
	void fixedSpring(ofVec2f &p, float a_spring, float a_len, bool a_add = false);
	void fixedSpring(ofVec2f &p, float a_spring, float a_len, ofVec2f &addVec);
	void fixedSpring(ofxParticle2D &p, float a_spring, float a_len);
	void fixedSpring(float a_x, float a_y, float a_spring, float a_len, ofVec2f &addVec);
	
	void drag(ofxParticle2D& a_p, float a_segmentLength);
	void drag(float a_x, float a_y, float a_segmentLength);
	
	void bounceOffEdges(bool bDampedOnCollision = false);
	void checkExtendedEdges(float a_buffer = 0.f);
	void elasticEdges( float a_elastic, float a_buffer );
	
private:
	void _setDefaults();
};

#endif