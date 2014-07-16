//
//  TestScene.cpp
//  KinectPerformanceV01
//
//  Created by Ben McChesney on 11/6/12.
//
//

#include "SimpleOpenCVScene.h"

//--------------------------------------------------------------
SimpleOpenCVScene::SimpleOpenCVScene() {
    
}

//--------------------------------------------------------------
SimpleOpenCVScene::~SimpleOpenCVScene() {
    
}

//--------------------------------------------------------------
void SimpleOpenCVScene::setup() {
    
}

//--------------------------------------------------------------
void SimpleOpenCVScene::setupGui(float a_x, float a_y) {
    // creates new gui and adds the name to it //
    BaseScene::setupGui(a_x, a_y);
    
    gui->addSlider( "OUTLINE SMOOTHING", 1, 35 , &outlineSmoothing ) ;

    ofAddListener( gui->newGUIEvent, this, &SimpleOpenCVScene::guiEvent );
    loadSettings() ; 
}

//--------------------------------------------------------------
void SimpleOpenCVScene::guiEvent(ofxUIEventArgs &e) {
    
    BaseScene::guiEvent( e ) ; 

 }

//--------------------------------------------------------------
void SimpleOpenCVScene::update()
{
    BaseScene::update( ) ; 
    depthCameraManager->update( );
    depthCameraManager->calculateCVOperations() ;
    
    //Set the values to very high so it's overriden easily
    boundingBox = ofRectangle( 40000 , 40000 , 0 , 0 ) ;
    ofxCvContourFinder * c = &depthCameraManager->contourFinder ;
    if ( c->nBlobs > 0 )
    {
        paths.clear() ;
        
        //c++ 11 has some cool new looping tricks like the auto iterator
        for( auto blob = c->blobs.begin() ; blob != c->blobs.end() ; blob++ )
        {
            //Polyline are good for smoothing / resampling CV blobs
            ofPolyline line ;
            
            float nPoint = 0.0f ;
            float nPointInc = 1.0f / ( float ) (*blob).pts.size() ;
            
            for ( auto pt = (*blob).pts.begin() ; pt != (*blob).pts.end() ; pt++ )
            {
                if ( nPoint < completion )
                {
                    //Transform the CV points from pixel space to screenspace
                    line.addVertex( depthCameraManager->cvPointToScreen( (*pt) , ofGetWidth() , ofGetHeight() ) );
                    nPoint += nPointInc ;
                }
            }
           
            
            line = line.getSmoothed( outlineSmoothing ) ;
            
            //Paths are good for storing more complex shapes , colors, and fills
            int index = paths.size() ;
            paths.push_back( ofPath() ) ;
            if ( line.getVertices().size() > 0 )
            {
                paths[ index ].moveTo( line.getVertices()[0] ) ;
            
                for ( auto pt = line.getVertices().begin() ; pt != line.getVertices().end() ; pt++ )
                {
                    paths[ index ].lineTo( (*pt) ) ; 
                }
            }
            
            paths[ index ].close() ;
            
            //if ( completion == 1.0f )
            paths[ index ].setFilled( true ) ;
            float normalized = (float)index / ( (float)( c->nBlobs ) ) ;
            ofColor pathFill = ofColor::fromHsb( normalized * 255.0f , 255 , 255 ) ;
            paths[ index ].setFillColor( pathFill ) ;
            
            ofRectangle bb = line.getBoundingBox() ;
            if ( bb.x < boundingBox.x ) boundingBox.x = bb.x ;
            if ( bb.y > boundingBox.y ) boundingBox.y = bb.y ;
            if ( bb.width > boundingBox.width ) boundingBox.width = bb.width ;
            if ( bb.height > boundingBox.height ) boundingBox.height = bb.height ;
            
        }
    }
}

//--------------------------------------------------------------
void SimpleOpenCVScene::draw() {

    ofSetColor( 255 , 255 ,255 ) ;
  
    ofPushMatrix() ;
    for ( auto path = paths.begin() ; path != paths.end() ; path++ )
    {
        //ofTranslate( boundingBox.width / 2 , boundingBox.height / 2 ) ;
        //ofScale( scale , scale ) ;
        //ofTranslate( (*path). * 0.5 , (*path).getHeight() * 0.5  ) ;  
        (*path).draw( 0 , 0 )  ;
        
    }
    
    ofPopMatrix();
}


bool SimpleOpenCVScene::transitionIn( float delay , float transitionTime )
{
    if ( BaseScene::transitionIn( delay , transitionTime ) == false )
        return false ;
    else
    {
        completion = 0.0f; 
        Tweenzor::add( &completion , completion , 3.0f , delay , transitionTime ) ;
    }
    
    return true ;
}

bool SimpleOpenCVScene::transitionOut( float delay , float transitionTime )
{
    if ( BaseScene::transitionOut( delay , transitionTime ) == false )
        return false ;
    else
    {
        Tweenzor::add( &completion , completion , 0.0f , delay , transitionTime ) ;
    }
    return true ;
}

