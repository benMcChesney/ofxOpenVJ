//
//  TestScene.cpp
//  KinectPerformanceV01
//
//  Created by Nick Hardeman on 11/6/12.
//
//

#include "KinectVertexShader.h"

//--------------------------------------------------------------
KinectVertexShader::KinectVertexShader() {
    
}

//--------------------------------------------------------------
KinectVertexShader::~KinectVertexShader() {
    
}

//--------------------------------------------------------------
void KinectVertexShader::setup() {
   
    string path = ofToDataPath( "../../../../ofxOpenVJ/shaders/" ) ;
    shader.load( path + "twist.vert", path + "twist.frag" ) ; 
    pixelSampling = 5.0 ; 
}

//--------------------------------------------------------------
void KinectVertexShader::setupGui(float a_x, float a_y) {
    // creates new gui and adds the name to it //
    BaseScene::setupGui(a_x, a_y);
    
    float dim = 24;
	float xInit = OFX_UI_GLOBAL_WIDGET_SPACING;
    float length = 320-xInit;
    int width = 300 ;
    int height = 18 ;
   // gui = new ofxUICanvas(0, 0, length+xInit, ofGetHeight());
  
    gui->addSlider("HUE TIME MULTIPLIER", 0.0f , 5.0f , hueTimeMultiplier  , width, height) ;
    gui->addSlider("SHADER FLOAT 1", 0.0f  , 200.0f  , shaderVar1  , width, height) ;
    gui->addSlider("SHADER FLOAT 2", 0.0f  , 200.0f  , shaderVar2  , width, height) ;
    gui->addSlider("SHADER FLOAT 3", 0.0f  , 200.0f  , shaderVar3 , width, height) ;
    gui->addSlider("SHADER FLOAT 4", 0.0f  , 200.0f  , shaderVar4 , width, height) ;
    
    
    boxStep = 5.0f ;
    
    gui->addSlider("BOX SIZE", 0.1f  , 50.0f  , boxSize , width, height) ;
    gui->addSlider("BOX STEP", 1.0f  , 10.0f  , boxStep , width, height) ;
    gui->addWidgetDown(new ofxUIToggle("USE SHADER" , bDrawShader , dim , dim ) ) ;

    ofAddListener( gui->newGUIEvent, this, &KinectVertexShader::guiEvent );
}

//--------------------------------------------------------------
void KinectVertexShader::guiEvent(ofxUIEventArgs &e) {
    string name = e.widget->getName();
	int kind = e.widget->getKind();
    
    if(name == "HUE TIME MULTIPLIER" )
	{
		ofxUISlider *slider = (ofxUISlider *) e.widget;
        hueTimeMultiplier = slider->getScaledValue() ;
	}
    
    if(name == "USE SHADER" )
	{
		ofxUIToggle *toggle = (ofxUIToggle *) e.widget;
        bDrawShader = toggle->getValue() ;
	}
    
    if(name ==  "SHADER FLOAT 1" ) shaderVar1 = ((ofxUISlider *) e.widget)->getScaledValue() ;
    if(name ==  "SHADER FLOAT 2" ) shaderVar2 = ((ofxUISlider *) e.widget)->getScaledValue() ;
    if(name ==  "SHADER FLOAT 3" ) shaderVar3 = ((ofxUISlider *) e.widget)->getScaledValue() ;
    if(name ==  "SHADER FLOAT 4" ) shaderVar4 = ((ofxUISlider *) e.widget)->getScaledValue() ;
    
    if ( name == "BOX SIZE" ) boxSize = ((ofxUISlider *) e.widget)->getScaledValue() ;
    if ( name == "BOX STEP" ) boxStep = ((ofxUISlider *) e.widget)->getScaledValue() ;
}

//--------------------------------------------------------------
void KinectVertexShader::activate() {
    
}

//--------------------------------------------------------------
void KinectVertexShader::deactivate() {
    
    // turn off the gui //
    BaseScene::deactivate();
}

//--------------------------------------------------------------
void KinectVertexShader::update() {
    depthCameraManager->update( );
	depthCameraManager->calculatePointCloud( ) ; 
}

