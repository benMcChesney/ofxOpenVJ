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
	drawNumCubes = 0.0f;

    generateRandomCubes() ;
}

void SimpleScene::setupGui(float a_x, float a_y)
{
    BaseScene::setupGui( a_x , a_y ) ;
    
	ofxOpenVJConstants *c = ofxOpenVJConstants::Instance(); 
	gui.add(spawnRadius.setup("SPAWN RADIUS", spawnRadius, 300, 1500, c->GUI_WIDGET_WIDTH , c->GUI_WIDGET_HEIGHT )); 
	gui.add(numCubes.setup("NUM CUBES", numCubes, 1, 2000, c->GUI_WIDGET_WIDTH, c->GUI_WIDGET_HEIGHT));
	gui.add(cubeSize.setup("CUBE SIZE", cubeSize, 1, 100, c->GUI_WIDGET_WIDTH, c->GUI_WIDGET_HEIGHT));
	gui.add(generateCubesButton.setup("REGENERATE CUBES" , c->GUI_WIDGET_HEIGHT , c->GUI_WIDGET_HEIGHT )); 

	generateCubesButton.addListener(this, &SimpleScene::generateRandomCubes); 
    loadSettings() ; 
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
        cubes.push_back( new ColorSquare() ) ;
        cubes[i]->color = ofColor::fromHsb( ofRandom( 255 ) , 255 , 255 ) ;
		cubes[i]->position = ofPoint(ofRandom(0, ofGetWidth()), ofRandom(0, ofGetHeight()));
        cubes[i]->size = cubeSize ;
    }
    
    
}

void SimpleScene::update()
{
    BaseScene::update( ) ; 
}

void SimpleScene::draw()
{
    //cameraManager->begin() ;
    
    ofSetColor( 255 , 0 , 0 ) ;

    int count = 0 ;
    for( auto cube = cubes.begin() ; cube != cubes.end() ; cube++ )
    {
        if ( count < drawNumCubes )
        {
            int cubeGroup = count % 3 ;
			ofColor newColor; 
			ofColor c; 
			c = (*cube)->color;

			if (cubeGroup == 0 )
			{
				
				newColor = c.lerp(ofColor::red, soundManager->beatTracker.isKick()); 
				//ofSetColor(newColor);
			}
	
              
			else if (cubeGroup == 1 )
			{
				newColor = c.lerp(ofColor::green, soundManager->beatTracker.isSnare());
				//ofSetColor(newColor);
			}
                
			else if (cubeGroup == 2)
			{
				newColor = c.lerp(ofColor::blue, soundManager->beatTracker.isHat());
				//ofSetColor(newColor);
			}

			ofSetColor( newColor );
			ofSetRectMode(OF_RECTMODE_CENTER); 
            ofRect( (*cube)->position , (*cube)->size , (*cube)->size) ;
			ofSetRectMode(OF_RECTMODE_CORNER);
        }
        count++ ; 
    }
    
    //cameraManager->end() ;
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

