//
//  TestScene.cpp
//  KinectPerformanceV01
//
//  Created by Nick Hardeman on 11/6/12.
//
//

#include "TestScene.h"

//--------------------------------------------------------------
TestScene::TestScene() {
    
}

//--------------------------------------------------------------
TestScene::~TestScene() {
    
}

//--------------------------------------------------------------
void TestScene::setup() {
    
}

//--------------------------------------------------------------
void TestScene::setupGui(float a_x, float a_y) {
    // creates new gui and adds the name to it //
    BaseScene::setupGui(a_x, a_y);
    
    
    ofAddListener( gui->newGUIEvent, this, &TestScene::guiEvent );
}

//--------------------------------------------------------------
void TestScene::guiEvent(ofxUIEventArgs &e) {
    name = e.getName() ; 
    if ( name == "LOAD SETTINGS" && e.getButton()->getValue() == true )
        loadSettings() ;
    
    if ( name == "SAVE SETTINGS" && e.getButton()->getValue() == true )
        saveSettings() ;
    
}

//--------------------------------------------------------------
void TestScene::activate() {
    
}

//--------------------------------------------------------------
void TestScene::deactivate() {
    // turn off the gui //
    BaseScene::deactivate();
}

//--------------------------------------------------------------
void TestScene::update() {
    
}

//--------------------------------------------------------------
void TestScene::draw() {
    ofSetColor(100, 20, 190);
    glPushMatrix();
    {
        glTranslatef( ofGetWidth()*.5f, ofGetHeight()*.5f, 0 );
        glRotatef( cos( ofGetFrameNum()*.1 ) * 3, 0, 0, 1);
        ofRect(-300, -200, 600, 400);
    }
    glPopMatrix();
}

















