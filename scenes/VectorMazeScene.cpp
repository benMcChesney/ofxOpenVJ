//
//  TestScene.cpp
//  KinectPerformanceV01
//
//  Created by Ben McChesney on 11/6/12.
//
//

#include "VectorMazeScene.h"

//--------------------------------------------------------------
VectorMazeScene::VectorMazeScene() {
    
}

//--------------------------------------------------------------
VectorMazeScene::~VectorMazeScene() {
    
}

//--------------------------------------------------------------
void VectorMazeScene::setup()
{
    //icon.svg.clear() ;
    //cout << "LOADING : " << info.files[0] << endl ;
    icon.setup( "maze.svg" , lineWidth ) ;
    
    Tweenzor::add( &icon.completion , 0.0f , maxCompletion , 0.0f , 2.0f , EASE_OUT_QUAD ) ;
    Tweenzor::getTween( &icon.completion )->setRepeat( -1, true );
}

//--------------------------------------------------------------
void VectorMazeScene::setupGui(float a_x, float a_y) {
    // creates new gui and adds the name to it //
    BaseScene::setupGui(a_x, a_y);
    
    //float animationTime ;
    float maxCompletion ;
    
    gui->addSlider( "ANIMATION TIME" , 1.0f , 25.0f , &animationTime ) ;
    gui->addSlider( "MAX COMPLETION" , 0.1f , 1.0f , &animationTime ) ;
    gui->addSlider( "LINE WIDTH" , 1.0f , 8.0f , &icon.lineWidth ) ;
    
    ofAddListener( gui->newGUIEvent, this, &VectorMazeScene::guiEvent );
    loadSettings() ; 
}

//--------------------------------------------------------------
void VectorMazeScene::guiEvent(ofxUIEventArgs &e) {
    
    BaseScene::guiEvent( e ) ; 

 }

//--------------------------------------------------------------
void VectorMazeScene::update()
{
    BaseScene::update( ) ;
    
  
}

//--------------------------------------------------------------
void VectorMazeScene::draw() {
    
    ofSetColor( 255 , 255 ,255 ) ;
  
    ofPushMatrix() ;
    
    ofPopMatrix();
    
}

void VectorMazeScene::drawDebug( )
{
    stringstream ss ;

    ofDrawBitmapStringHighlight( ss.str() , 50 , 50 ) ;
}

bool VectorMazeScene::transitionIn( float delay , float transitionTime )
{
    if ( BaseScene::transitionIn( delay , transitionTime ) == false )
        return false ;
    else
    {
        
    }
    
    return true ;
}

bool VectorMazeScene::transitionOut( float delay , float transitionTime )
{
    if ( BaseScene::transitionOut( delay , transitionTime ) == false )
        return false ;
    else
    {

    }
    return true ;
}

