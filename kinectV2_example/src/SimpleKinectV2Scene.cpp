//
//  TestScene.cpp
//  KinectPerformanceV01
//
//  Created by Ben McChesney on 11/6/12.
//
//

#include "SimpleKinectV2Scene.h"

//--------------------------------------------------------------
SimpleKinectV2Scene::SimpleKinectV2Scene() {
    
}

//--------------------------------------------------------------
SimpleKinectV2Scene::~SimpleKinectV2Scene() {
    
}

//--------------------------------------------------------------
void SimpleKinectV2Scene::setup() {

}

//--------------------------------------------------------------
void SimpleKinectV2Scene::setupGui(float a_x, float a_y) {
    // creates new gui and adds the name to it //
    BaseScene::setupGui(a_x, a_y);
    
    //gui->addSlider( "OUTLINE SMOOTHING", 1, 35 , &outlineSmoothing ) ;

    ofAddListener( gui->newGUIEvent, this, &SimpleKinectV2Scene::guiEvent );
    loadSettings() ; 
}

//--------------------------------------------------------------
void SimpleKinectV2Scene::guiEvent(ofxUIEventArgs &e) {
    
    BaseScene::guiEvent( e ) ; 

 }

//--------------------------------------------------------------
void SimpleKinectV2Scene::activate() {
    
}

//--------------------------------------------------------------
void SimpleKinectV2Scene::deactivate() {
    
    // turn off the gui //
    BaseScene::deactivate();
}

//--------------------------------------------------------------
void SimpleKinectV2Scene::update() {
    depthCameraManager->update();
	//depthCameraManager->calculateCVOperations() ; 
	
	
	/*
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
    }*/
}

//--------------------------------------------------------------
void SimpleKinectV2Scene::draw() {

	
	ofxKinectCommonBridge * kinect =  &((KinectV2Manager*)depthCameraManager)->kinect ;

    ofSetColor( 255 , 255 ,255 ) ;
  
    ofPushMatrix() ;
    //((KinectV2Manager*)depthCameraManager)->draw( );

	//((KinectV2Manager*)depthCameraManager)->kinect.draw( 0 , 0 ) ; 
	kinect->drawDepth( 0 , 0 ) ; 
	kinect->drawRawDepth( 0 , kinect->getDepthTexture().getHeight() , kinect->getDepthTexture().getWidth() , kinect->getDepthTexture().getHeight() ) ; 


	//kinect->drawIR( 0 , kinect->getDepthTexture().getHeight(), kinect->getDepthTexture().getWidth() , kinect->getDepthTexture().getHeight() ) 
	/*
	int w = ((KinectV2Manager*)depthCameraManager)->kinect.getDepthTexture().getWidth() ; 
	int h = ((KinectV2Manager*)depthCameraManager)->kinect.getDepthTexture().getHeight() ;
	int totalPixels =  kinect->depthLookupTable.size()   ;
	unsigned char * pixels = new unsigned char [ totalPixels ] ;  
	 
	for ( int i = 0 ; i < totalPixels ; i++ ) 
	{
		pixels[i] =  kinect->depthLookupTable[ i ] ; 
	}

	((KinectV2Manager*)depthCameraManager)->grayImage.setFromPixels( pixels , w , h ) ; 
	((KinectV2Manager*)depthCameraManager)->grayImage.draw( 0 , 0 ) ; */
	//pix.setFromPixels( ((KinectV2Manager*)depthCameraManager)->kinect.depthLookupTable ,
		//gui->addWidgetRight( new ofxUIBaseDraws(128, 96, ((ofxCvGrayscaleImage*) &grayImage), "Open CV Texture") );
    ofPopMatrix();
}
