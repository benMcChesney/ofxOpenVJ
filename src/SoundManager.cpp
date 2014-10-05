//
//  SoundManager.cpp
//  scenePlayground
//
//  Created by Ben McChesney on 9/7/14.
//
//
#include "SoundManager.h"


void SoundManager::setup ( )
{
    beatDetector.enableBeatDetect() ;
}

void SoundManager::update( )
{
    if ( low > 0.0f )
        low -= beatValueDecay ;
    
    if ( beatDetector.isLow() )
        low = 1.0f ;

}

void SoundManager::draw ( )
{
    
}

void SoundManager::audioReceived(float* input, int bufferSize, int nChannels)
{
    beatDetector.update( input ) ;
}

void SoundManager::setupGui( ofxUICanvas * _gui )
{
    gui = _gui ;
    gui->addSpacer() ;
    gui->addLabel( "SOUND PARAMS" ) ;
    
    
    gui->addSpectrum("FFT" , beatDetector.getSmoothedFFT() , 32 ) ;
    
    gui->addSlider( "BEAT DECAY", 0.0f , 0.1f , &beatValueDecay ) ;
    gui->addToggle( "KICK" , false ) ;
    gui->addToggle( "SNARE" , false ) ;
    gui->addToggle( "HAT" , false ) ;
    
   ofAddListener( gui->newGUIEvent, this, &SoundManager::guiEvent );
}

void SoundManager::guiEvent( ofxUIEventArgs& e )
{
    

}
