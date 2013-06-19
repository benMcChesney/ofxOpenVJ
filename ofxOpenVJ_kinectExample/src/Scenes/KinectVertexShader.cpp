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
    
    
    bToggleTrails = false ;
    redrawAlpha = 0.0f ; 
    
    trailFbo.allocate( getWidth() , getHeight() , GL_RGBA ) ;
    
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
    gui->addSlider("FBO FADE AMOUNT", 0.0f , 255.0f , fboFadeAmount  , width, height) ;
    gui->addSlider("SHADER FLOAT 1", 0.0f  , 200.0f  , shaderVar1  , width, height) ;
    gui->addSlider("SHADER FLOAT 2", 0.0f  , 200.0f  , shaderVar2  , width, height) ;
    gui->addSlider("SHADER FLOAT 3", 0.0f  , 200.0f  , shaderVar3 , width, height) ;
    gui->addSlider("SHADER FLOAT 4", 0.0f  , 200.0f  , shaderVar4 , width, height) ;
    
    
    boxStep = 5.0f ;
    
    gui->addSlider("BOX SIZE", 0.1f  , 50.0f  , boxSize , width, height) ;
    gui->addSlider("BOX STEP", 1.0f  , 10.0f  , boxStep , width, height) ;
    
    gui->addWidgetDown(new ofxUIToggle(dim, dim, bToggleTrails , "TOGGLE TRAILS")) ;
    gui->addWidgetDown(new ofxUIToggle("USE SHADER" , bDrawShader , dim , dim ) ) ;

    /*
     int width = 300 ;
     int height = 25 ;
     gui->addSlider("FORCE RADIUS", 0.0f , 1200.0f , forceRadius, width, height) ;
   
     */
    
    /*
     float boxSize ;
     float boxStep ;
     */
    //
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
    
    if(name == "USE SHADER" )
	{
		ofxUIToggle *toggle = (ofxUIToggle *) e.widget;
        bDrawShader = toggle->getValue() ;
	}
    
    if(name ==  "SHADER FLOAT 1" ) shaderVar1 = ((ofxUISlider *) e.widget)->getScaledValue() ;
    if(name ==  "SHADER FLOAT 2" ) shaderVar2 = ((ofxUISlider *) e.widget)->getScaledValue() ;
    if(name ==  "SHADER FLOAT 3" ) shaderVar3 = ((ofxUISlider *) e.widget)->getScaledValue() ;
    if(name ==  "SHADER FLOAT 4" ) shaderVar4 = ((ofxUISlider *) e.widget)->getScaledValue() ;
    
    /*
     gui->addSlider("BOX SIZE", 0.1f  , 50.0f  , boxSize , width, height) ;
     gui->addSlider("BOX STEP", 1.0f  , 10.0f  , boxStep , width, height) ;
   
    */
    
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
    kinectMan->update( );
}

//--------------------------------------------------------------
void KinectVertexShader::draw() {

    
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
    
    ofBackground( 255 , 255 , 255 ) ; //, <#int b#>)
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
    //kinectMan->post.end( ) ;
    trailFbo.end() ;
    
    if ( bDrawShader )
        shader.end( ) ;
    
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

void KinectVertexShader::drawPointCloud( )
{
    int w = 640;
	int h = 480;
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
    glEnable(GL_DEPTH_TEST);
    ofScale(1, -1, -1);
   
    ofEnableBlendMode( OF_BLENDMODE_ALPHA ) ;
    
    
    
    ofColor offset = ofColor::fromHsb(( (int)(ofGetFrameNum() * hueTimeMultiplier)  )%255, 255, 255 ) ;
    // ofEnableBlendMode( OF_BLENDMODE_ADD ) ;
	int step = boxStep ;

	for(int y = 0; y < h; y += step) {
		for(int x = 0; x < w; x += step) {
			if(kinectMan->kinect.getDistanceAt(x, y) > 0) {
				
                ofVec3f vertex = kinectMan->getWorldCoordAt(x, y) ;
                if ( vertex.z > kinectMan->pointCloudMinZ && vertex.z < kinectMan->pointCloudMaxZ )
                {
                    float normalizedZ = ofMap( vertex.z , kinectMan->pointCloudMinZ , kinectMan->pointCloudMaxZ , -360.0f , 360.0f ) ;
                    //mesh.addVertex( vertex );
                    
                    //Offset the color here
                    ofColor col = kinectMan->kinect.getColorAt(x,y) + offset ; // + offset ;
                    
                    if ( col.getBrightness() < kinectMan->minimumPixBrightness )
                        col.setBrightness( kinectMan->minimumPixBrightness );
                    
                    //float kinectHue = kinectMan->kinect.getColorAt( x , y ).getHue() ;
                    //float ofMap(float value, float inputMin, float inputMax, float outputMin, float outputMax, bool clamp) {
                    float hue = ((int)(ofGetElapsedTimef() * hueTimeMultiplier )) % 255  + col.getHue() ;
                    
                    float zHueOffset = ofMap( vertex.z , kinectMan->pointCloudMinZ , kinectMan->pointCloudMaxZ ,  0 , 254.0f ) ;
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
	}
    glDisable(GL_DEPTH_TEST);
    ofPopMatrix();
    ofEnableBlendMode( OF_BLENDMODE_ADD ) ;
}
