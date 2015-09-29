/*
    EmptyScene
    ofxOpenVJ
 
    Created by Ben Mcchesney on 6/1/14.
 
    This class serves as the most basic functionalities a ofxOpenVJ scene should have
    When creating a new scene it's recommended to copy this one and rename it as a starting point
 
*/

#pragma once 
#include "BaseScene.h"
#include "ofxTweenzor.h"

class EmptyScene : public BaseScene {
public:
    EmptyScene();
    EmptyScene( int a_index, string a_name ):BaseScene( a_index, a_name ) {}
    ~EmptyScene();
    
    void setup();
    void setupGui(float a_x=0, float a_y=0);
 
    void update();
    void draw();
    
    void activate();
    void deactivate();

};
