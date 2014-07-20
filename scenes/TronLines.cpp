//
//  PCSDK_TronLines.cpp
//  KinectPerformanceV01
//
//  Created by Ben McChesney on 7/25/2013.
//
//

#include "TronLines.h"
//--------------------------------------------------------------
TronLines::TronLines() {
    
}

//-----------------------------------------------------------TronLines--
TronLines::~TronLines() {
    
}

//--------------------------------------------------------------
void TronLines::setup() {
    
    extrudeDepth = 100.0f ;

}

//--------------------------------------------------------------
void TronLines::setupGui(float a_x, float a_y) {
    // creates new gui and adds the name to it //
    BaseScene::setupGui(a_x, a_y);
    
    float dim = 24;
	float xInit = OFX_UI_GLOBAL_WIDGET_SPACING;
    float length = 320-xInit;
    
   // gui = new ofxUICanvas(0, 0, length+xInit, ofGetHeight());
  
    //gui->addWidgetDown(new ofxUIRangeSlider(length, dim, 0 , 10000 , pointCloudMinZ , pointCloudMaxZ, "POINT CLOUD Z RANGE")) ;
    int width = 300 ;
    int height = 18 ;
    
//    gui->addSlider( "MESH TIME HUE MULTIPLIER" , 0.0f , 255.0f , meshHueTimeMultiplier , width, height) ;
  
    gui->addSlider( "EXTRUDE DEPTH" , 0.0f , 1000.0f , extrudeDepth , width, height) ;
	 gui->addSlider( "LINE ROW SKIP" , 1.0f , 15.0f , &lineRowSkip ) ;
	//
    ofAddListener( gui->newGUIEvent, this, &TronLines::guiEvent );
}

//--------------------------------------------------------------
void TronLines::guiEvent(ofxUIEventArgs &e) {
    string name = e.widget->getName();
	int kind = e.widget->getKind();
    
 
    
    if (name == "EXTRUDE DEPTH" )
	{
		ofxUISlider *slider = (ofxUISlider *) e.widget;
        extrudeDepth = slider->getScaledValue() ;
	}
    

}

//--------------------------------------------------------------
void TronLines::update() {
    depthCameraManager->update( );
	depthCameraManager->calculatePointCloud( ) ; 
}

//--------------------------------------------------------------
void TronLines::draw() {

    ofSetColor( 255 , 255 ,255 ) ;

    cameraManager->begin();
    ofPushMatrix() ;
        //ofTranslate(0 , 0 , depthCameraManager->pointCloudZOffset ) ;
		drawPointCloud() ;
	ofPopMatrix();

    cameraManager->end() ;
}

void TronLines::drawPointCloud( )
{
    int w = depthCameraManager->getWidth() ; 
	int h = depthCameraManager->getHeight() ; 

    float _time = ofGetElapsedTimef() ; 
    float theta = sin ( ofGetElapsedTimef() ) ;

    int numTriangles = 0 ;
    ofPoint closestPoint = ofPoint ( 0 , 0 , 10000.0f ) ;
    
	ofColor col ; 

	int inc = (int) lineRowSkip ; 
	for(int y = 0; y < h; y+= inc ) //= pcsdkMan->step )
    {
		ofPath line ; 
		bool bLastValid = false; 
		for(int x = 0; x < w; x+= depthCameraManager->step ) //= pcsdkMan->step )
        {
            float low = ( sin ( ofGetElapsedTimef() * 1.5f ) + 1.0f ) / 2.0f ;
            float   noiseStep =  ofNoise( x + y * h * _time ) * extrudeDepth * low ;
            
            ofVec3f vertex = depthCameraManager->getWorldCoordAt(x,y) ;
			if ( vertex.z > depthCameraManager->pointCloudMinZ && vertex.z < depthCameraManager->pointCloudMaxZ )
            {
				//vertex.z *= -1 ;
                vertex.z -= noiseStep ;
				if ( bLastValid == false ) 
				{
					line.moveTo( vertex ) ; 
				}
				else
				{
					line.lineTo( vertex ) ;//addVertex( vertex ) ; 
				}
				bLastValid = true ; 
			}
			else
			{
				bLastValid = false ; 
			}
		}

		ofPushMatrix() ; 
        ofScale( depthCameraManager->scale , -depthCameraManager->scale , -depthCameraManager->scale );
        ofTranslate( 0 , 0 , depthCameraManager->pointCloudZOffset ) ;
        glEnable(GL_DEPTH_TEST);
        
        
        ofEnableBlendMode(OF_BLENDMODE_ADD);
		ofColor( 35 , 255 , 24 ) ;
		line.setColor( ofColor( 35 , 255 , 24 ) ) ; 
		line.setFilled( false ) ;
		line.setStrokeColor( ofColor( 35 , 255 , 24 ) ) ; 
		line.setStrokeWidth( 3 ) ; 
		line.draw() ;
        
        glDisable(GL_DEPTH_TEST);
        ofPopMatrix();
        
    }
}

bool TronLines::transitionIn( float delay , float transitionTime )
{
    if ( BaseScene::transitionIn( delay , transitionTime ) == false )
        return false ;
    else
    {
        //alpha = 0.0f;
       // Tweenzor::add( &alpha , alpha , 1.0f , delay , transitionTime ) ;
    }
    
    return true ;
}

bool TronLines::transitionOut( float delay , float transitionTime )
{
    if ( BaseScene::transitionOut( delay , transitionTime ) == false )
        return false ;
    else
    {
        //Tweenzor::add( &alpha , alpha , 0.0f , delay , transitionTime ) ;
    }
    return true ;
}


