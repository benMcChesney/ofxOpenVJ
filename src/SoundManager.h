//
//  SoundManager.h
//  scenePlayground
//
//  Created by Ben McChesney on 9/7/14.
//
//

#ifndef __scenePlayground__SoundManager__
#define __scenePlayground__SoundManager__

#include "ofMain.h"
#include "ofxBeatDetector.h"
#include "ofxUI.h"


class SoundManager
{
    public :
    SoundManager() { }
    ~SoundManager() { }

    
    void setup ( ) ;
    void setupGui( ofxUICanvas * gui ) ;
    void guiEvent( ofxUIEventArgs& e );
    
    void update( ) ;
    void draw ( ) ;
    void audioReceived(float* input, int bufferSize, int nChannels);
    
    ofxBeatDetector beatDetector ;
    
    ofxUICanvas * gui ;
    
    float beatValueDecay ;
    float low ; 

};


#endif /* defined(__scenePlayground__SoundManager__) */
