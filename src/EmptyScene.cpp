//
//  TestScene.cpp
//  KinectPerformanceV01
//
//  Created by Ben McChesney on 11/6/12.
//
//

#include "EmptyScene.h"

//--------------------------------------------------------------
EmptyScene::EmptyScene() {
    
}

//--------------------------------------------------------------
EmptyScene::~EmptyScene() {
    
}

//--------------------------------------------------------------
void EmptyScene::setup() {
    
}

//--------------------------------------------------------------
void EmptyScene::setupGui(float a_x, float a_y)
{
    // creates new gui and adds the name to it //
    BaseScene::setupGui(a_x, a_y);
    
    ofAddListener( gui->newGUIEvent, this, &EmptyScene::guiEvent );
    loadSettings() ; 
}

//--------------------------------------------------------------
void EmptyScene::guiEvent(ofxUIEventArgs &e) {
    
    BaseScene::guiEvent( e ) ; 

 }

//--------------------------------------------------------------
void EmptyScene::activate() {
    
}

//--------------------------------------------------------------
void EmptyScene::deactivate() {
    
    // turn off the gui //
    BaseScene::deactivate();
}

//--------------------------------------------------------------
void EmptyScene::update() {
}

//--------------------------------------------------------------
void EmptyScene::draw() {
}
