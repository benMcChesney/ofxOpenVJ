//
//  PCSDK_HuePointCloud.h
//  ofxOpenVJ
//
//  Created by Ben McChesney on 6/5/12.
//
//



#include "PCSDK_HuePointCloud.h"

//--------------------------------------------------------------
PCSDK_HuePointCloud::PCSDK_HuePointCloud() {
    
}

//--------------------------------------------------------------
PCSDK_HuePointCloud::~PCSDK_HuePointCloud() {
    
}

//--------------------------------------------------------------
void PCSDK_HuePointCloud::setup() {
    
      meshHueTimeMultiplier = 0.0f ;
    extrudeDepth = 100.0f ;
    extrudeNoiseStrength = 0.0f ;
    redrawAlpha = 0.0f ; 
    
    
   //  string path = ofToDataPath( "../../../../ofxOpenVJ/shaders/" ) ;
    shader.load( shaderDirectory + "basic.vert", shaderDirectory + "PointCloud.frag" ) ;
    
    pixelSampling = 5.0 ; 
}

//--------------------------------------------------------------
void PCSDK_HuePointCloud::setupGui(float a_x, float a_y) {
    // creates new gui and adds the name to it //
    BaseScene::setupGui(a_x, a_y);
    
    float dim = 24;
	float xInit = OFX_UI_GLOBAL_WIDGET_SPACING;
    float length = 320-xInit;
   int width = 300 ;
    int height = 18 ;
	gui->addLabel("PCSDK_HUE_POINT_CLOUD" ) ; 
    gui->addSlider( "MESH TIME HUE MULTIPLIER" , 0.0f , 255.0f , meshHueTimeMultiplier , width, height) ;
    gui->addSlider( "EXTRUDE DEPTH" , 0.0f , 10.0f , extrudeDepth , width, height) ;
    gui->addSlider( "EXTRUDE NOISE STRENGTH" , 0.0f , 500.0f , extrudeNoiseStrength , width, height) ;
    gui->addSlider( "Y COLOR MULTIPLIER" , 0.0f , 6.5f  , yColorMultipler , width, height) ;
    gui->addSlider( "BOX SIZE" , 1.0f , 15.0f  , boxSize , width, height) ;
    gui->addSlider( "PIXEL SAMPLING" , 1.0f , 15.0f  , pixelSampling, width, height) ;
    gui->addSlider( "HUE TIME MULTIPLIER" , 1.0f , 15.0f  , hueTimeMultiplier , width, height) ;
    gui->addSlider(  "ROT TIME MULTIPLIER" , 1.0f , 15.0f  , rotationTimeMultiplier , width, height) ;
    gui->addSlider("HUE OFFSET RANGE", 0.0f , 255.0f , hueOffsetRange , width , height ) ;
    gui->addSlider("Y COLOR OFFSET", 0.0f , 3.0f , yColorOffset , width , height ) ;
    ofAddListener( gui->newGUIEvent, this, &PCSDK_HuePointCloud::guiEvent );
}

//--------------------------------------------------------------
void PCSDK_HuePointCloud::guiEvent(ofxUIEventArgs &e) {
    string name = e.widget->getName();
	int kind = e.widget->getKind();
    
    if(name == "MESH TIME HUE MULTIPLIER" )
	{
		ofxUISlider *slider = (ofxUISlider *) e.widget;
        meshHueTimeMultiplier = slider->getScaledValue() ;
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
}

//--------------------------------------------------------------
void PCSDK_HuePointCloud::activate() {
    
}

//--------------------------------------------------------------
void PCSDK_HuePointCloud::deactivate() {
    
    // turn off the gui //
    BaseScene::deactivate();
}

//--------------------------------------------------------------
void PCSDK_HuePointCloud::update() {
    depthCameraManager->update( );
	depthCameraManager->calculatePointCloud( ) ; 
}

//--------------------------------------------------------------
void PCSDK_HuePointCloud::draw() {
    
    ofSetColor( 255 , 255 ,255 ) ;
  
    cameraMan->begin();
    ofPushMatrix() ;
    ofTranslate(0 , 0 , cameraMan->zOffset ) ;
		drawPointCloud( ) ; 
	ofPopMatrix();

    cameraMan->end() ; 
}

void PCSDK_HuePointCloud::drawPointCloud( )
{
    int w = 640;
	int h = 480;
    ofPushMatrix();
    glEnable(GL_DEPTH_TEST);
    ofScale(1, -1, -1 * depthCameraManager->zScale);
    //ofTranslate(0, 0, kinectMan->pointCloudZOffset ); // center the points a bit
    ofEnableBlendMode( OF_BLENDMODE_ALPHA ) ; 
    
    
    ofColor offset = ofColor::fromHsb((ofGetFrameNum()/2  )%255, 255, 255 ) ;
    // ofEnableBlendMode( OF_BLENDMODE_ADD ) ;
	int step = pixelSampling ;
    //float boxSize = step ;//16.5f ;
	for(int y = 0; y < h; y += step) {
		for(int x = 0; x < w; x += step) {

			 ofVec3f vertex = depthCameraManager->getWorldCoordAt(x, y) ;
			
                
               
                if ( vertex.z >  depthCameraManager->pointCloudMinZ && vertex.z < depthCameraManager->pointCloudMaxZ )
                {
                    float normalizedZ = ofMap( vertex.z , depthCameraManager->pointCloudMinZ , depthCameraManager->pointCloudMaxZ , -360.0f , 360.0f ) + ofGetElapsedTimef() ;
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
    glDisable(GL_DEPTH_TEST);
    ofPopMatrix() ; 

}
