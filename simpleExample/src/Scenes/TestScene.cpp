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
void TestScene::update() {
    BaseScene::update( ) ; 
}

//--------------------------------------------------------------
void TestScene::draw() {
    ofSetColor(100, 20, 190, shapeAlpha * 255.0f );
    ofPushMatrix();
    {

        ofTranslate( ofGetWidth()*.5f, ofGetHeight()*.5f, 0 );
        ofScale( shapeScale , shapeScale , shapeScale  ); 
        ofRotate( cos( ofGetFrameNum()*.1 ) * 40 , 0, 0, 1);
        ofRect(-300, -200, 600, 400);
    }
    ofPopMatrix() ; 
}

bool TestScene::transitionIn( float delay , float transitionTime )
{
    
    if ( BaseScene::transitionIn( delay , transitionTime ) == false )
        return false ;
    else
    {
        //Build the scene out
        Tweenzor::add( &shapeAlpha , 0.0f , 1.0f , delay , transitionTime , EASE_OUT_QUAD ) ;
        Tweenzor::add( &shapeScale , 0.0f , 1.0f , delay , transitionTime , EASE_OUT_QUAD ) ;
    }
    
    return true ;
}

bool TestScene::transitionOut( float delay , float transitionTime )
{
    if ( BaseScene::transitionOut( delay , transitionTime ) == false )
        return false ;
    else
    {
        Tweenzor::add( &shapeAlpha , shapeAlpha , 0.0f , delay , transitionTime , EASE_OUT_QUAD ) ;
        Tweenzor::add( &shapeScale , shapeScale , 0.0f , delay , transitionTime , EASE_OUT_QUAD ) ;
    }
    return true ;
}













