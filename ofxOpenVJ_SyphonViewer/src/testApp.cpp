#include "testApp.h"

const int width = 800;
const int height = 600;

//--------------------------------------------------------------
void testApp::setup(){

	mClient.setup();
    
  //  mClient.setApplicationName("ofxOpenVJ");
    mClient.setServerName("ofxOpenVJ");
	    
    bShowMouse = false ;
    ofHideCursor() ; 
	ofSetFrameRate(60); // if vertical sync is off, we can go a bit fast... this caps the framerate at 60fps.
}

//--------------------------------------------------------------
void testApp::update(){
}

//--------------------------------------------------------------
void testApp::draw(){
	
    //ofBackground( 0 , 0 ,0 ) ;
    ofSetColor( 255 , 255 , 255 ) ;
    ofEnableAlphaBlending() ;
    mClient.draw( 0 , 0 , ofGetWidth() , ofGetHeight() ) ;
}


//--------------------------------------------------------------
void testApp::keyPressed  (int key)
{
    switch ( key )
    {
        case 'f':
        case 'F':
            ofToggleFullscreen() ;
            break ;
            
        case 'm':
        case 'M':
            bShowMouse = !bShowMouse ;
            if ( bShowMouse )
                ofShowCursor() ;
            else
                ofHideCursor() ; 
    }
}
