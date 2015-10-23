//
//  SimpleScene.h
//  simpleExample
//
//  Created by Ben McChesney on 5/15/14.
//
//

#pragma once

#include "BaseScene.h"
#include "ofxSimpleMask.h"

class TileSquare
{
public : 
	TileSquare( ofColor c , float _w , float _x ) 
	{
		color = c; 
		width = _w;
		offset = _x; 
	} 

	ofColor color; 
	float width; 
	float offset; 
};

class ReflectMaskScene : public BaseScene
{
public :
	ReflectMaskScene() {} 
	ReflectMaskScene(int a_index, string a_name, string folder) :BaseScene(a_index, a_name) { loadContentFromDir(folder); }
   
    struct ColorSquare
    {
        ofPoint position  ;
        ofColor color = ofColor::gray ;
        float size = 50.0f ;
    };

	void loadContentFromDir(string path); 
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
    
	ofDirectory dir;
	vector< ofImage > loadedImages;
	int activeIndex;

	ofxFloatSlider rectWidthSlider;
	float drawOffset; 

	float lastBeatPerc; 
	bool bFirstWhite; 

	vector < TileSquare*> squares; 

	ofxSimpleMask mask; 
	ofFbo maskFbo; 

	ofxButton nextImage; 
	ofxButton prevImage; 

	void nextImageHandler(); 
	void prevImageHandler(); 
	void offsetImageByIndex(int index);



    
};
