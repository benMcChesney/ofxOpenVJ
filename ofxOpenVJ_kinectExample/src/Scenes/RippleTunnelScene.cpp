//
//  TestScene.cpp
//  KinectPerformanceV01
//
//  Created by Ben Mcchesney on 11/6/12.
//
//

#include "RippleTunnelScene.h"

//--------------------------------------------------------------
RippleTunnelScene::RippleTunnelScene() {
    
}

//--------------------------------------------------------------
RippleTunnelScene::~RippleTunnelScene() {
    
}

//--------------------------------------------------------------
void RippleTunnelScene::setup() {
    
    string path = ofToDataPath( "../../../../ofxOpenVJ/shaders/" ) ;
    shader.load( path+"basic.vert", path+"RippleTunnel.frag" ) ;

}

//--------------------------------------------------------------
void RippleTunnelScene::setupGui(float a_x, float a_y) {
    // creates new gui and adds the name to it //
    BaseScene::setupGui(a_x, a_y);
    
    
    ofAddListener( gui->newGUIEvent, this, &RippleTunnelScene::guiEvent );
}

//--------------------------------------------------------------
void RippleTunnelScene::guiEvent(ofxUIEventArgs &e) {
    
}

//--------------------------------------------------------------
void RippleTunnelScene::activate() {
    if(fbo.getWidth() != getWidth() || fbo.getHeight() != getHeight()) {
        fbo.allocate( getWidth() , getHeight(), GL_RGBA ) ;
        fbo.begin() ;
        ofClear( 1 , 1 , 1 , 0 ) ;
        fbo.end() ;
    }
}

//--------------------------------------------------------------
void RippleTunnelScene::deactivate() {
    // turn off the gui //
    BaseScene::deactivate();
}

//--------------------------------------------------------------
void RippleTunnelScene::update() {

}

//--------------------------------------------------------------
void RippleTunnelScene::draw() {
    
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
    
    ofEnableAlphaBlending() ;
    ofSetColor( 255 , 255 , 255 );
    ofPushMatrix() ;
        fbo.draw( 0 , 0 ) ;
    ofPopMatrix( ) ;
    
 
}

//--------------------------------------------------------------
void RippleTunnelScene::drawDebug() {
    
}
















