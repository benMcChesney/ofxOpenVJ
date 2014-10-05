//
//  NexusLine.h
//  Zeitgeist_2014
//
//  Created by Ben McChesney on 9/14/14.
//
//

#ifndef Zeitgeist_2014_NexusLine_h
#define Zeitgeist_2014_NexusLine_h

#include "ofMain.h"
#include "Tweenzor.h"

class NexusLine
{
    public :
    NexusLine()
    {
        percent = 0.0f ;
        color = ofColor::white  ;
        tweenTime = 4.0f;
    }
    ~NexusLine() { }
    
    float percent ;
    ofPath line ;
    ofColor color ;
    float strokeWidth ;
    
    ofPoint origin , destination ;
    
    float tweenTime ;

    
    void setup ( ofColor _color  , float _tweenTime )
    {
        color = _color ;
        tweenTime = _tweenTime ;
        strokeWidth = ofRandom( 2 , 9 ) ;
    }
    
    
    void start( float startY , bool bFromRight )
    {
        line.clear() ;
        float dstX = ofRandom( 5 , 65 ) ;
        float randomStartX = ofRandom( -5 , -65 ) ;
        
        float offsetPerc = ofRandom( 0.05 , .95 ) ;
        if ( bFromRight == true )
        {
            origin = ofPoint ( randomStartX , startY ) ;
            destination = origin ;
            dstX += ofGetWidth() ;
            Tweenzor::add( &destination.x , origin.x , dstX , 0.0f , tweenTime , EASE_IN_OUT_QUAD ) ;
            Tweenzor::add( &origin.x , origin.x , dstX ,  tweenTime * offsetPerc  , tweenTime , EASE_IN_OUT_QUAD ) ;
      
        }
        else
        {
            origin = ofPoint ( ofGetWidth() + randomStartX , startY ) ;
            destination = origin ;
            dstX -= 100 ;
            Tweenzor::add( &destination.x , origin.x , dstX , 0.0f , tweenTime , EASE_IN_OUT_QUAD ) ;
            Tweenzor::add( &origin.x , origin.x , dstX ,  tweenTime * offsetPerc , tweenTime , EASE_IN_OUT_QUAD ) ;
        }
    }
    
    
    void draw ( )
    {
        line.clear() ;
        line.moveTo( origin ) ;
        line.lineTo( destination ) ;
        line.setStrokeWidth( strokeWidth ) ;
        line.setStrokeColor( color ) ;
        line.draw( ) ;
    }
    
    
};

#endif
