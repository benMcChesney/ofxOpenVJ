//
//  TestScene.cpp
//  KinectPerformanceV01
//
//  Created by Ben Mcchesney on 11/6/12.
//
//

#include "CircleNoiseScene.h"

//--------------------------------------------------------------
CircleNoiseScene::CircleNoiseScene() {
    
}

//--------------------------------------------------------------
CircleNoiseScene::~CircleNoiseScene() {
    
}

//--------------------------------------------------------------
void CircleNoiseScene::setup() {
    
    string path = ofToDataPath( "../../../../ofxOpenVJ/shaders/" ) ;
    shader.load( path+"basic.vert", path+"CircleNoise.frag" ) ;
    
    
    maskFbo.allocate( ofGetWidth() , ofGetHeight() ) ;
    maskFbo.begin() ;
    ofClear( 1 , 1 ,1 , 0 ) ;
    maskFbo.end() ; 
    simpleMask.setup("shaders/composite" , ofRectangle( 0 , 0, ofGetWidth() , ofGetHeight() ) ) ;
                     
}

//--------------------------------------------------------------
void CircleNoiseScene::setupGui(float a_x, float a_y) {
    // creates new gui and adds the name to it //
    BaseScene::setupGui(a_x, a_y);
    
    
    ofAddListener( gui->newGUIEvent, this, &CircleNoiseScene::guiEvent );
}

//--------------------------------------------------------------
void CircleNoiseScene::guiEvent(ofxUIEventArgs &e) {
    
}

//--------------------------------------------------------------
void CircleNoiseScene::activate() {
    if(fbo.getWidth() != getWidth() || fbo.getHeight() != getHeight()) {
        fbo.allocate( getWidth() , getHeight(), GL_RGBA ) ;
        fbo.begin() ;
        ofClear( 1 , 1 , 1 , 0 ) ;
        fbo.end() ;
    }
}

//--------------------------------------------------------------
void CircleNoiseScene::deactivate() {
    // turn off the gui //
    BaseScene::deactivate();
}

//--------------------------------------------------------------
void CircleNoiseScene::update() {
        kinectMan->update();
    if(kinectMan->isFrameNew()) {
        kinectMan->calculateCVOperations();
        
     //   if( ( ofGetElapsedTimeMillis() - lastAddTime  ) > millisDelay ) {
     //       addContour();
            //cout << "lines.size() = " << lines.size() << " particles.size() = " << particles.size() << endl;
    
    }
}

//--------------------------------------------------------------
void CircleNoiseScene::draw() {
    
    fbo.begin() ; 
    shader.begin();
        //we want to pass in some varrying values to animate our type / color
        shader.setUniform1f("time", ofGetElapsedTimef() );
        
        shader.setUniform1f( "low" , low ) ;
        shader.setUniform1f( "mid" , mid ) ;
        shader.setUniform1f( "high" , high ) ;
        shader.setUniform2f("resolution",getWidth() , getHeight() );
        
        ofSetColor( 255 , 255 , 255 ) ;
        ofRect( 0 ,0, getWidth() , getHeight() ) ;
    shader.end() ;
    
    ofEnableBlendMode( OF_BLENDMODE_ADD ) ;
    ofSetColor( 255 , 255 , 255 , 120 ) ;
   // for ( int i = 0 ; i < 2 ; i++ )
        fbo.draw( 0 , 0 ) ; 
    
    fbo.end() ;
    
    
    maskFbo.begin() ;
    ofSetColor( 255 , 255 , 255 ) ;
    kinectMan->grayImage.draw( 0 , 0, ofGetWidth() , ofGetHeight() ) ;
    maskFbo.end() ;

    
    ofEnableAlphaBlending() ;
    ofSetColor( 255 , 255 , 255 );
    ofPushMatrix() ;
  //  simpleMask.drawMask( maskFbo.getTextureReference() , fbo.getTextureReference() ,  0, 0, 1.0f) ;
        fbo.draw( 0 , 0 ) ;
    ofPopMatrix( ) ;
    
 
}

//--------------------------------------------------------------
void CircleNoiseScene::drawDebug() {
    
}
















