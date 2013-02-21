//
//  TestScene.cpp
//  KinectPerformanceV01
//
//  Created by Nick Hardeman on 11/6/12.
//
//

#include "TriangleTunnelScene.h"

//--------------------------------------------------------------
TriangleTunnelScene::TriangleTunnelScene() {
    
}

//--------------------------------------------------------------
TriangleTunnelScene::~TriangleTunnelScene() {
    
}

//--------------------------------------------------------------
void TriangleTunnelScene::setup() {
    
    string path = ofToDataPath( "../../../../ofxOpenVJ/shaders/" ) ;
    shader.load( path+"basic.vert", path+"triangleLightTunnel.frag" ) ;

}

//--------------------------------------------------------------
void TriangleTunnelScene::setupGui(float a_x, float a_y) {
    // creates new gui and adds the name to it //
    BaseScene::setupGui(a_x, a_y);
    
    
    ofAddListener( gui->newGUIEvent, this, &TriangleTunnelScene::guiEvent );
}

//--------------------------------------------------------------
void TriangleTunnelScene::guiEvent(ofxUIEventArgs &e) {
    
}

//--------------------------------------------------------------
void TriangleTunnelScene::activate() {
    if(fbo.getWidth() != getWidth() || fbo.getHeight() != getHeight()) {
        fbo.allocate( getWidth() , getHeight(), GL_RGBA ) ;
        fbo.begin() ;
        ofClear( 1 , 1 , 1 , 0 ) ;
        fbo.end() ;
    }
}

//--------------------------------------------------------------
void TriangleTunnelScene::deactivate() {
    // turn off the gui //
    BaseScene::deactivate();
}

//--------------------------------------------------------------
void TriangleTunnelScene::update() {

}

//--------------------------------------------------------------
void TriangleTunnelScene::draw() {
    
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
void TriangleTunnelScene::drawDebug() {
    
}
















