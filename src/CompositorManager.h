//
//  CompositorManager.h
//  scenePlayground
//
//  Created by Ben McChesney on 10/4/2015
//
//

#pragma once

#include "ofMain.h"
#include "ofxPostGlitch.h"
#include "ofxGui.h"
#include "ofxMidi.h"

class GlitchGuiMap
{
public:
	GlitchGuiMap(string _label, ofxPostGlitchType _type , int _midiPitch = -1 )
	{
		label = _label;
		type = _type;
		toggle.setup(label, false);
		midiPitch = _midiPitch; 
	}

	ofxToggle toggle;
	string label;
	ofxPostGlitchType type;
	int midiPitch; 
};

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
	void beginDraw(); 
	void endDraw(); 

	void midiMessageRecieved(ofxMidiMessage& msg); 

    ofxPanel gui ;
	bool bDrawGui; 

	ofxColorSlider channels;

	ofxPostGlitch glitch  ; 
	ofFbo fbo; 

	vector< GlitchGuiMap * > glitches;

};
