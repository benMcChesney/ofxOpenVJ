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
   
    void setup();
    void setupGui(float a_x=0, float a_y=0);
    void guiEvent(ofxUIEventArgs &e);
    
    void update();
    void draw();
    
    void activate();
    void deactivate();
   
    vector< ofPoint > lowCubes ;
    vector< ofPoint > midCubes ;
    vector< ofPoint > highCubes ;
    
    float spawnRadius ;
    ofPoint getRandomPointInSpawnRadius( ) ;
};
