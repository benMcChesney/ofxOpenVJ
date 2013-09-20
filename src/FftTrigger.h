//
//  FftTrigger.h
//  emptyExample
//
//  Created by Ben McChesney on 10/30/12.
//
//
#include "ofMain.h"

#ifndef emptyExample_FftTrigger_h
#define emptyExample_FftTrigger_h

class FftTrigger
{
    public :
        FftTrigger( ) { } 
        ~FftTrigger ( ) { }
    
        void setup ( float lowBand , float highBand ) ;
        void update ( ) ; 
        void draw( ) ;
        bool hitTest( float x , float y ) ;
        bool hitTestX( float x  ) ; 
        int aboveOrBelow( float y ) ;
    
        ofRectangle bounds ;
        float value ;
        ofColor color ;
    
        float lowBand;
        float highBand;
        float height;
        string name;
	
        bool hit;
        bool sent;

        void updateBands() ; 
        void updateBands( float lowBand, float highBand ) ;
    
        float lastTriggerTime ;
        float minTriggerDelay ;
        bool trigger() ;
    
        float averageAmplitude ; 
        //float minFreq ;
        float maxFreq ; 
    
};

#endif
