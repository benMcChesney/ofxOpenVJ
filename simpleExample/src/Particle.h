//
//  Particle.h
//  PixelForces
//
//  Created by Ben McChesney on 7/2/11.
//  Copyright 2011 Helios Interactive. All rights reserved.
//
//  A Simple Particle Class

#ifndef _PARTICLE
#define _PARTICLE

#include "ofMain.h" 

class Particle
{
    public : 
        Particle() ; 
        Particle( ofVec3f _position , ofColor _color ) 
        {
            position = _position ; 
            color = _color ; 
            velocity = ofVec3f ( ofRandom ( -2 , 2 ) , ofRandom ( -2 , 2 ) , ofRandom ( -2 , -2 ) ) ; 
            spawnPoint = _position ; 
        }
    
        ofVec3f position , velocity ; 
        ofVec3f acceleration ;          //smoothing applied to velocity
        ofVec3f spawnPoint ;            //original location to line up the picture
        ofColor color ; 
        
};
#endif