//
//  ImageSpringParticles.h
//  KinectPerformanceV01
//
//  Created by Ben McChesney on 11/6/12.
//
//  ImageSpringParticles
//

#pragma once 
#include "BaseScene.h"
#include "Particle.h"

class ImageSpringParticles : public BaseScene {
public:
    ImageSpringParticles();
    ImageSpringParticles( int a_index, string a_name ):BaseScene( a_index, a_name ) {}
    ~ImageSpringParticles();
    
    void setup();
    void setupGui(float a_x=0, float a_y=0);
    void guiEvent(ofxUIEventArgs &e);
    
    void update();
    void draw();
    
    void activate();
    void deactivate();
    
    ofImage image ;                 //image to load
    int sampling ;                  //pixels to skip
    vector<Particle> particles ;    //vector to store pixels
    int numParticles ;          //Number of particles
    
    //Spring and Sink Factors
    bool bSpringEnabled ;        //toggle whether particles return to their origin
    float forceRadius ;             //radius of repellent/attraction force
    float friction ;                //damping to slow the particles down
    float springFactor ;          //how much the particle "springs" back to origin
    bool bSeekEnabled ; 
    
    ofFbo fadeFbo ;
    int curImageIndex ;
    
    //Directory list
    int 		nImages;
    ofImage	* 	images;
    ofDirectory   DIR;
    
    unsigned char r , g , b ;
    
    ofPoint mousePos ;
    ofPoint offset ;
    ofPoint startDrag ;
    void setupParticles() ; 
    float fadeAlpha ;
    float particleAlpha ;
    float forceStrength ; 
    
    ofVec3f pointCloudOffset ;
    ofVec3f forceTarget ;
    ofVec3f forcePosition ;
    
    bool bShowSphere ;
    bool bAdditiveBlend ;

    float specialZOffset ; 
    
    int numFramesUntilTransition ;
    float maxParticleSpeed ; 
    float xWander, yWander , xWanderNoise , yWanderNoise , wanderTimeMultiplier , zWander ;
    
};
