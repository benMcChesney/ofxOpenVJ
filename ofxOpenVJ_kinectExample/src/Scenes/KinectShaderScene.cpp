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
    
    meshHueTimeMultiplier = 0.0f ;
    bToggleTrails = false ;
    extrudeDepth = 100.0f ;
    extrudeNoiseStrength = 0.0f ;
    redrawAlpha = 0.0f ; 
    
    trailFbo.allocate( getWidth() , getHeight() , GL_RGBA ) ;
    
    string path = ofToDataPath( "shaders/" ) ;
    shader.load( path + "basic.vert", path + "PointCloud.frag" ) ;
    
    pixelSampling = 5.0 ; 
}

//--------------------------------------------------------------
void KinectShaderScene::setupGui(float a_x, float a_y) {
    // creates new gui and adds the name to it //
    BaseScene::setupGui(a_x, a_y);
    
    float dim = 24;
	float xInit = OFX_UI_GLOBAL_WIDGET_SPACING;
    float length = 320-xInit;
    
   // gui = new ofxUICanvas(0, 0, length+xInit, ofGetHeight());
  
    int width = 300 ;
    int height = 18 ;
    gui->addLabel( name ) ; 
    gui->addSlider( "MESH TIME HUE MULTIPLIER" , 0.0f , 255.0f , meshHueTimeMultiplier , width, height) ;
    gui->addSlider( "FBO FADE AMOUNT" , 0.0f , 255.0f , fboFadeAmount , width, height) ;
     gui->addWidgetDown(new ofxUIToggle(dim, dim, bToggleTrails , "TOGGLE TRAILS")) ;
    gui->addSlider( "EXTRUDE DEPTH" , 0.0f , 10.0f , extrudeDepth , width, height) ;
    gui->addSlider( "EXTRUDE NOISE STRENGTH" , 0.0f , 500.0f , extrudeNoiseStrength , width, height) ;
    gui->addSlider( "Y COLOR MULTIPLIER" , 0.0f , 6.5f  , yColorMultipler , width, height) ;
    gui->addSlider( "BOX SIZE" , 1.0f , 15.0f  , boxSize , width, height) ;
    gui->addSlider( "PIXEL SAMPLING" , 1.0f , 15.0f  , pixelSampling, width, height) ;
    gui->addSlider( "HUE TIME MULTIPLIER" , 1.0f , 15.0f  , hueTimeMultiplier , width, height) ;
    gui->addSlider(  "ROT TIME MULTIPLIER" , 1.0f , 15.0f  , rotationTimeMultiplier , width, height) ;
    gui->addSlider("HUE OFFSET RANGE", 0.0f , 255.0f , hueOffsetRange , width , height ) ;
    gui->addSlider("Y COLOR OFFSET", 0.0f , 3.0f , yColorOffset , width , height ) ;
    //
    //hueOffsetRange
    ofAddListener( gui->newGUIEvent, this, &KinectShaderScene::guiEvent );
}

//--------------------------------------------------------------
void KinectShaderScene::guiEvent(ofxUIEventArgs &e) {
    string name = e.widget->getName();
	int kind = e.widget->getKind();
    
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
    
    if (name == "Y COLOR MULTIPLIER" ) yColorMultipler = ((ofxUISlider *) e.widget)->getScaledValue() ;
    if (name == "BOX SIZE" ) boxSize = ((ofxUISlider *) e.widget)->getScaledValue() ;
    if (name == "PIXEL SAMPLING" ) pixelSampling = ((ofxUISlider *) e.widget)->getScaledValue() ;
    //if (name == "TIME MULTIPLIER" ) timeMultiplier = ((ofxUISlider *) e.widget)->getScaledValue() ;
    if (name == "HUE TIME MULTIPLIER" ) hueTimeMultiplier = ((ofxUISlider *) e.widget)->getScaledValue() ;
    if (name == "ROT TIME MULTIPLIER" ) rotationTimeMultiplier = ((ofxUISlider *) e.widget)->getScaledValue() ;
    
    if (name =="HUE OFFSET RANGE" ) hueOffsetRange = ((ofxUISlider *) e.widget)->getScaledValue() ;
    if (name =="Y COLOR OFFSET" ) yColorOffset= ((ofxUISlider *) e.widget)->getScaledValue() ;
        //, 0.0f , 100.0f , yColorOffset , width , height ) ;
    //  gui->addSlider("HUE OFFSET R" ) hueOffsetRange = ((ofxUISlider *) e.widget)->getScaledValue() ;
    
    //gui->addSlider("Y COLOR OFFSET", 0.0f , 100.0f , yColorOffset , width , height ) ;
    //  gui->addSlider("HUE OFFSET RANGE", 0.0f , 255.0f , hueOffsetRange , width , height ) ;
    
    /*
     gui->addWidgetDown(new ofxUISlider(length, dim, 1.0f , 15.0f  ,  , )) ;
     gui->addWidgetDown(new ofxUISlider(length, dim, 1.0f , 15.0f  ,  , )) ;
     */
    //gui->addWidgetDown(new ofxUISlider(length, dim, 1.0f , 5.0f  , timeMultiplier , )) ;

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

  //  trailFbo.begin () ;
    ofBackground ( 0 ) ;
    
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
    cameraMan->begin() ;
        ofPushMatrix() ;
            ofTranslate(0 , 0 , cameraMan->zOffset ) ;
            drawPointCloud();
        ofPopMatrix();
    cameraMan->end() ;
//    trailFbo.end() ;
    /*
    ofSetColor( 255 , 255 , 255 ) ;
    ofPushMatrix( ) ;
        ofTranslate( 0 , ofGetHeight() ) ;
        ofScale( 1 , -1 , 1 ) ;
        trailFbo.draw(0 , 0 ) ;
        ofEnableBlendMode(OF_BLENDMODE_ADD ) ;
        ofSetColor( 255 , 255 , 255 , redrawAlpha ) ;
        trailFbo.draw( 0 , 0 );
    ofPopMatrix( ) ;*/
}