//--------------------------------------------------------------
void KinectVertexShader::draw() {

    
  
    
    //ofBackground( 255 , 255 , 255 ) ; //, <#int b#>)
    ofSetColor( 255 , 255 ,255 ) ;
    
    if ( bDrawShader )
    {
        shader.begin() ;
        //shader.setUniform1f("time", ofGetElapsedTimef() ) ;
        shader.setUniform1f("time", ofGetElapsedTimef() ) ;
        shader.setUniform1f("var1", shaderVar1 ) ; //+ sin ( ofGetElapsedTimef() ) * .2f ) ;
        shader.setUniform1f("var2", shaderVar2 ) ; //* mid ) ;
        shader.setUniform1f("var3", shaderVar3 ) ;
        shader.setUniform1f("var4", shaderVar4 * low ) ;
    }
    
   // kinectMan->post.begin( cameraMan->cam )  ;
   cameraMan->begin();
   ofPushMatrix() ;
       ofTranslate(0 , 0 , cameraMan->zOffset ) ;
       drawPointCloud();
   ofPopMatrix();
   cameraMan->end();

    if ( bDrawShader )
    {
		shader.end() ; 
	}
    //kinectMan->post.end( ) ;
}

void KinectVertexShader::drawPointCloud( )
{
	int w = depthCameraManager->getWidth() ; 
	int h = depthCameraManager->getHeight() ; 
    /*
     Change the color based on time. You can use ofGetElapsedTimef() which returns
     a float for how many seconds this app has been running
     
     in can be used such as :
     sin( ofGetElapsedTimef() )
     ofNoise( ofGetElapsedTimef() )
     
     for interesting repeating animation patterns
     
     ofColor has a function called "fromHSB( hue , saturation , brightness )" that allows for easy color offset
     */
    
    //ofColor offset = ?
    ofPushMatrix();
   // glEnable(GL_DEPTH_TEST);
	ofScale(1, -1, -1 * depthCameraManager->zScale );
   
    ofEnableBlendMode( OF_BLENDMODE_ALPHA ) ;
    
    
    
    ofColor offset = ofColor::fromHsb(( (int)(ofGetFrameNum() * hueTimeMultiplier)  )%255, 255, 255 ) ;
    // ofEnableBlendMode( OF_BLENDMODE_ADD ) ;
	int step = boxStep ;

	for(int y = 0; y < h; y += step) 
	{
		for(int x = 0; x < w; x += step) 
		{
	
            ofVec3f vertex = depthCameraManager->getWorldCoordAt(x, y) ;
            if ( vertex.z > depthCameraManager->pointCloudMinZ && vertex.z < depthCameraManager->pointCloudMaxZ )
            {
                float normalizedZ = ofMap( vertex.z , depthCameraManager->pointCloudMinZ , depthCameraManager->pointCloudMaxZ , -360.0f , 360.0f ) ;
                //mesh.addVertex( vertex );
                    
                //Offset the color here
                ofColor col = depthCameraManager->getColorAt(x,y) + offset ; // + offset ;
                    
                if ( col.getBrightness() < depthCameraManager->minimumPixBrightness )
                    col.setBrightness( depthCameraManager->minimumPixBrightness );
                    
                //float kinectHue = kinectMan->kinect.getColorAt( x , y ).getHue() ;
                //float ofMap(float value, float inputMin, float inputMax, float outputMin, float outputMax, bool clamp) {
                float hue = ((int)(ofGetElapsedTimef() * hueTimeMultiplier )) % 255  + col.getHue() ;
                    
                float zHueOffset = ofMap( vertex.z , depthCameraManager->pointCloudMinZ , depthCameraManager->pointCloudMaxZ ,  0 , 254.0f ) ;
                hue+= zHueOffset ;
                    
                    
                while ( hue > 254 )
                {
                    hue -= 255.0f ;
                }
                //mesh.addColor( col );
                col.setHue( hue ) ; 
                ofSetColor( col ) ;
                ofPushMatrix() ;
                ofQuaternion rot ;
                ofQuaternion rotX = ofQuaternion( sin( ofGetElapsedTimef() + y + x * 2.5f ) * 360.0f , ofVec3f( 0.0f , 1.0f , 0.0f ) ) ;
                ofQuaternion rotY = ofQuaternion( normalizedZ , ofVec3f( 1.0f , 0.0f , 0.0f ) ) ;
                rot = rotX * rotY ;
                ofVec3f axis ;
                float angle ;
                rot.getRotate( angle , axis ) ;
                    
                //vertex.z += kinectMan->pointCloudZOffset ;
                ofTranslate( vertex ) ;
                ofRotate( angle , axis.x , axis.y , axis.z ) ;
                ofBox( ofVec3f( )  , boxSize ) ;
                ofPopMatrix() ;
            }
				
		}
	}
    //glDisable(GL_DEPTH_TEST);
    ofPopMatrix();
   // ofEnableBlendMode( OF_BLENDMODE_ADD ) ;
}
