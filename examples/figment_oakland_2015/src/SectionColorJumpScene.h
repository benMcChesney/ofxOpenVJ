//
//  SimpleScene.h
//  simpleExample
//
//  Created by Ben McChesney on 5/15/14.
//
//

#pragma once

#include "BaseScene.h"



class SectionColorJumpScene : public BaseScene
{
public :
	SectionColorJumpScene() {}
	SectionColorJumpScene( int a_index, string a_name ):BaseScene( a_index, a_name ) {}

    void setup();
    void setupGui(float a_x=0, float a_y=0);
//    void guiEvent(ofxUIEventArgs &e);
    
    void update();
    void draw();
	void drawDebug(); 
    
    void activate();
    void deactivate();
    
    bool transitionIn( float delay , float transitionTime );
    bool transitionOut( float delay , float transitionTime ) ;
	void newBeatHandler(); 
	void drawHorizontalBars( ofRectangle r ); 
	void drawVerticalBars(ofRectangle r);

	ofxIntSlider numSegments ; 
	ofxToggle bStep; 
	ofxToggle bSequence;
	ofxToggle bHorizontal; 

	ofxFloatSlider hueSequenceStep; 
	ofxFloatSlider segmentColorHue;
	ofxFloatSlider segmentColorBrightness; 
	ofxFloatSlider segmentColorSaturation;
	ofColor segmentColor; 
	int curSegment; 

	ofColor curColor; 
	ofxIntSlider angleStep; 
	float curAngle; 
	ofxButton resetAngle; 
	void resetAngleListener(); 


    


    
};
