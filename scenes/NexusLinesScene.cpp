//
//  TestScene.cpp
//  KinectPerformanceV01
//
//  Created by Ben McChesney on 11/6/12.
//
//

#include "NexusLinesScene.h"

//--------------------------------------------------------------
NexusLinesScene::NexusLinesScene() {
    
}

//--------------------------------------------------------------
NexusLinesScene::~NexusLinesScene() {
    
}

//--------------------------------------------------------------
void NexusLinesScene::setup()
{
    logo.loadImage( "logo.png" ) ;
    logo.setAnchorPercent( 0.5 , 0.5 ) ;
}

//--------------------------------------------------------------
void NexusLinesScene::setupGui(float a_x, float a_y) {
    // creates new gui and adds the name to it //
    BaseScene::setupGui(a_x, a_y);
    
    //gui->addSlider( "OUTLINE SMOOTHING", 1, 35 , &outlineSmoothing ) ;
    gui->addSlider("MIN TRAVEL TIME", 1.0f , 20.0f , &minTravelTime ) ;
    gui->addSlider("MAX TRAVEL TIME", 1.0f , 20.0f , &maxTravelTime ) ;
    
    ofAddListener( gui->newGUIEvent, this, &NexusLinesScene::guiEvent );
    loadSettings() ; 
}

//--------------------------------------------------------------
void NexusLinesScene::guiEvent(ofxUIEventArgs &e) {
    
    BaseScene::guiEvent( e ) ; 

 }

//--------------------------------------------------------------
void NexusLinesScene::update()
{
    BaseScene::update( ) ;
    
    if ( ofGetFrameNum() % 15 == 0  )
        addNewLine() ; 
}

//--------------------------------------------------------------
void NexusLinesScene::draw() {
    
    ofSetColor( 255 , 255 ,255 ) ;
  
    ofPushMatrix() ;
    for ( auto line = lines.begin() ; line != lines.end() ; line++ )
    {
        (*line)->draw( )  ;
        
    }
    
    
    ofPopMatrix();
    
    ofSetColor( 255 ) ;
    logo.draw( ofGetWidth() / 2 , ofGetHeight() / 2 ) ;
    
}

void NexusLinesScene::drawDebug( )
{
    stringstream ss ;
    ss << " # of lines : " << lines.size() << endl ;
    if ( lines.size() > 0 )
        ss << "[0] " << lines[0]->origin << " -> " << lines[0]->destination << endl ;
    ofDrawBitmapStringHighlight( ss.str() , 50 , 50 ) ;
}

void NexusLinesScene::addNewLine( )
{
    ofLogNotice() << " adding a new line ! " ;
    ofColor c = ofColor::blue ;
    
    
    int seed = ofRandom( 0 , 1000 ) ;
    bool bFromRight = true ;
    if ( seed %2 == 0 )
        bFromRight = false ;
    
    if ( lines.size() % 2 == 0 )
        c = ofColor::green ;
    
    lines.push_back( new NexusLine() ) ;
    lines[ lines.size() -1 ]->setup( c , ofRandom( minTravelTime , maxTravelTime ) ) ;
    lines[ lines.size() -1 ]->start( ofRandom( 15 , ofGetHeight() - 15 ) , bFromRight ) ;
    
    
   // drawDebug( ) ;
}

bool NexusLinesScene::transitionIn( float delay , float transitionTime )
{
    if ( BaseScene::transitionIn( delay , transitionTime ) == false )
        return false ;
    else
    {
        completion = 0.0f; 
        Tweenzor::add( &completion , completion , 3.0f , delay , transitionTime ) ;
    }
    
    return true ;
}

bool NexusLinesScene::transitionOut( float delay , float transitionTime )
{
    if ( BaseScene::transitionOut( delay , transitionTime ) == false )
        return false ;
    else
    {
        Tweenzor::add( &completion , completion , 0.0f , delay , transitionTime ) ;
    }
    return true ;
}

