//
//  ImageSpringParticles.cpp
//  KinectPerformanceV01
//
//  Created by Ben McChesney on 11/6/12.
//
//

#include "ImageSpringParticles.h"

//--------------------------------------------------------------
ImageSpringParticles::ImageSpringParticles() {
    
}

//--------------------------------------------------------------
ImageSpringParticles::~ImageSpringParticles() {
    
}

//--------------------------------------------------------------
void ImageSpringParticles::setup() {


    //if the app performs slowly raise this number
    sampling = 1 ;
    curImageIndex = 0 ;
    
    numParticles = 0; 
    ofSetFrameRate( 30 ) ;
    //  numParticles = ( image.width * image.height ) / sampling ;
    
    //Set spring and sink values
    bSpringEnabled = false ;
    forceRadius = 45 ;
    friction = 0.85 ;
    springFactor = 0.12 ;
    bSeekEnabled = false ;
    
    //setup openGL
    ofSetFrameRate(30) ;
    ofBackground(0, 0, 0);
	//ofSetBackgroundAuto(false);
	ofSetVerticalSync(true);
    
    nImages = DIR.listDir("images/");
 	images = new ofImage[nImages];
    DIR.allowExt("jpg") ;
    
    //you can now iterate through the files as you like
    for(int i = 0; i < nImages; i++)
    {
        images[i].loadImage(DIR.getPath(i));
    }
    
    fadeFbo.allocate( ofGetWidth() , ofGetHeight() ) ;
    fadeFbo.begin() ;
    ofClear(0, 0, 0, 1);
    fadeFbo.end() ;
    
    
    fadeAlpha = 2 ;

    setupParticles() ;
    
}

//--------------------------------------------------------------
void ImageSpringParticles::setupGui(float a_x, float a_y) {
    // creates new gui and adds the name to it //
    BaseScene::setupGui(a_x, a_y);
    
    int width = 300 ;
    int height = 25 ;
    gui->addSlider("FORCE RADIUS", 0.0f , 1200.0f , forceRadius, width, height) ;
    gui->addSlider("FRICTION", 0.0f , 1.0f , friction, width, height) ;
    gui->addSlider("SPRING FACTOR", 0.0f , 1.0f , springFactor, width, height) ;
    gui->addSlider("FADE AMOUNT", 0.0f , 255.0f , fadeAlpha, width, height) ;
    gui->addSlider("PARTICLE ALPHA", 0.0f , 255.0f , particleAlpha, width, height) ;
    gui->addSlider("FORCE STRENGTH", 0.0f , 1.0f , forceStrength, width, height) ;
    gui->addSlider("SAMPLING", 0.0f , 16 , sampling, width, height) ;
    gui->addSlider("FRAMES UNTIL SWITCH", 0.0 , 200 , numFramesUntilTransition, width, height) ;
    
    //float xWander, yWander , xWanderNoise , yWanderNoise , wanderTimeMultiplier , zWander ; 
    gui->addSlider("X WANDER" , 0.0 , 500.0f , xWander, width , height ) ;
    gui->addSlider("X NOISE WANDER" , 0.0 , 500.0f , xWanderNoise , width , height ) ;
    gui->addSlider("Y WANDER" , 0.0 , 500.0f , yWander , width , height ) ;
    gui->addSlider("Y NOISE WANDER" , 0.0 , 500.0f , yWanderNoise , width , height ) ;
    gui->addSlider("WANDER TIME MULTIPLIER" , 0.0 , 2.0f , wanderTimeMultiplier , width , height ) ;
    gui->addSlider("Z WANDER", 0.0f, 1500.0f,  zWander , width , height );
    gui->addSlider("MAX PARTICLE SPEED", 0.0f, 4.0f,  maxParticleSpeed , width , height );
    //gui->addSlider("POINT CLOUD OFFSET X" , -3000.0 , 3000.0f , pointCloudOffset.x , width , height ) ;
    //gui->addSlider("POINT CLOUD OFFSET Y" , -3000.0 , 3000.0f , pointCloudOffset.y , width , height ) ;
    //gui->addSlider("POINT CLOUD OFFSET Z" , -3000.0 , 3000.0f , pointCloudOffset.z , width , height ) ;

    //gui->addSlider("FORCE TARGET X" , -3000.0 , 3000.0f , forceTarget.x , width , height ) ;
    //gui->addSlider("FORCE TARGET Y" , -3000.0 , 3000.0f , forceTarget.y , width , height ) ;
    //gui->addSlider("FORCE TARGET Z" , -3000.0 , 3000.0f , forceTarget.z , width , height ) ;

    gui->addToggle( "SHOW FORCE TARGET" , bShowSphere ) ;
    gui->addToggle("SEEK", bSeekEnabled, height, height ) ;
    gui->addToggle("SPRING ENABLED", bSpringEnabled, height, height ) ;
    gui->addToggle("USE ADDITIVE BLENDING", bAdditiveBlend, height, height ) ; 

        //bAdditiveBlend
    //maxParticleSpeed
    
    ofAddListener( gui->newGUIEvent, this, &ImageSpringParticles::guiEvent );
}

