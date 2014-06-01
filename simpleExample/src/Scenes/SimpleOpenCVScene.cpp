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
void SimpleOpenCVScene::activate() {
    
}

//--------------------------------------------------------------
void SimpleOpenCVScene::deactivate() {
    
    // turn off the gui //
    BaseScene::deactivate();
}

//--------------------------------------------------------------
void SimpleOpenCVScene::update() {
    kinectMan->update( );
    kinectMan->calculateCVOperations() ;
    
    ofxCvContourFinder * c = &kinectMan->contourFinder ;
    if ( c->nBlobs > 0 )
    {
        paths.clear() ;
        
        //c++ 11 has some cool new looping tricks like the auto iterator
        for( auto blob = c->blobs.begin() ; blob != c->blobs.end() ; blob++ )
        {
            //Polyline are good for smoothing / resampling CV blobs
            ofPolyline line ;
            for ( auto pt = (*blob).pts.begin() ; pt != (*blob).pts.end() ; pt++ )
            {
                //Transform the CV points from pixel space to screenspace
                line.addVertex( kinectMan->cvPointToScreen( (*pt) , ofGetWidth() , ofGetHeight() ) );  
            }
           
            
            line = line.getSmoothed( outlineSmoothing ) ;
            
            //Paths are good for storing more complex shapes , colors, and fills
            int index = paths.size() ;
            paths.push_back( ofPath() ) ;
            paths[ index ].moveTo( line.getVertices()[0] ) ;
            
            for ( auto pt = line.getVertices().begin() ; pt != line.getVertices().end() ; pt++ )
            {
                paths[ index ].lineTo( (*pt) ) ; 
            }
            
            paths[ index ].close() ;
            paths[ index ].setFilled( true ) ;
            float normalized = (float)index / ( (float)( c->nBlobs ) ) ;
            ofColor pathFill = ofColor::fromHsb( normalized * 255.0f , 255 , 255 ) ;
            paths[ index ].setFillColor( pathFill ) ; 
        }
    }
}

//--------------------------------------------------------------
void SimpleOpenCVScene::draw() {

    ofSetColor( 255 , 255 ,255 ) ;
  
    ofPushMatrix() ;
    for ( auto path = paths.begin() ; path != paths.end() ; path++ )
    {
        (*path).draw( 0 , 0 )  ;
    }
    
    ofPopMatrix();
}