void KinectShaderScene::drawPointCloud( )
{
    int w = 640;
	int h = 480;
    ofPushMatrix();
    glEnable(GL_DEPTH_TEST);
    ofScale(1, 1, -1);
    //ofTranslate(0, 0, kinectMan->pointCloudZOffset ); // center the points a bit
    ofEnableBlendMode( OF_BLENDMODE_ALPHA ) ; 
    
    
    ofColor offset = ofColor::fromHsb((ofGetFrameNum()/2  )%255, 255, 255 ) ;
    // ofEnableBlendMode( OF_BLENDMODE_ADD ) ;
	int step = pixelSampling ;
    //float boxSize = step ;//16.5f ;
	for(int y = 0; y < h; y += step) {
		for(int x = 0; x < w; x += step) {
			if(kinectMan->kinect.getDistanceAt(x, y) > 0) {
                
                ofVec3f vertex = kinectMan->getWorldCoordAt(x, y) ;
                if ( vertex.z >  kinectMan->pointCloudMinZ && vertex.z < kinectMan->pointCloudMaxZ )
                {
                    float normalizedZ = ofMap( vertex.z , kinectMan->pointCloudMinZ , kinectMan->pointCloudMaxZ , -360.0f , 360.0f ) + ofGetElapsedTimef() ;
                    //mesh.addVertex( vertex );
                    
                    //Offset the color here
                    float _yColor = yColorOffset *  ( low + 0.01 ) ; 
                    int hue = ((int)(ofGetFrameNum()*hueTimeMultiplier)) % 255 + (float)y * _yColor  ;
                     hue += ofSignedNoise ( ofGetElapsedTimef() + vertex.y * yColorOffset ) * hueOffsetRange ;
                    
                    while ( hue >= 254 )
                    {
                        hue -= 255 ;
                    }
                    
                   
                   // unsigned char _b =
                   // ofColor col = ofColor::fromHsb( hue , ofNoise( ofGetElapsedTimef() ) * 20 + 220 , 255 ) ;
                    
                     ofColor col = ofColor::fromHsb( hue  , 255 , 255 ) ;
                   
                    //if ( col.getBrightness() < kinectMan->minimumPixBrightness )
                    //    col.setBrightness( kinectMan->minimumPixBrightness );
                    //mesh.addColor( col );
                    ofSetColor( col ) ;
                    ofPushMatrix() ;
                    ofQuaternion rot ;
                    ofQuaternion rotX = ofQuaternion( sin( ofGetElapsedTimef() + y + x * 5.5f ) * 360.0f * rotationTimeMultiplier , ofVec3f( 0.0f , 1.0f , 0.0f ) ) ;
                    ofQuaternion rotY = ofQuaternion( normalizedZ , ofVec3f( 1.0f , 0.0f , 1.0f ) ) ;
                    rot = rotX * rotY ;
                    ofVec3f axis ;
                    float angle ;
                    rot.getRotate( angle , axis ) ;
                    
                    ofTranslate( vertex ) ;
                    ofRotate( angle , axis.x , axis.y , axis.z ) ;
                    ofBox( ofVec3f( )  , boxSize ) ;
                    ofPopMatrix() ;
                }
                
			}
		}
	}
    glDisable(GL_DEPTH_TEST);
    ofPopMatrix() ; 
}
