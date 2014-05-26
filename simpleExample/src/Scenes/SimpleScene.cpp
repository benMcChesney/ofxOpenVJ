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
    spawnRadius = 500 ;
    numCubes = 60 ;
    cubeSize = 50 ; 
    generateRandomCubes() ; 
}

void SimpleScene::setupGui(float a_x, float a_y)
{
    BaseScene::setupGui( a_x , a_y ) ;
    
    gui->addSlider("SPAWN RADIUS", 300, 1500, &spawnRadius ) ;
    gui->addSlider("NUM CUBES" , 1, 2000 , &numCubes ) ;
    gui->addSlider("CUBE SIZE", 1 , 100 , &cubeSize ) ;
    
    gui->addButton("GENERATE CUBES" , false ) ;
    
    ofAddListener( gui->newGUIEvent , this , &SimpleScene::guiEvent ) ;
}

void SimpleScene::guiEvent(ofxUIEventArgs &e )
{
    string name = e.getName() ;
    if ( name == "GENERATE CUBES" && e.getButton()->getValue() == true )
        generateRandomCubes() ; 
}

void SimpleScene::generateRandomCubes( )
{
    ofLogNotice() << " SimpleScene::generateRandomCubes " ; 
    while ( cubes.size() > 0 )
    {
        delete (*cubes.begin()) ;
        cubes.erase( cubes.begin() ) ;
    }
    cubes.clear() ;
    
    for ( int i = 0 ; i < (int)numCubes  ; i++ )
    {
        cubes.push_back( new ColorCube() ) ;
        cubes[i]->color = ofColor::fromHsb( ofRandom( 255 ) , 255 , 255 ) ;
        cubes[i]->position = getRandomPointInSpawnRadius() ;
        cubes[i]->size = cubeSize ;
    }
    
    
}

void SimpleScene::update()
{
  
}

void SimpleScene::draw()
{
    cameraMan->begin() ;
    
    ofSetColor( 255 , 0 , 0 ) ;
    for( auto cube = cubes.begin() ; cube != cubes.end() ; cube++ )
    {
        ofSetColor( (*cube)->color ) ; 
        ofDrawBox( (*cube)->position , (*cube)->size ) ;
    }
    
    cameraMan->end() ; 
}


void SimpleScene::activate()
{
    BaseScene::activate() ;
    generateRandomCubes() ; 
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