void ImageSpringParticles::setupParticles()
{
    
    if ( curImageIndex == nImages )
        curImageIndex = 0 ;
    ofImage nextImage = images[curImageIndex] ;

    forceTarget = ofVec3f ( images[curImageIndex].getWidth() / 2 , images[curImageIndex].getHeight() / 2 , 0 )  ; 
    
    //Retrieve the pixels from the loaded image
    ofPixels pixelsRef = nextImage.getPixelsRef() ; 
    unsigned char * pixels = nextImage.getPixels() ;
    //store width and height for optimization and clarity
    int w = nextImage.width ;
    int h = nextImage.height ;

    numParticles= 0 ;
    
    particles.clear() ; 
    //Loop through all the rows
    for ( int x = 0 ; x < w ; x+=sampling )
    {
        //Loop through all the columns
        for ( int y = 0 ; y < h ; y+=sampling )
        {
            particles.push_back( Particle ( ofPoint ( x , y , 0 ) , pixelsRef.getColor( x, y ) ) ) ;
            numParticles++ ;
        }
    }
}

//--------------------------------------------------------------
void ImageSpringParticles::guiEvent(ofxUIEventArgs &e) {
    
    
    string name = e.widget->getName() ;
    
    //sliders
    if ( name == "FORCE RADIUS" ) forceRadius = ((ofxUISlider*)e.widget)->getScaledValue() ;
    if ( name == "FRICTION" ) friction = ((ofxUISlider*)e.widget)->getScaledValue() ;
    if ( name == "SPRING FACTOR" ) springFactor = ((ofxUISlider*)e.widget)->getScaledValue() ;
    if ( name == "FADE AMOUNT" ) fadeAlpha = ((ofxUISlider*)e.widget)->getScaledValue() ;
    if ( name == "PARTICLE ALPHA" ) particleAlpha = ((ofxUISlider*)e.widget)->getScaledValue() ;
    if ( name == "FORCE STRENGTH" ) forceStrength = ((ofxUISlider*)e.widget)->getScaledValue() ;
    if ( name == "SAMPLING" ) sampling = (int)((ofxUISlider*)e.widget)->getScaledValue() ;
    if ( name == "FRAMES UNTIL SWITCH" ) numFramesUntilTransition = (int)((ofxUISlider*)e.widget)->getScaledValue() ;

    
    if ( name == "POINT CLOUD OFFSET X" ) pointCloudOffset.x = (int)((ofxUISlider*)e.widget)->getScaledValue() ;
    if ( name == "POINT CLOUD OFFSET Y" ) pointCloudOffset.y = (int)((ofxUISlider*)e.widget)->getScaledValue() ;
    if ( name == "POINT CLOUD OFFSET Z" ) pointCloudOffset.z = (int)((ofxUISlider*)e.widget)->getScaledValue() ;

    //if ( name == "FORCE TARGET X" ) forceTarget.x = (int)((ofxUISlider*)e.widget)->getScaledValue() ;
    //if ( name == "FORCE TARGET X" ) forceTarget.y = (int)((ofxUISlider*)e.widget)->getScaledValue() ;
    //if ( name == "SHOW FORCE TARGET") forceTarget.z = (int)((ofxUISlider*)e.widget)->getScaledValue() ;

    //toggles
    if ( name == "SEEK" ) bSeekEnabled = ((ofxUIToggle*)e.widget)->getValue() ;
    if ( name == "SPRING ENABLED" ) bSpringEnabled = ((ofxUIToggle*)e.widget)->getValue() ;
    if ( name == "SHOW FORCE TARGET" ) bShowSphere = ((ofxUIToggle*)e.widget)->getValue() ;
    if ( name == "USE ADDITIVE BLENDING" ) bAdditiveBlend = ((ofxUIToggle*)e.widget)->getValue() ;
 
    if ( name == "X WANDER" ) xWander = ((ofxUISlider*)e.widget)->getScaledValue() ;
    if ( name == "X NOISE WANDER" ) xWanderNoise = ((ofxUISlider*)e.widget)->getScaledValue() ;
    if ( name == "Y WANDER" ) yWander = ((ofxUISlider*)e.widget)->getScaledValue() ;
    if ( name == "Y NOISE WANDER" ) yWanderNoise = ((ofxUISlider*)e.widget)->getScaledValue() ;
    if ( name == "WANDER TIME MULTIPLIER" ) wanderTimeMultiplier = ((ofxUISlider*)e.widget)->getScaledValue() ;
    if ( name == "Z WANDER" ) zWander = ((ofxUISlider*)e.widget)->getScaledValue() ;
    if ( name == "MAX PARTICLE SPEED" ) maxParticleSpeed = ((ofxUISlider*)e.widget)->getScaledValue() ;
     
    //gui->addSlider("MAX PARTICLE SPEED", 0.0f, 25.0f,  maxParticleSpeed , width , height );
    //gui->addToggle( "SHOW FORCE TARGET" , bShowSphere ) ;
    
    /*
     gui->addToggle("USE ADDITIVE BLENDING", bAdditiveBlend, height, height ) ;
     gui->addSlider("X WANDER" , 0.0 , 3000.0f , xWander, width , height ) ;
     gui->addSlider("X NOISE WANDER" , 0.0 , 3000.0f , xWanderNoise , width , height ) ;
     gui->addSlider("Y WANDER" , 0.0 , 3000.0f , yWander , width , height ) ;
     gui->addSlider("Y NOISE WANDER" , 0.0 , 3000.0f , yWanderNoise , width , height ) ;
     gui->addSlider("WANDER TIME MULTIPLIER" , 0.0 , 3000.0f , wanderTimeMultiplier , width , height ) ;
     gui->addSlider("Z WANDER", 0.0f, 500.0f,  zWander , width , height );
     */
}

