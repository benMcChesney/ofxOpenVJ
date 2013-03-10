//
//  TestScene.cpp
//  KinectPerformanceV01
//
//  Created by Nick Hardeman on 11/6/12.
//
//

#include "KinectShaderScene.h"

//--------------------------------------------------------------
KinectShaderScene::KinectShaderScene() {
    
}

//--------------------------------------------------------------
KinectShaderScene::~KinectShaderScene() {
    
}

//--------------------------------------------------------------
void KinectShaderScene::setup() {
    pointCloudMinZ = -100 ;
    pointCloudMaxZ = 100 ;
    
    meshHueTimeMultiplier = 0.0f ;
    bToggleTrails = false ;
    extrudeDepth = 100.0f ;
    extrudeNoiseStrength = 0.0f ;
    redrawAlpha = 0.0f ; 
    
    trailFbo.allocate( getWidth() , getHeight() , GL_RGBA ) ;
    
     string path = ofToDataPath( "../../../../ofxOpenVJ/shaders/" ) ;
    shader.load( path + "basic.vert", path + "PointCloud.frag" ) ;
}

//--------------------------------------------------------------
void KinectShaderScene::setupGui(float a_x, float a_y) {
    // creates new gui and adds the name to it //
    BaseScene::setupGui(a_x, a_y);
    
    float dim = 24;
	float xInit = OFX_UI_GLOBAL_WIDGET_SPACING;
    float length = 320-xInit;
    
   // gui = new ofxUICanvas(0, 0, length+xInit, ofGetHeight());
  
    gui->addWidgetDown(new ofxUIRangeSlider(length, dim, 0 , 10000 , pointCloudMinZ , pointCloudMaxZ, "POINT CLOUD Z RANGE")) ;
    gui->addWidgetDown(new ofxUISlider(length, dim, 0.0f , 255.0f , meshHueTimeMultiplier , "MESH TIME HUE MULTIPLIER")) ;
    gui->addWidgetDown(new ofxUISlider(length, dim, 0.0f , 255.0f , fboFadeAmount , "FBO FADE AMOUNT")) ;
    gui->addWidgetDown(new ofxUIToggle(dim, dim, bToggleTrails , "TOGGLE TRAILS")) ;
    gui->addWidgetDown(new ofxUISlider(length, dim, 0.0f , 10.0f , extrudeDepth , "EXTRUDE DEPTH")) ;
    gui->addWidgetDown(new ofxUISlider(length, dim, 0.0f , 500.0f , extrudeNoiseStrength , "EXTRUDE NOISE STRENGTH")) ;
    gui->addWidgetDown(new ofxUISlider(length, dim, -2000.0f, 2000.0f , zOffset , "Z OFFSET")) ;
    gui->addWidgetDown(new ofxUISlider(length, dim, 1.0 ,150.0f  , triangleSizeMax , "TRIANGLE MAX")) ;
    gui->addWidgetDown(new ofxUISlider(length, dim, 1.0 ,150.0f  , triangleSizeMin , "TRIANGLE MIN")) ;
    
    ofAddListener( gui->newGUIEvent, this, &KinectShaderScene::guiEvent );
}

//--------------------------------------------------------------
void KinectShaderScene::guiEvent(ofxUIEventArgs &e) {
    string name = e.widget->getName();
	int kind = e.widget->getKind();
    
    if(name == "POINT CLOUD Z RANGE" )
	{
		ofxUIRangeSlider *slider = (ofxUIRangeSlider *) e.widget;
        pointCloudMinZ = slider->getScaledValueLow() ;
        pointCloudMaxZ = slider->getScaledValueHigh() ;
	}
    
    if(name == "MESH TIME HUE MULTIPLIER" )
	{
		ofxUISlider *slider = (ofxUISlider *) e.widget;
        meshHueTimeMultiplier = slider->getScaledValue() ;
	}
    
    if(name == "FBO FADE AMOUNT" )
	{
		ofxUISlider *slider = (ofxUISlider *) e.widget;
        fboFadeAmount = slider->getScaledValue() ;
	}
    
    if ( name == "TOGGLE TRAILS")
    {
        ofxUIToggle *toggle = (ofxUIToggle *) e.widget;
        bToggleTrails = toggle->getValue() ;
    }
    
    if (name == "EXTRUDE DEPTH" )
	{
		ofxUISlider *slider = (ofxUISlider *) e.widget;
        extrudeDepth = slider->getScaledValue() ;
	}
    
    if (name == "EXTRUDE NOISE STRENGTH" )
	{
		ofxUISlider *slider = (ofxUISlider *) e.widget;
        extrudeNoiseStrength = slider->getScaledValue() ;
	}
  
    if (name == "PC Z" )
	{
		ofxUISlider *slider = (ofxUISlider *) e.widget;
	}
    
    if (name == "Z OFFSET" )
	{
		ofxUISlider *slider = (ofxUISlider *) e.widget;
        zOffset = slider->getScaledValue() ;
	}
    
    if (name ==  "TRIANGLE MAX" )
	{
		ofxUISlider *slider = (ofxUISlider *) e.widget;
        triangleSizeMax = slider->getScaledValue() ;
	}
    
    if (name == "TRIANGLE MIN" )
	{
		ofxUISlider *slider = (ofxUISlider *) e.widget;
        triangleSizeMin = slider->getScaledValue() ;
	}
}

