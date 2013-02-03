//
//  FftTrigger.cpp
//  emptyExample
//
//  Created by Ben McChesney on 10/30/12.
//
//

#include "FftTrigger.h"

void FftTrigger::setup ( float _lowBand , float _highBand )
{
    
    updateBands( _lowBand, _highBand ) ; 
    color = ofColor( ofRandom ( 255 ) , ofRandom( 255 ) , ofRandom( 255 ) ) ;
    
    lastTriggerTime = ofGetElapsedTimef() ;
    minTriggerDelay = 0.1f ;
    //minFreq = 0.2f ;
    maxFreq = 1.0f ;
   
}

void FftTrigger::update( )
{
    if( hit == true )
    {
        if( sent == true )
        {
            hit = false;
            sent = false;
        }
        
        color = ofColor(255,0,0);
    }
    else
        color = ofColor(255,255,0);
}
void FftTrigger::draw( )
{
    ofPushStyle() ;
        ofNoFill( ) ;
    
       // if ( hit == true )
       //     ofSetColor( 255 , 0 , 0 ) ; //255 - color.r , 255 - color.g , 255 - color.b ) ;
       // else
       //     ofSetColor( 0 , 255 , 0 ) ; //color ) ;
        ofSetColor( color ) ; 
        updateBands( ) ;
        ofRect( bounds ) ;
        ofDrawBitmapString( name , bounds.x +5 , bounds.y + 10 ) ;
        ofSetColor ( 255 , 255 , 255 ) ; 
        ofDrawBitmapString( ofToString( averageAmplitude ) , bounds.x +5 , bounds.y -15 ) ;
    
        ofSetColor( 255 , 0 , 0 ) ;

        //ofGetHeight() - 16 - height * 512 - 15 ,
        float _y = ( ofGetHeight() - 16 ) + ( minTriggerDelay * -512 ) ;
        ofSetLineWidth( 5 ) ;
        //ofLine ( bounds.x , _y , bounds.x + bounds.width, _y ) ;
        
        
        _y = ofGetHeight() - 16 - maxFreq * 512  ;
        ofSetColor( 255 , 0 , 255 ) ;
        ofLine ( bounds.x , _y , bounds.x + bounds.width, _y ) ;
    
        ofFill( ) ; 
        ofSetColor( 0 , 255 , 0 , 90 ) ;
        ofRect ( bounds.x , ofGetHeight() - 16 , bounds.width , averageAmplitude * -512 ) ;
    
    ofPopStyle() ;
}

bool FftTrigger::trigger( )
{
    if ( ofGetElapsedTimef() > ( lastTriggerTime + minTriggerDelay ))
    {
        //cout << "TRIGGER SHOULD BE ON! " << ofGetElapsedTimef() << endl ;
        lastTriggerTime = ofGetElapsedTimef() ;
        hit = true ; 
        return true ;
    }
    else
    {
        return false ;
    }
}

bool FftTrigger::hitTest( float x , float y )
{
    if ( (x > bounds.x && x < ( bounds.x + bounds.width )) && ( y > bounds.y && y < ( bounds.y + bounds.height )) ) 
        return true ;
    else
        return false ;
}

bool FftTrigger::hitTestX( float x  )
{
    if ( (x > bounds.x && x < ( bounds.x + bounds.width )) ) 
        return true ;
    else
        return false ;
}

int FftTrigger::aboveOrBelow( float y )
{
    cout << "FftTrigger::aboveOrBelow : y " << bounds.y<< " ? " << y << endl ; 
    if ( y < bounds.y )
        return -1 ;
    if ( y > bounds.y )
        return 1 ;
}

void FftTrigger::updateBands( )
{
    bounds = ofRectangle( lowBand*4 ,
                         ofGetHeight() - 16 - height * 512 - 15 ,
                         ( highBand*4 ) - ( lowBand*4 )  ,
                         15) ;
}

void FftTrigger::updateBands( float _lowBand, float _highBand )
{
    lowBand = _lowBand ;
    highBand = _highBand ;
    updateBands() ; 
}