//--------------------------------------------------------------
void ImageSpringParticles::activate() {
    
}

//--------------------------------------------------------------
void ImageSpringParticles::deactivate() {
    // turn off the gui //
    BaseScene::deactivate();
}


//--------------------------------------------------------------
void ImageSpringParticles::update() {
    
     ofPoint center = ofPoint ( ofGetWidth() /2 , ofGetHeight() /2 ) ;
    
    ofVec3f diff ;          //Difference between particle and mouse
    float dist ;            //distance from particle to mouse ( as the crow flies )
    float ratio ;           //Ratio of how strong the effect is = 1 + (-dist/maxDistance) ;
    
   

   // xWander, yWander , xWanderNoise , yWanderNoise , wanderTimeMultiplier , zWander ;
    
    float _time = ofGetElapsedTimef() * wanderTimeMultiplier ;
    float _x = sin( _time ) * xWander + ofNoise ( _time * 0.12 ) * xWanderNoise ;
    float _y = cos( _time * 0.35 ) * yWander + ofNoise ( _time ) * yWanderNoise ;
    float _z = cos( _time ) * zWander ; 
    forcePosition = forceTarget + ofVec3f( _x , _y , _z ) ; //ofVec3f()  ; //() ; // sin ( ofGetElapsedTimef() ) * xWander  , cos ( ofGetElapsedTimef() ) * yWander , 0 )  + center ;
    
    float _forceStrength = forceStrength * low ;
    //cout << "force Strength : " << _forceStrength << endl ;
    float _forceRadius = forceRadius * low ;
    
    
    //Allocate and retrieve mouse values once.
    const ofVec3f origin = ofVec3f(0,0,0);
    
    if ( low < 0.15 )
        bSeekEnabled = true ;
    else
        bSeekEnabled = false ;
    //Create an iterator to cycle through the vector
    std::vector<Particle>::iterator p ;
    for ( p = particles.begin() ; p != particles.end() ; p++ )
    {
        ratio = 1.0f ;
        p->velocity *= friction ;
        //reset acceleration every frame
        p->acceleration = ofVec3f() ;
        
        diff = (forcePosition - p->position).normalize() ;
        diff *= _forceStrength ; 
        
        
        dist = forcePosition.distance( p->position ) ;
        
        //If within the zone of interaction
        if ( dist * .5 < _forceRadius )
        {
            ratio = -1. + dist / _forceRadius ;
            //Repulsion
            if ( bSeekEnabled )
                p->acceleration -= ( diff * _forceStrength) ;
            //Attraction
            else
                p->acceleration += ( diff * _forceStrength ) ;
        }
        if ( bSpringEnabled )
        {
            //Move back to the original position
            p->acceleration += (springFactor * (p->spawnPoint - p->position ));
        }
        
        ofVec3f v = p->acceleration * ratio ;
        v.x = ofClamp( v.x , -maxParticleSpeed , maxParticleSpeed ) ;
        v.y = ofClamp( v.y , -maxParticleSpeed , maxParticleSpeed ) ;
        v.z = ofClamp( v.z , -maxParticleSpeed , maxParticleSpeed ) ;
       
        p->velocity += v; 
        p->position += p->velocity ;
    }
    
    if ( ofGetFrameNum() % numFramesUntilTransition == 0 )
    {
        curImageIndex++ ;
        setupParticles() ;
    }
    
    
}

