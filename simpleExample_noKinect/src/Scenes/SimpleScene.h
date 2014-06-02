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
   
    struct ColorCube
    {
        ofPoint position  ;
        ofColor color = ofColor::gray ;
        float size = 50.0f ;
    };

    void setup();
    void setupGui(float a_x=0, float a_y=0);
    void guiEvent(ofxUIEventArgs &e);
    
    void update();
    void draw();
    
    void activate();
    void deactivate();
   
    vector< ColorCube* > cubes ;
    
    float spawnRadius ;
    float numCubes ;
    float cubeSize ;
    
       
    ofPoint getRandomPointInSpawnRadius( ) ;
    
    void generateRandomCubes( ) ; 
    
    
};
