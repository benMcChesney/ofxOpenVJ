/*
 *  Particle2D.cpp
 *  openFrameworks
 *
 *  Created by Nick Hardeman on 11/22/09.
 *  Copyright 2009 __MyCompanyName__. All rights reserveofVec2fd.
 *
 */

#include "ofxParticle2D.h"

ofxParticle2D::ofxParticle2D() {
	set(0.f, 0.f);
	
	_setDefaults();
}

ofxParticle2D::ofxParticle2D(float a_x, float a_y) {
	set(a_x, a_y);
}

ofxParticle2D::~ofxParticle2D() {
	
}

void ofxParticle2D::addDamping(float a_damp) {
	acc = (acc - vel) * a_damp;
}

void ofxParticle2D::xeno(float a_x, float a_y, float a_pct) {
	x = (x * (1 - a_pct)) + (a_x * a_pct);
	y = (y * (1 - a_pct)) + (a_y * a_pct);
}
void ofxParticle2D::xeno(ofVec2f& a_target, float a_pct) {
	xeno(a_target.x, a_target.y, a_pct);
}

void ofxParticle2D::ease(ofVec2f& a_target, float a_easing) {
	ofVec2f diff = a_target - (*this);
	vel += diff * a_easing;
}
void ofxParticle2D::ease(float a_x, float a_y, float a_easing) {
	ofVec2f temp(a_x, a_y);
	ease(temp, a_easing);
}




void ofxParticle2D::seek(float a_x, float a_y) {
	steer(ofVec2f(a_x, a_y), false);
}

// Daniel Shiffman //
void ofxParticle2D::steer(ofVec2f a_target, bool a_slowdown) {
    ofVec2f steer;
    ofVec2f desired = a_target - (*this);
    float d = desired.length();
	
    // If the distance is greater than 0, calc steering (otherwise return zero vector)
    if (d > 0.f) {
		desired.normalize();
		// Two options for desired vector magnitude (1 -- based on distance, 2 -- maxspeed)
		if ((a_slowdown) && (d < 100.0f)) {desired *= (MAX_SPEED * (d/100.0f));} // This damping is somewhat arbitrary
		else {desired *= (MAX_SPEED); }
		
		steer = (desired - vel);
		steer.limit(MAX_STEER);
		
    } else {
		steer.set(0.f, 0.f);
    }
    acc += steer;
}

// Daniel Shiffman //
void ofxParticle2D::steer(ofVec2f a_target, bool a_slowdown, float a_scale) {
    ofVec2f steer;
    ofVec2f desired = a_target - (*this);
    float d = desired.length();
	
    // If the distance is greater than 0, calc steering (otherwise return zero vector)
    if (d > 0.f) {
		desired.normalize();
		// Two options for desired vector magnitude (1 -- based on distance, 2 -- maxspeed)
		if ((a_slowdown) && (d < 100.0f)) {desired *= (MAX_SPEED * (d/100.0f));} // This damping is somewhat arbitrary
		else {desired *= (MAX_SPEED); }
		
		steer = (desired - vel);
		steer.limit(MAX_STEER);
		steer *= a_scale;
    } else {
		steer.set(0.f, 0.f);
    }
    acc += steer;
}

void ofxParticle2D::addForce(ofVec2f a_loc) {
	acc += a_loc;
}

void ofxParticle2D::addForce(float a_x, float a_y) {
	acc.x += a_x;
	acc.y += a_y;
}

void ofxParticle2D::addForce(float a_x, float a_y, float a_minDist, float a_scale) {
	ofVec2f dir(a_x, a_y);
	dir = dir - (*this);
	float d = dir.length();
	if ( d < a_minDist && d > 0) {
		dir.normalize();
		dir *= a_scale * ( 1 - (d / a_minDist) );
		acc += dir;
	}
}

void ofxParticle2D::addForce(ofVec2f a_loc, float a_minDist, float a_scale) {
	ofVec2f dir = a_loc - (*this);
	float d = dir.length();
	if ( d < a_minDist) {
		dir.normalize();
		dir *= a_scale * ( 1 - (d / a_minDist) );
		acc += dir;
	}
}

void ofxParticle2D::addForce(ofxParticle2D& a_p, float a_minDist, float a_scale) {
	ofVec2f dir = a_p - (*this);
	float d = dir.length();
	if ( d < a_minDist) {
		dir.normalize();
		dir *= a_scale * ( 1 - (d / a_minDist) );
		acc += dir;
		a_p.acc -= dir;
	}
}



