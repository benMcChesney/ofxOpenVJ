/*
 *  Particle.cpp
 *  openFrameworks
 *
 *  Created by Nick Hardeman on 11/22/09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */

#include "ofxParticle3D.h"

ofxParticle3D::ofxParticle3D() {
	set(0.f, 0.f, 0.f);
	
	_setDefaults();
}

ofxParticle3D::ofxParticle3D(float a_x, float a_y, float a_z) {
	set(a_x, a_y, a_z);
}

ofxParticle3D::~ofxParticle3D() {
	
}

void ofxParticle3D::addDamping(float a_damp) {
	acc = (acc - vel) * a_damp;
}

void ofxParticle3D::xeno(ofVec3f a_target, float a_amt) {
	//pos.x = catchUpSpeed * catchX + (1-catchUpSpeed) * pos.x; 
	//pos.y = catchUpSpeed * catchY + (1-catchUpSpeed) * pos.y; 
	ofVec3f newPos = (a_amt * a_target) + ((1.f-a_amt) * (*this));
	set(newPos.x, newPos.y, newPos.z);
}

void ofxParticle3D::seek(float a_x, float a_y, float a_z) {
	steer(ofVec3f(a_x, a_y, a_z), false);
}

void ofxParticle3D::seek(ofVec3f a_loc, bool a_slowdown) {
	steer(a_loc, a_slowdown);
}

void ofxParticle3D::steer(ofVec3f a_target, bool a_slowdown) {
	steer( a_target, a_slowdown, 1.f);
}

// Daniel Shiffman //
void ofxParticle3D::steer(ofVec3f a_target, bool a_slowdown, float a_scale) {
	float minDist = 0.f;
	// pick an arbitrary distance for slowdown //
	if(a_slowdown) minDist = 100.f;
	steer( a_target, a_slowdown, a_scale, minDist);
}

void ofxParticle3D::steer(ofVec3f& a_target, bool a_slowdown, float a_scale, float a_minDist ) {
    ofVec3f steer;
    ofVec3f desired = a_target - *this;
    float d = desired.length();
	
    // If the distance is greater than 0, calc steering (otherwise return zero vector)
    if (d > 0.f) {
		desired.normalize();
		if(a_minDist == 0) a_slowdown = false;
		// Two options for desired vector magnitude (1 -- based on distance, 2 -- maxspeed)
		if ((a_slowdown) && (d < a_minDist)) {desired *= (MAX_SPEED * (d/a_minDist));} // This damping is somewhat arbitrary
		else {desired *= (MAX_SPEED); }
		
		steer = (desired - vel);
		steer.limit(MAX_STEER);
		steer *= a_scale;
    } else {
		steer.set(0.f, 0.f, 0.f);
    }
    acc += steer;
}

void ofxParticle3D::addForce(ofVec3f a_loc) {
	acc += a_loc;
}

void ofxParticle3D::addForce(float a_x, float a_y, float a_z) {
	acc.x += a_x;
	acc.y += a_y;
	acc.z += a_z;
}

void ofxParticle3D::addForce(float a_x, float a_y, float a_z, float a_minDist, float a_scale) {
	ofVec3f dir(a_x, a_y, a_z);
	dir = dir - *this;
	float d = dir.length();
	if ( d < a_minDist) {
		dir.normalize();
		dir *= a_scale * ( 1 - (d / a_minDist) );
		acc += dir;
	}
}

void ofxParticle3D::addForce(ofVec3f a_loc, float a_minDist, float a_scale) {
	ofVec3f dir = a_loc - *this;
	float d = dir.length();
	if ( d < a_minDist) {
		dir.normalize();
		dir *= a_scale * ( 1 - (d / a_minDist) );
		acc += dir;
	}
}

void ofxParticle3D::addForce(ofxParticle3D& a_p, float a_minDist, float a_scale) {
	ofVec3f dir = a_p - *this;
	float d = dir.length();
	if ( d < a_minDist) {
		dir.normalize();
		dir *= a_scale * ( 1 - (d / a_minDist) );
		acc += dir;
		a_p.acc -= dir;
	}
}

void ofxParticle3D::addForce(ofxParticle3D& a_p, float a_minDist, float a_scale1, float a_scale2) {
	ofVec3f dir = a_p - *this;
	float d = dir.length();
	if ( d < a_minDist) {
		dir.normalize();
		dir *= ( 1 - (d / a_minDist) );
		acc += dir * a_scale1;
		a_p.acc -= dir * a_scale2;
	}
}


void ofxParticle3D::addClockwiseForce(ofVec3f a_loc, float a_minDist, float a_scale ) {
	ofVec3f dir = *this - a_loc;
	float d = dir.length();
	if (d < a_minDist && d > 0) {
		float pct = 1 - (d / a_minDist);
		dir.normalize();
		dir *= (MAX_SPEED);
		dir = (dir - vel);
		dir *= (a_scale * pct);
		
		acc.x = acc.x - dir.y;
		acc.y = acc.y + dir.x;
	}
}


void ofxParticle3D::addClockwiseForce(float a_x, float a_y, float a_z, float a_minDist, float a_scale ) {
	addClockwiseForce(ofVec3f(a_x, a_y, a_z), a_minDist, a_scale );
}


void ofxParticle3D::addCounterClockwiseForce(ofVec3f a_loc, float a_minDist, float a_scale ) {
	ofVec3f dir = *this - a_loc;
	float d = dir.length();
	if (d < a_minDist && d > 0) {
		float pct = 1 - (d / a_minDist);
		dir.normalize();
		dir *= (MAX_SPEED);
		dir = (dir - vel);
		dir *= (a_scale * pct);
		
		acc.x = acc.x + dir.y;
		acc.y = acc.y - dir.x;
		
	}
}

