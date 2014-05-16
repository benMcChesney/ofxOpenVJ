//
//  SimpleScene.cpp
//  simpleExample
//
//  Created by Ben McChesney on 5/15/14.
//
//

#include "SimpleScene.h"

void SimpleScene::setup()
{
        /*
    vector< ofPoint > lowCubes ;
    vector< ofPoint > midCubes ;
    vector< ofPoint > highCubes ;
         */
    
    spawnRadius = 500 ;
    float numPerRange = 50 ;
    for ( int i = 0 ; i < numPerRange ; i++ )
    {
        lowCubes.push_back( getRandomPointInSpawnRadius() ) ;
        midCubes.push_back( getRandomPointInSpawnRadius() ) ;
        highCubes.push_back( getRandomPointInSpawnRadius() ) ;
    }
}

void SimpleScene::setupGui(float a_x, float a_y)
{
    BaseScene::setupGui( a_x , a_y ) ;
    
    
}

void SimpleScene::guiEvent(ofxUIEventArgs &e )
{
    
}


void SimpleScene::update()
{
    
}

void SimpleScene::draw()
{
    cameraMan->begin() ;
    
    ofColor c ;
    
    ofSetColor( 255 , 0 , 0 ) ;
    if ( beatDetector->isBeat( 0 ) )
        ofSetColor( 255 ) ; 
    for( auto cube = lowCubes.begin() ; cube != lowCubes.end() ; cube++ )
    {
        ofDrawBox( (*cube), 25 ) ; 
    }
    
    ofSetColor( 0 , 255 , 0 ) ;
    if ( beatDetector->isMid() )
        ofSetColor( 255 ) ;
    for( auto cube = midCubes.begin() ; cube != midCubes.end() ; cube++ )
    {
        ofDrawBox( (*cube), 25 ) ;
    }
    
    ofSetColor( 0 , 0 , 255 ) ;
    if ( beatDetector->isHigh() )
        ofSetColor( 255 ) ;
    
    for( auto cube = highCubes.begin() ; cube != highCubes.end() ; cube++ )
    {
        ofDrawBox( (*cube), 25 ) ;
    }
    cameraMan->end() ;
}


void SimpleScene::activate()
{
    BaseScene::activate() ;
}

void SimpleScene::deactivate()
{
    BaseScene::deactivate() ; 
}

ofPoint SimpleScene::getRandomPointInSpawnRadius( )
{
    float r = spawnRadius ; 
    ofPoint p = ofPoint ( ofRandom( -r , r ) , ofRandom ( -r , r ) , ofRandom ( - r, r ) ) ;
    return p ; 
}