//--------------------------------------------------------------
void KinectShaderScene::activate() {
    
}

//--------------------------------------------------------------
void KinectShaderScene::deactivate() {
    
    // turn off the gui //
    BaseScene::deactivate();
}

//--------------------------------------------------------------
void KinectShaderScene::update() {
    kinectMan->update( );
}

//--------------------------------------------------------------
void KinectShaderScene::draw() {

    trailFbo.begin () ;
    
    if ( bToggleTrails )
    {
        
        ofEnableBlendMode(OF_BLENDMODE_ADD ) ;
        ofSetColor( 255 , 255 , 255 , redrawAlpha ) ;
        trailFbo.draw( 0 , 0 );
        
        ofEnableAlphaBlending() ; 
        ofSetColor( 0 , 0 , 0, fboFadeAmount ) ;
        ofRect( 0 , 0,  getWidth() , getHeight() ) ;
    }
    else
    {
        ofClear( 1 , 1 , 1 , 0 ) ;
    }
    
    ofSetColor( 255 , 255 ,255 ) ;
    cameraMan->begin();
    drawPointCloud();
    cameraMan->end();
    trailFbo.end() ;
    
    ofSetColor( 255 , 255 , 255 ) ;
    ofPushMatrix( ) ;
        ofTranslate( 0 , ofGetHeight() ) ;
        ofScale( 1 , -1 , 1 ) ;
        trailFbo.draw(0 , 0 ) ;
        ofEnableBlendMode(OF_BLENDMODE_ADD ) ;
        ofSetColor( 255 , 255 , 255 , redrawAlpha ) ;
        trailFbo.draw( 0 , 0 );
    ofPopMatrix( ) ;
}

void KinectShaderScene::drawPointCloud( )
{
    int w = 640;
	int h = 480;
	ofMesh mesh;
	mesh.setMode( OF_PRIMITIVE_TRIANGLES );
	int step = 3;
    //Get out hue offset
    int timeHue = ofGetElapsedTimef() * meshHueTimeMultiplier ;
    timeHue %= 255 ;
    
    ofColor hueOffset = ofColor::fromHsb( timeHue , 255.0f , 255.0f ) ;
	
    float _time = ofGetElapsedTimef() ; 
    float theta = sin ( ofGetElapsedTimef() ) ;
    
    float center = ( pointCloudMinZ + pointCloudMaxZ ) / 2.0f ;
    
    int numTriangles = 0 ;
    ofPoint closestPoint = ofPoint ( 0 , 0 , 10000.0f ) ;
    
    for(int y = 0; y < h; y += step)
    {
		for(int x = 0; x < w; x += step)
        {

            float   noiseStep = 0 + ofSignedNoise( _time + x )*  extrudeNoiseStrength * extrudeDepth ;             
            float diff = low ; 
            
			if( kinectMan->kinect.getDistanceAt(x, y) > 0)
            {
                ofVec3f vertex = kinectMan->kinect.getWorldCoordinateAt(x, y) ;

                if ( vertex.z > pointCloudMinZ && vertex.z < pointCloudMaxZ )
                {
                    if ( vertex.z < closestPoint.z )
                        closestPoint = vertex ;
                    float zOffset = noiseStep ;
                    vertex.z += zOffset ;
                 
                    float offset = -1 ;
                    if ( numTriangles % 2 == 0 )
                        offset = 1 ; 
                    
                    ofColor col = kinectMan->kinect.getColorAt( x , y ) + hueOffset ;
                    ofVec3f _v = vertex ;
                    mesh.addVertex( vertex );
                    mesh.addColor( col );

               
                    vertex.x -= ofSignedNoise( _time ) * ( 1.0 + diff ) * triangleSizeMax + triangleSizeMin ;
                    vertex.y += ofSignedNoise ( _time ) * ( offset * 1.0f + diff  ) * triangleSizeMax + triangleSizeMin ;
                    mesh.addVertex( vertex );
                    mesh.addColor( col );
                    
                    _v.x += ofSignedNoise( _time ) * ( 1.0 + diff ) * triangleSizeMax + triangleSizeMin ;
                    _v.y += ofSignedNoise ( _time ) * ( offset * 1.0f + diff ) * triangleSizeMax + triangleSizeMin ;
                    mesh.addVertex( _v );
                    mesh.addColor( ofColor::white - col );

                    numTriangles++ ;
                }
			}
		}
	}
	glPointSize(3);
    
    
    ofPushMatrix();
    
    // the projected points are 'upside down' and 'backwards'
    ofEnableBlendMode(OF_BLENDMODE_ADD ) ; 
    ofScale(1, -1, -1);
        ofTranslate( 0.0f , 0.0f , zOffset ) ;
        glEnable(GL_DEPTH_TEST);
        mesh.draw( );
        glDisable(GL_DEPTH_TEST);
    ofPopMatrix();

}
