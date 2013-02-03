//
//  TestScene.cpp
//  KinectPerformanceV01
//
//  Created by Nick Hardeman on 11/6/12.
//
//

#include "AlienTunnelScene.h"

//--------------------------------------------------------------
AlienTunnelScene::AlienTunnelScene() {
    
}

//--------------------------------------------------------------
AlienTunnelScene::~AlienTunnelScene() {
    
}

//--------------------------------------------------------------
void AlienTunnelScene::setup() {
    
    string path = ofToDataPath( "../../../../ofxOpenVJ/shaders/" ) ;
    shader.load( path + "AlienTunnel.vert", path + "AlienTunnel.frag" ) ;

}

//--------------------------------------------------------------
void AlienTunnelScene::setupGui(float a_x, float a_y) {
    // creates new gui and adds the name to it //
    BaseScene::setupGui(a_x, a_y);
    
    
    ofAddListener( gui->newGUIEvent, this, &AlienTunnelScene::guiEvent );
}

//--------------------------------------------------------------
void AlienTunnelScene::guiEvent(ofxUIEventArgs &e) {
    
}

//--------------------------------------------------------------
void AlienTunnelScene::activate() {
    
}

//--------------------------------------------------------------
void AlienTunnelScene::deactivate() {
    // turn off the gui //
    BaseScene::deactivate();
}

//--------------------------------------------------------------
void AlienTunnelScene::update() {
    
}

//--------------------------------------------------------------
void AlienTunnelScene::draw() {
    
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
 
}

//--------------------------------------------------------------
void AlienTunnelScene::drawDebug() {
    
}
