void ofxParticle2D::addClockwiseForce(ofVec2f a_loc, float a_minDist, float a_scale ) {
	ofVec2f dir = (*this) - a_loc;
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


void ofxParticle2D::addClockwiseForce(float a_x, float a_y, float a_minDist, float a_scale ) {
	addClockwiseForce(ofVec2f(a_x, a_y), a_minDist, a_scale );
}


void ofxParticle2D::addCounterClockwiseForce(ofVec2f a_loc, float a_minDist, float a_scale ) {
	ofVec2f dir = (*this) - a_loc;
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

void ofxParticle2D::addCounterClockwiseForce(float a_x, float a_y, float a_minDist, float a_scale ) {
	addCounterClockwiseForce( ofVec2f(a_x, a_y), a_minDist, a_scale );
}

void ofxParticle2D::spring(float a_x, float a_y, float a_spring) {
	ofVec2f diff = ofVec2f(a_x, a_y) - (*this);
	diff *= a_spring;
	addForce( diff );
}

void ofxParticle2D::spring(float a_x, float a_y, float a_spring, float a_minDist) {
	ofVec2f diff = ofVec2f(a_x, a_y) - (*this);
	if (diff.length() < a_minDist) {
		diff *= a_spring;
		addForce( diff );
	}
}

void ofxParticle2D::spring(ofVec2f &a_loc, float a_spring, float a_minDist) {
	ofVec2f diff = a_loc - (*this);
	if (diff.length() < a_minDist) {
		diff *= a_spring;
		addForce( diff );
	}
}

void ofxParticle2D::fixedSpring(float a_x, float a_y, float a_spring, float a_len) {
	ofVec2f diff = ofVec2f(a_x, a_y) - (*this);
	float springForce = a_spring * (a_len - diff.length());
	diff.normalize();
	diff *= springForce;
	
	addForce( -diff );
	
}

void ofxParticle2D::fixedSpring(ofxParticle2D &p, float a_spring, float a_len) {
	ofVec2f diff = p - (*this);
	float springForce = a_spring * (a_len - diff.length());
	diff.normalize();
	diff *= springForce;
	
	addForce( -diff );
	p.addForce( diff );
	
}

void ofxParticle2D::fixedSpring(ofVec2f &p, float a_spring, float a_len, bool a_add) {
	ofVec2f diff = p - (*this);
	float springForce = a_spring * (a_len - diff.length());
	diff.normalize();
	diff *= springForce;
	
	addForce( -diff );
	if (a_add) p += diff; 
}

void ofxParticle2D::fixedSpring(ofVec2f &p, float a_spring, float a_len, ofVec2f &addVec) {
	ofVec2f diff = p - (*this);
	float springForce = a_spring * (a_len - diff.length());
	diff.normalize();
	diff *= springForce;
	
	addForce( -diff );
	addVec += diff; 
}

void ofxParticle2D::fixedSpring(float a_x, float a_y, float a_spring, float a_len, ofVec2f &addVec) {
	ofVec2f p(a_x, a_y);
	ofVec2f diff = p - (*this);
	float springForce = (a_spring * (a_len - diff.length()));
	diff.normalize();
	diff *= springForce;
	
	addForce( -diff );
	addVec += diff; 
}

void ofxParticle2D::drag(ofxParticle2D& a_p, float a_segmentLength) {
	ofVec2f diff = a_p - (*this);
	diff.normalize();
	diff *= a_segmentLength;
	x = a_p.x - diff.x;
	y = a_p.y - diff.y;
}

void ofxParticle2D::drag(float a_x, float a_y, float a_segmentLength) {
	ofVec2f diff = ofVec2f(a_x, a_y) - (*this);
	diff.normalize();
	diff *= a_segmentLength;
	x = a_x - diff.x;
	y = a_y - diff.y;
}



// Bounds checking ---------------------------------------

//------------------------------------------------------------
void ofxParticle2D::bounceOffEdges(bool bDampedOnCollision) {
	
	// sometimes it makes sense to damped, when we hit
	bool bDidICollide = false;
	
	// what are the walls
	float minx = 0;
	float miny = 0;
	float maxx = ofGetWidth();
	float maxy = ofGetHeight();
	
	if (x > maxx){
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

void ofxParticle2D::checkExtendedEdges(float a_buffer) {
	float buffer = a_buffer;
	if (x > ofGetWidth() + buffer ) x = -buffer;
	if (x < -buffer) x = ofGetWidth() + buffer;
	
	if (y > ofGetHeight() + buffer) y = -buffer;
	if (y < -buffer) y = ofGetHeight() + buffer;
}


void ofxParticle2D::elasticEdges( float a_elastic, float a_buffer ) {
	if (x > ofGetWidth() + a_buffer )   vel.x += -a_elastic;
	if (x < -a_buffer)                  vel.x += a_elastic;
	
	if (y > ofGetHeight() + a_buffer)   vel.y += -a_elastic;
	if (y < -a_buffer)                  vel.y += a_elastic;
}





void ofxParticle2D::_setDefaults() {
	
	MAX_SPEED = 15.f;
	MAX_STEER = .9f;
	
	DAMPING = 0.01f;
	
	vel.set(0.f, 0.f);
	acc.set(0.f, 0.f);
	
	prevLoc = (*this);
}





