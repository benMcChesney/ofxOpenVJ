//
//  SoundManager.cpp
//  scenePlayground
//
//  Created by Ben McChesney on 9/7/14.
//
//
#include "SoundManager.h"
#include "ofxOpenVJConstants.h"



void SoundManager::setup ( int _bufferSize )
{
	bufferSize = _bufferSize; 

	ofxOpenVJConstants * c = ofxOpenVJConstants::Instance(); 
	gui.setDefaultWidth(c->GUI_WIDGET_WIDTH); 
	gui.setDefaultHeight(c->GUI_WIDGET_HEIGHT); 
	gui.setup("SOUND MANAGER PANEL", "GUI/soundManagerGui.xml", c->GUI_WIDGET_WIDTH * 4, 0); 

	gui.add(beatPerc.setup("BEAT %", 0.0f , 1.0f , 1.0f )); 
	gui.add(beat.setup("BEAT ?", false)); 
	gui.add(button_tapBPM.setup("TAP", false)); 
	gui.add(button_clearBPM.setup("RESET BPM")); 
	gui.add(bpmLabel.setup("BPM", "NONE" )); 

	button_tapBPM.addListener(this, &SoundManager::tapBPM);
	button_clearBPM.addListener(this, &SoundManager::clearBPM);
}

void SoundManager::tapBPM()
{
	bpmTapper.tap(); 
	cout << "BPM TAP ! " << endl; 
}

void SoundManager::clearBPM()
{
	bpmTapper.startFresh(); 
	cout << "BPM CLEAR ! " << endl;
}

void SoundManager::update( )
{
	beatTracker.update(ofGetElapsedTimeMillis());
	bpmTapper.update();
	beatPerc = bpmTapper.beatPerc(); 
	//bpmLabel.set = ofToString( bpmTapper.bpm() ) ; 
}

void SoundManager::drawFFTBands(float x, float y, float width, float height)
{
	ofPushMatrix();

	//HighHat / Snare / Kick + Space 
	float widthPerBand = width / ((float)(FFT_SUBBANDS + 4.0));

	ofEnableAlphaBlending();
	ofSetColor(255, 215);
	ofNoFill();
	ofSetLineWidth(2);
	ofRect(x, y, width, height);
	ofFill();
	ofSetLineWidth(1);

	int totalBands = (FFT_SUBBANDS + 4);

	int h = -height / 2.0f;
	//ofTranslate(0, height ); 
	for (int i = 0; i < FFT_SUBBANDS; i++)
	{

		ofRect(x + (i * widthPerBand), y + height, widthPerBand, beatTracker.getBand(i) *h);
	}

	ofSetColor(255, 0, 0, 215);
	ofRect(x + ((FFT_SUBBANDS + 1)* widthPerBand), y + height, widthPerBand, beatTracker.isKick() * h);
	ofDrawBitmapStringHighlight("K", x + (FFT_SUBBANDS + 1) * widthPerBand, y + height + 1);

	ofSetColor(0, 255, 0, 215);
	ofRect(x + ((FFT_SUBBANDS + 2) * widthPerBand), y + height, widthPerBand, beatTracker.isSnare() * h);
	ofDrawBitmapStringHighlight("S", x + (FFT_SUBBANDS + 2) * widthPerBand, y + height + 1);

	ofSetColor(0, 0, 255, 215);
	ofRect(x + ((FFT_SUBBANDS + 3) * widthPerBand), y + height, widthPerBand, beatTracker.isHat() * h);
	ofDrawBitmapStringHighlight("H", x + (FFT_SUBBANDS + 3) * widthPerBand, y + height + 1);

	ofPopMatrix();
}

void SoundManager::midiMessageRecieved(ofxMidiMessage& msg)
{
	if (msg.status == MIDI_NOTE_ON)
	{
		if (msg.pitch == 37)
		{
			tapBPM(); 
		}
		else if (msg.pitch == 36)
		{
			clearBPM(); 
		}
	}
}


void SoundManager::draw ( )
{
	
}

void SoundManager::audioReceived(float* input, int bufferSize, int nChannels)
{
	beatTracker.audioReceived(input, bufferSize, nChannels);
}
