//
//  CompositorManager.h
//  scenePlayground
//
//  Created by Ben McChesney on 10/4/2015
//
//

#pragma once

#include "ofMain.h"
#include "ofxGui.h"

class CompositorManager
{
    public :
	CompositorManager() { }
	~CompositorManager() { }

    void setup (  ) ;
    void setupGui( ) ;
    //void guiEvent( ofxUIEventArgs& e );
    
    void update( ) ;
	void drawScene( ofFbo * fbo , ofColor clearColor ); 

    ofxPanel gui ;
	bool bDrawGui; 

	ofxColorSlider channels;


};
