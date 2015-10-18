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

class FftRadialShape
{
public : 
	FftRadialShape() { } 
	FftRadialShape(ofColor _color, ofPolyline _shape, float _rotation, float _scale)
	{
		color = _color;
		shape = _shape; 
		rotation = _rotation;
		scale = _scale; 
	}
	~FftRadialShape() {} 

	void firstTween(float tRotation, float tScale, float duration, float delay)
	{
		//Tweenzor::add( &)
	}
	void firstTweenComplete(float * args)
	{

	}
	void secondTweenComplete(float * args)
	{

	}

	ofColor color; 
	ofPolyline shape ; 
	float rotation; 
	float scale; 

};

class RadialFftScene : public BaseScene {
public:
	RadialFftScene();
	RadialFftScene( int a_index, string a_name ):BaseScene( a_index, a_name ) {}
    ~RadialFftScene();
    
    void setup();
    void setupGui(float a_x=0, float a_y=0);
 
    void update();
    void draw();
	void drawDebug();

    void activate();
	void deactivate();

	bool transitionIn(float delay, float transitionTime);
	bool transitionOut(float delay, float transitionTime);

	void newBeatHandler();

	vector < FftRadialShape * > shapes;

	ofxFloatSlider maxRadius; 
	ofxFloatSlider minRadius; 
	ofxFloatSlider smoothedAmount; 
	ofxIntSlider resampledAmount; 
};
