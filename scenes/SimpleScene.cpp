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
    drawNumCubes = 0.0f ; 
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
    loadSettings() ; 
}

void SimpleScene::guiEvent(ofxUIEventArgs &e )
{
    BaseScene::guiEvent( e ) ; 
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
    BaseScene::update( ) ; 
}

void SimpleScene::draw()
{
    cameraManager->begin() ;
    
    ofSetColor( 255 , 0 , 0 ) ;

    int count = 0 ;
    for( auto cube = cubes.begin() ; cube != cubes.end() ; cube++ )
    {
        if ( count < drawNumCubes )
        {
            int cubeGroup = count % 3 ;
			
            if ( cubeGroup == 0 && soundManager->beatTracker.isKick() == true )
                ofSetColor( ofColor::red ) ;
            else if ( cubeGroup == 1 && soundManager->beatTracker.isSnare() == true )
                ofSetColor( ofColor::green ) ;
            else if ( cubeGroup == 2 && soundManager->beatTracker.isHat() == true )
                ofSetColor( ofColor::blue ) ;
            else
                ofSetColor( (*cube)->color ) ;
            ofDrawBox( (*cube)->position , (*cube)->size ) ;
        }
        count++ ; 
    }
    
    cameraManager->end() ;
    sceneTransitionTimer.draw( 50 , 50 ) ;
}



bool SimpleScene::transitionIn( float delay , float transitionTime )
{
    
    if ( BaseScene::transitionIn( delay , transitionTime ) == false )
        return false ;
    else
    {
        cout << "simple scene transitionin ! " << endl ; 
        //Build the scene out
        Tweenzor::add( &drawNumCubes , 0.0f , (float)numCubes , delay , transitionTime , EASE_OUT_QUAD ) ;
    }

    return true ;
}

bool SimpleScene::transitionOut( float delay , float transitionTime )
{
    if ( BaseScene::transitionOut( delay , transitionTime ) == false )
        return false ;
    else
    {
        Tweenzor::add( &drawNumCubes , numCubes , 0.0f , delay , transitionTime , EASE_OUT_QUAD ) ;
    }
    return true ;
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

