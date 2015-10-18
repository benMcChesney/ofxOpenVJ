//
//  SoundManager.h
//  scenePlayground
//
//  Created by Ben McChesney on 9/7/14.
//
//

#ifndef __scenePlayground__SoundManager__
#define __scenePlayground__SoundManager__


#include "ofxBeat.h"
#include "ofMain.h"
#include "ofxGui.h"
#include "MSABPMTapper.h"
#include "ofxMidi.h"


class SoundManager 
{
    public :
    SoundManager() { }
    ~SoundManager() { }
    
    void setup ( int bufferSize ) ;
    
    void update( ) ;
    void draw ( ) ;
    void audioReceived(float* input, int bufferSize, int nChannels);
	void midiMessageRecieved(ofxMidiMessage& msg);

	ofxBeat beatTracker ;
	void drawFFTBands(float x, float y, float width, float height);

    ofxPanel gui ;
	bool bDrawGui; 
    
    float beatValueDecay ;
    float low ; 
	int bufferSize; 

	//BPM
	msa::BPMTapper  bpmTapper;

	void tapBPM(); 
	void clearBPM(); 

	ofxFloatSlider beatPerc; 
	float lastBeatPerc; 


	ofxButton beat; 
	ofxButton button_tapBPM; 
	ofxButton button_clearBPM; 
	ofxLabel bpmLabel; 
};


#endif /* defined(__scenePlayground__SoundManager__) */
