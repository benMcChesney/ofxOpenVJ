//
//  SoundManager.cpp
//  scenePlayground
//
//  Created by Ben McChesney on 9/7/14.
//
//
#include "SoundManager.h"


void SoundManager::setup ( int _bufferSize )
{
	bufferSize = _bufferSize; 
}

void SoundManager::update( )
{
	beatTracker.updateFFT(); 

    if ( low > 0.0f )
        low -= beatValueDecay ;

	/*

	((ofxUIToggle*)gui->getWidget("KICK"))->setValue(beatTracker.isKick()); 
	((ofxUIToggle*)gui->getWidget("SNARE"))->setValue(beatTracker.isSnare()); 
	((ofxUIToggle*)gui->getWidget("HAT"))->setValue(beatTracker.isHat()); 

  */
}



void SoundManager::draw ( )
{
	char str[32];

	// ????FFT??? bd.magnitude[i] ?????????????
	// ????????FFT?bd.magnitude[i]??????????FFT?????

	// ??FFT????? (1??)
	ofSetColor(155, 155, 75);
	for (int i = 1; i < (int)bufferSize / 2; i++) {
		if (i % 16 == 0) {
			ofSetColor(200, 0, 0);
		}
		else {
			ofSetColor(155, 155, 75);
		}
		ofLine(10 + (i * 3), 150, 10 + (i * 3), 150 - beatTracker.magnitude[i] * 10.0f);
		//printf("%f \n", magnitude_average[i]);
	}
	// ???????????2??
	for (int i = (int)512 / 2, b = 1; i<bufferSize; i++) {
		if (i % 16 == 0) {
			ofSetColor(200, 0, 0);
		}
		else {
			ofSetColor(155, 155, 75);
		}
		ofLine(10 + (b * 3), 300, 10 + (b * 3), 300 - beatTracker.magnitude[i] * 10.0f);
		b++;
		//printf("%f \n", magnitude_average[i]);
	}


	// ??????FFT????? (1??)
	ofSetColor(134, 113, 89);
	for (int i = 1; i < (int)bufferSize / 2; i++) {
		if (i % 16 == 0) {
			ofSetColor(200, 0, 0);
		}
		else {
			ofSetColor(134, 113, 89);
		}
		ofLine(10 + (i * 3), 500, 10 + (i * 3), 500 - beatTracker.magnitude_average[i] * 10.0f);
	}
	// ???????????2?
	for (int i = (int)bufferSize / 2, b = 1; i<bufferSize; i++) {
		if (i % 16 == 0) {
			ofSetColor(200, 0, 0);
		}
		else {
			ofSetColor(134, 113, 89);
		}
		ofLine(10 + (b * 3), 650, 10 + (b * 3), 650 - beatTracker.magnitude_average[i] * 10.0f);
		b++;
	}

	//ofSetColor(200,200,200);
	//for (int i = 1; i < (int)testApp_fft_size/2; i++){
	//    //ofLine(200+(i*4),200,200+(i*4),400-magnitude[i]*10.0f);
	//    //ofLine(10+(i*5.3),400,  10+(i*5.3),400-magnitude[i]*10.0f);
	//    sprintf(str, "%.0f", magnitude[i]);
	//    fbook.drawString(str,5+(i*7), 270);
	//    fbook.drawString(str,10+(i*5.3),250-magnitude[i]*10.0f);
	//}

	// ???????
	/*
	if (drumVisible) {
		if (bd.isBeatRange(0, 2, 2)) {
			ofSetColor(255, 0, 0);
			fbook.drawString("DRUM!!", 100, 735);
		}
		else {
			ofSetColor(0, 255, 0);
			ofRect(100, 700, 200, 50);
		}
	}

	// ???????
	if (snareVisible) {
		if (bd.isBeatRange(12, 18, 4)) {
			ofSetColor(255, 0, 0);
			fbook.drawString("SNARE!!", 350, 735);
		}
		else {
			ofSetColor(0, 255, 0);
			ofRect(350, 700, 200, 50);
		}
	}

	// ?????????
	if (hihatVisible) {
		if (bd.isBeatRange(27, 31, 3)) {
			ofSetColor(255, 0, 0);
			fbook.drawString("HiHat!!", 600, 735);
		}
		else {
			ofSetColor(0, 255, 0);
			ofRect(600, 700, 200, 50);
		}
	}*/
}

void SoundManager::audioReceived(float* input, int bufferSize, int nChannels)
{
	beatTracker.audioReceived(input, bufferSize);
}

void SoundManager::setupGui( ofxUICanvas * _gui )
{
    gui = _gui ;
    gui->addSpacer() ;
    gui->addLabel( "SOUND PARAMS" ) ;
    

	gui->addSpectrum("FFT", beatTracker.magnitude_average , 32 ); 
    
    gui->addSlider( "BEAT DECAY", 0.0f , 0.1f , &beatValueDecay ) ;
    gui->addToggle( "KICK" , false ) ;
    gui->addToggle( "SNARE" , false ) ;
    gui->addToggle( "HAT" , false ) ;
    
   ofAddListener( gui->newGUIEvent, this, &SoundManager::guiEvent );
}

void SoundManager::guiEvent( ofxUIEventArgs& e )
{
    

}
