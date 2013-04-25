//
//  TestScene.cpp
//  KinectPerformanceV01
//
//  Created by Ben Mcchesney on 11/6/12.
//
//

#include "HexTunnelScene.h"

//--------------------------------------------------------------
HexTunnelScene::HexTunnelScene() {
    
}

//--------------------------------------------------------------
HexTunnelScene::~HexTunnelScene() {
    
}

//--------------------------------------------------------------
void HexTunnelScene::setup() {
    
    string path = ofToDataPath( "../../../../ofxOpenVJ/shaders/" ) ;
    shader.load( path + "basic.vert", path + "HexTunnel.frag" ) ;

}

//--------------------------------------------------------------
void HexTunnelScene::setupGui(float a_x, float a_y) {
    // creates new gui and adds the name to it //
    BaseScene::setupGui(a_x, a_y);
    
    
    ofAddListener( gui->newGUIEvent, this, &HexTunnelScene::guiEvent );
}

//--------------------------------------------------------------
void HexTunnelScene::guiEvent(ofxUIEventArgs &e) {
    
}

//--------------------------------------------------------------
void HexTunnelScene::activate() {
    
}

//--------------------------------------------------------------
void HexTunnelScene::deactivate() {
    // turn off the gui //
    BaseScene::deactivate();
}

//--------------------------------------------------------------
void HexTunnelScene::update() {
    
  }

//--------------------------------------------------------------
void HexTunnelScene::draw() {
    
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
void HexTunnelScene::drawDebug() {
    
}
