void ofxParticle3D::addCounterClockwiseForce(float a_x, float a_y, float a_z, float a_minDist, float a_scale ) {
	addCounterClockwiseForce( ofVec3f(a_x, a_y, a_z), a_minDist, a_scale );
}

void ofxParticle3D::spring(float a_x, float a_y, float a_z, float a_spring, float a_minDist) {
	ofVec3f diff = ofVec3f(a_x, a_y, a_z) - *this;
	if (diff.length() < a_minDist) {
		diff *= a_spring;
		addForce( diff );
	}
}

void ofxParticle3D::spring(ofVec3f &a_loc, float a_spring, float a_minDist) {
	ofVec3f diff = a_loc - *this;
	if (diff.length() < a_minDist) {
		diff *= a_spring;
		addForce( diff );
	}
}

void ofxParticle3D::spring(ofVec3f &a_loc, float a_spring) {
	ofVec3f diff = a_loc - *this;
	diff *= a_spring;
	addForce( diff );
}

void ofxParticle3D::fixedSpring(ofxParticle3D &p, float a_spring, float a_len) {
	ofVec3f diff = p - *this;
	float springForce = a_spring * (a_len - diff.length());
	diff.normalize();
	diff *= springForce;
	
	addForce( -diff );
	p.addForce( diff );
	
}

void ofxParticle3D::fixedSpring(ofxParticle3D &p, float a_spring, float a_len, bool a_add) {
	ofVec3f diff = p - *this;
	float springForce = a_spring * (a_len - diff.length());
	diff.normalize();
	diff *= springForce;
	
	addForce( -diff );
	if (a_add) p.addForce( diff );
}

void ofxParticle3D::fixedSpring(ofVec3f &p, float a_spring, float a_len, bool a_add) {
	ofVec3f diff = p - *this;
	float springForce = a_spring * (a_len - diff.length());
	diff.normalize();
	diff *= springForce;
	
	addForce( -diff );
	if (a_add) p += diff; 
}

void ofxParticle3D::fixedSpring(ofVec3f &p, float a_spring, float a_len, ofVec3f &addVec) {
	ofVec3f diff = p - *this;
	float springForce = a_spring * (a_len - diff.length());
	diff.normalize();
	diff *= springForce;
	
	addForce( -diff );
	addVec += diff; 
}

void ofxParticle3D::fixedSpring(float a_x, float a_y, float a_z, float a_spring, float a_len, ofVec3f &addVec) {
	ofVec3f p(a_x, a_y, a_z);
	ofVec3f diff = p - *this;
	float springForce = (a_spring * (a_len - diff.length()));
	diff.normalize();
	diff *= springForce;
	
	addForce( -diff );
	addVec += diff; 
}


void ofxParticle3D::drag(ofxParticle3D& a_p, float a_segmentLength) {
	ofVec3f diff = a_p - *this;
	diff.normalize();
	diff *= a_segmentLength;
	x = a_p.x - diff.x;
	y = a_p.y - diff.y;
	z = a_p.z - diff.z;
}

void ofxParticle3D::drag(float a_x, float a_y, float a_z, float a_segmentLength) {
	ofVec3f diff = ofVec3f (a_x, a_y, a_z) - *this;
	diff.normalize();
	diff *= a_segmentLength;
	x = a_x - diff.x;
	y = a_y - diff.y;
	z = a_z - diff.z;
}


// Bounds checking ---------------------------------------

//------------------------------------------------------------
void ofxParticle3D::bounceOffEdges(bool bDampedOnCollision) {
	
	// sometimes it makes sense to damped, when we hit
	bool bDidICollide = false;
	
	// what are the walls
	float minx = 0;
	float miny = 0;
	float maxx = ofGetWidth();
	float maxy = ofGetHeight();
	
	if ( x > maxx ) {
		x = maxx; // move to the edge, (important!)
		vel.x *= -1;
		bDidICollide = true;
	} else if (x < minx){
		x = minx; // move to the edge, (important!)
		vel.x *= -1;
		bDidICollide = true;
	}
	
	if (y > maxy){
		y = maxy; // move to the edge, (important!)
		vel.y *= -1;
		bDidICollide = true;
	} else if (y < miny){
		y = miny; // move to the edge, (important!)
		vel.y *= -1;
		bDidICollide = true;
	}
	
	if (bDidICollide == true && bDampedOnCollision == true){
		vel *= 0.3;
	}
	
}

void ofxParticle3D::checkExtendedEdges(float a_buffer) {
	float buffer = a_buffer;
	if (x > ofGetWidth() + buffer ) x = -buffer;
	if (x < -buffer) x = ofGetWidth() + buffer;
	
	if (y > ofGetHeight() + buffer) y = -buffer;
	if (y < -buffer) y = ofGetHeight() + buffer;
}


void ofxParticle3D::elasticEdges( float a_elastic, float a_buffer ) {
	if (x > ofGetWidth() + a_buffer )	vel.x += -a_elastic;
	if (x < -a_buffer)					vel.x += a_elastic;
	
	if (y > ofGetHeight() + a_buffer)	vel.y += -a_elastic;
	if (y < -a_buffer)					vel.y += a_elastic;
}








void ofxParticle3D::_setDefaults() {
	
	MAX_SPEED = 15.f;
	MAX_STEER = .9f;
	
	DAMPING = 0.1f;
	
	vel.set(0.f, 0.f, 0.f);
	acc.set(0.f, 0.f, 0.f);
	
	prevLoc = *this;
	bRemove = false;
	mass	= 1.f;
}