//--------------------------------------------------------------
void ImageSpringParticles::draw()
{
    
        
    
    glPointSize(1.0f ) ;
    ofSetColor( 0 , 0 , 0 ) ;
    ofRect( -1000, -1000 , 3000, 3000 ) ;
    fadeFbo.begin() ;
    ofEnableAlphaBlending() ;
    
    ofSetColor( 0 , 0 , 0 , fadeAlpha ) ;
    ofRect( -1000 , -1000 , 3000, 3000 ) ;
    if ( bAdditiveBlend ) 
    ofEnableBlendMode( OF_BLENDMODE_ADD ) ;
    cameraMan->begin() ; 
 
        
    ofPushMatrix() ;
        ofPushMatrix() ;
        //Offset by the center so that our openGL pivot point is in the center of the screen
        ofPoint center = ofPoint ( ofGetWidth() /2 , ofGetHeight() /2 ) ;
        ofTranslate( images[ curImageIndex ].getWidth() / -2 , images[ curImageIndex ].getHeight()/-2 , cameraMan->zOffset ) ;
      
        //Draw particles
        //Begin the openGL Drawing Mode
        glBegin(GL_POINTS);
        //glBegin(GL_LINES);
        //glBegin(GL_TRIANGLES);

        ofEnableAlphaBlending() ;

        //Create an iterator to cycle through the vector
        std::vector<Particle>::iterator p ;
        for ( p = particles.begin() ; p != particles.end() ; p++ )
        {
            ofSetColor ( p->color , particleAlpha ) ;
            glVertex3f(p->position.x , p->position.y , p->position.z );
        }

        ofPopMatrix() ;
        glEnd();

        ofEnableAlphaBlending() ;
    
        ofSetColor( 255 ) ;
    if ( bShowSphere )
        ofSphere( forcePosition , 5 ) ;
    
        ofPopMatrix() ;
    cameraMan->end() ;
    
   

    fadeFbo.end() ;
 
    ofSetColor ( 255 , 255 , 255 ) ;
    fadeFbo.draw( 0 , 0 ) ;
}

















