#pragma once

#include "ofMain.h"
#include "ofxSvg.h"

class AnimatedIcon
{
public : 
	AnimatedIcon() { }
	~AnimatedIcon( ) { } 

	void setup(string _path, float _lineWidth , ofFloatColor c = ofColor::white );
	void draw( );
	void drawStroke ( ) ; 

	ofFloatColor color ; 
	ofxSVG svg;
    string filePath ; 
	float completion;
	float lineWidth;
	vector<ofPolyline>polylines;
    
    void clear() ; 
};