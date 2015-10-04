//
//  ofxOpenVJConstants.h
//  KinectPerformanceV01
//
//  Created by Ben McChesney on 6/1/2014
//
//
#include "ofMain.h"
#pragma once

/*
 comment out this preprocessor if you don't have a kinect handy or aren't planning on using one
*/

//#define USE_KINECT 3
//#define USE_KINECT_V2 3
#define USE_SPOUT 4

class ofxOpenVJConstants {
public:

	ofxOpenVJConstants()
	{
		GUI_WIDGET_WIDTH = 300; 
		GUI_WIDGET_HEIGHT = 45; 
		GUI_WIDGET_BG_COLOR = ofColor(15, 15, 15, 128); 
	}

	static ofxOpenVJConstants* Instance()
	{
		static ofxOpenVJConstants inst;
		return &inst;
	}

	float GUI_WIDGET_WIDTH; 
	float GUI_WIDGET_HEIGHT; 
	ofColor GUI_WIDGET_BG_COLOR; 
    
};




