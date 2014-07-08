//
//  ofxOpenVJEvents.h
//  simpleExample
//
//  Created by Ben McChesney on 6/28/14.
//
//

#ifndef simpleExample_ofxOpenVJEvents_h
#define simpleExample_ofxOpenVJEvents_h

#include "ofMain.h"

class ofxOpenVJEventArgs
{
    public :
    
    ofxOpenVJEventArgs( ) { }
    ofxOpenVJEventArgs( string _name )
    {
        name = _name ;
    }
    
    string name ;
};

class ofxOpenVJEvents
{
    public :
    
    static ofxOpenVJEvents* Instance()
    {
        static ofxOpenVJEvents inst;
        return &inst;
    }
    
    ofEvent< ofxOpenVJEventArgs > SCENE_TRANSITION_IN_COMPLETE ;
    ofEvent< ofxOpenVJEventArgs > SCENE_TRANSITION_OUT_COMPLETE ;
};

#endif
