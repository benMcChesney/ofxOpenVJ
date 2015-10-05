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
#include "ofxGui.h"

class ReflectMaskScene: public BaseScene {
public:
	ReflectMaskScene();
	ReflectMaskScene( int a_index, string a_name ):BaseScene( a_index, a_name ) {}
    ~ReflectMaskScene();
    
    void setup();
    void setupGui(float a_x=0, float a_y=0);
 
    void update();
    void draw();
	void drawDebug();

    void activate();
	void deactivate();

	bool transitionIn(float delay, float transitionTime);
	bool transitionOut(float delay, float transitionTime);

	ofDirectory dir; 

	vector< ofImage > loadedImages; 

	int activeIndex; 

	ofxFloatSlider rectWidthSlider ; 


};
