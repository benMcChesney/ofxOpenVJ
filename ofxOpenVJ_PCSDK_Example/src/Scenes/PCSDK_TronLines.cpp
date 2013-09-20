//
//  PCSDK_TronLines.cpp
//  KinectPerformanceV01
//
//  Created by Ben McChesney on 7/25/2013.
//
//

#include "PCSDK_TronLines.h"
//--------------------------------------------------------------
PCSDK_TronLines::PCSDK_TronLines() {
    
}

//--------------------------------------------------------------
PCSDK_TronLines::~PCSDK_TronLines() {
    
}

//--------------------------------------------------------------
void PCSDK_TronLines::setup() {
    
    extrudeDepth = 100.0f ;
 
  hue = 0.0f ; 
  //   string path = ofToDataPath( "../../../../ofxOpenVJ/shaders/" ) ;
   // shader.load( path + "basic.vert", path + "PointCloud.frag" ) ;
}

//--------------------------------------------------------------
void PCSDK_TronLines::setupGui(float a_x, float a_y) {
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
  
    gui->addSlider( "EXTRUDE DEPTH" , 0.0f ,800.0f , extrudeDepth , width, height) ;
	 gui->addSlider( "LINE ROW SKIP" , 1.0f , 15.0f , &lineRowSkip ) ;
	 gui->addSlider( "EXTRUDE OFFSET" , 0.0f , 15.0f , &noiseOffset ) ; 
	 gui->addSlider( "MAX Z CONNECT DISTANCE" , 0.0f , 1000.0f , &maxZConnectDist ) ; 
	 gui->addSlider( "HUE ADDITION MULTIPLER" , 0.0f , 30.0f , &hueAdditionMultiplier ) ; 
	 gui->addSlider( "STROKE WIDTH" , 0.1f , 30.0f , &strokeWidth ) ; 
	 gui->addSlider( "X STEP" , 1.0f , 6.0f , &xStep ); 
	 gui->addSlider( "LINE ALPHA" , 0.0f , 255.0f , &lineAlpha ); 
	 gui->addToggle( "STROKE" , &bStroke ) ;
	 gui->addToggle( "FILL" , &bFill ) ; 
	//
    ofAddListener( gui->newGUIEvent, this, &PCSDK_TronLines::guiEvent );
}

//--------------------------------------------------------------
void PCSDK_TronLines::guiEvent(ofxUIEventArgs &e) {
    string name = e.widget->getName();
	int kind = e.widget->getKind();
    
 
    
    if (name == "EXTRUDE DEPTH" )
	{
		ofxUISlider *slider = (ofxUISlider *) e.widget;
        extrudeDepth = slider->getScaledValue() ;
	}
    
    if (name == "PC Z" )
	{
		ofxUISlider *slider = (ofxUISlider *) e.widget;
	}
}

//--------------------------------------------------------------
void PCSDK_TronLines::activate() {
    
}

//--------------------------------------------------------------
void PCSDK_TronLines::deactivate() {
    
    // turn off the gui //
    BaseScene::deactivate();
}

//--------------------------------------------------------------
void PCSDK_TronLines::update() {

	hue += ( low * hueAdditionMultiplier ) ; 
	if ( low > 0.25f )
		hue += ( hueAdditionMultiplier * 2.0 ) ; 
	if ( hue >= 255 ) 
		hue -= 255 ; 
    depthCameraManager->update( );
	depthCameraManager->calculatePointCloud( ) ; 
}

//--------------------------------------------------------------
void PCSDK_TronLines::draw() {

    ofSetColor( 255 , 255 ,255 ) ;

    cameraMan->begin();
    ofPushMatrix() ;
    ofTranslate(0 , 0 , cameraMan->zOffset ) ;
		drawPointCloud() ;
	ofPopMatrix();

    cameraMan->end() ; 
}

void PCSDK_TronLines::drawPointCloud( )
{
    int w = depthCameraManager->getWidth() ; 
	int h = depthCameraManager->getHeight() ; 

	//cout << "low : " << low << endl ; 
	ofMesh mesh;
	mesh.setMode( OF_PRIMITIVE_TRIANGLES );

    float _time = ofGetElapsedTimef() ; 
    float theta = sin ( ofGetElapsedTimef() ) ;

    int numTriangles = 0 ;
    ofPoint closestPoint = ofPoint ( 0 , 0 , 10000.0f ) ;
    
	ofColor col ; 

	ofPoint lastPoint ; 
	int inc = (int) lineRowSkip ; 
	//ofEnableBlendMode( OF_BLENDMODE_ADD ) ; 
	for(int y = 0; y < h; y+= inc ) //= pcsdkMan->step )
    {
		ofPath line ; 
		bool bLastValid = false; 

		int _xStep = (int) xStep ; 
		for(int x = 0; x < w; x+= depthCameraManager->step + _xStep  ) //= pcsdkMan->step )
        {
			ofVec3f vertex = depthCameraManager->getWorldCoordAt(x,y) ;
			ofPoint _lastPoint = vertex ; 
			 float dist = abs(vertex.z - lastPoint.z) ;

			 float   noiseStep = ( ofNoise( _time + x + y ) + noiseOffset ) * extrudeDepth ; 
			 vertex.z += (( noiseStep + 0.01 ) * low ); 
			// float dist = vertex.distance( lastPoint ) ; // 
			
			if ( vertex.z > depthCameraManager->pointCloudMinZ && vertex.z < depthCameraManager->pointCloudMaxZ )
            {
			
				 float diff = low ; 

				if (  dist < maxZConnectDist  ) 
				{
				
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
			lastPoint = vertex ;
		}

		ofColor c = ofColor::fromHsb( hue , sin( ofGetElapsedTimef() * 20 ) + 225 , lineAlpha ) ; 
		ofPushMatrix() ; 
		ofScale(1, -1, -1 * depthCameraManager->zScale);
		ofColor( 35 , 255 , 24 ) ; 
		line.setColor( c ) ; 
		
		line.setFilled( bFill ) ;
		
		if ( bStroke ) 
		{
		line.setStrokeColor( c ) ; 
		line.setStrokeWidth( ofNoise( y ) * strokeWidth ) ; 
		}
		else
		{
			line.setStrokeWidth( 0 ) ; 
		}
			line.draw() ; 
		ofPopMatrix() ; 
	}

	ofEnableBlendMode( OF_BLENDMODE_ALPHA ) ; 
}
