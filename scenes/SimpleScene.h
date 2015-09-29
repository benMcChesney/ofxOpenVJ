//
//  SimpleScene.h
//  simpleExample
//
//  Created by Ben McChesney on 5/15/14.
//
//

#pragma once

#include "SimpleScene.h"
#include "BaseScene.h"

class SimpleScene : public BaseScene
{
public :
    SimpleScene( ) ;
    SimpleScene( int a_index, string a_name ):BaseScene( a_index, a_name ) {}
   
    struct ColorSquare
    {
        ofPoint position  ;
        ofColor color = ofColor::gray ;
        float size = 50.0f ;
    };

    void setup();
    void setupGui(float a_x=0, float a_y=0);
//    void guiEvent(ofxUIEventArgs &e);
    
    void update();
    void draw();
    
    void activate();
    void deactivate();
   
    vector< ColorSquare* > cubes ;
    
    ofxFloatSlider spawnRadius ;
	ofxFloatSlider numCubes ;
	ofxFloatSlider cubeSize ;
    
    bool transitionIn( float delay , float transitionTime );
    bool transitionOut( float delay , float transitionTime ) ;
    
    ofPoint getRandomPointInSpawnRadius( ) ;
    
	ofxButton generateCubesButton; 
    void generateRandomCubes( ) ;
	float drawNumCubes;
    
};
