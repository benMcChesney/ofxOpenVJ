//
//  TestScene.cpp
//  KinectPerformanceV01
//
//  Created by Ben Mcchesney on 11/6/12.
//
//

#include "SimpleMaskScene.h"

//--------------------------------------------------------------
SimpleMaskScene::SimpleMaskScene() {
    
}

//--------------------------------------------------------------
SimpleMaskScene::~SimpleMaskScene() {
    
}

//--------------------------------------------------------------
void SimpleMaskScene::setup() {
    
    string path = ofToDataPath( "../../ofxOpenVJ/shaders/" ) ;
    //
    shader.load( path+"basic.vert", path+"hexagon.frag" ) ;
    cout << " path : " << ofToDataPath( path , true ) << endl;
    //tring path = ofToDataPath( "../../../../ofxOpenVJ/shaders/" ) ;
    
    string maskPath = "../../ofxSimpleMask/shaders/" ; 
    simpleMask.setup( maskPath+"composite_rgb", ofRectangle( 0 , 0 , ofGetScreenWidth() , ofGetScreenHeight() )) ;
   // shader.load( "shader/basicVertex.vert" , "shader/hexagon.frag" ) ;
    fbo.allocate( ofGetScreenWidth() , ofGetScreenHeight() ) ;
    fbo.begin() ;
    ofClear( 1 , 1 , 1 , 0 ) ;
    fbo.end() ;
    
    maskFbo.allocate( ofGetScreenWidth() , ofGetScreenHeight() ) ;
    maskFbo.begin() ;
    ofClear( 1 , 1 , 1 , 0 ) ;
    maskFbo.end() ;
    
    offsetAmount = 0.0f ; 
}

//--------------------------------------------------------------
void SimpleMaskScene::setupGui(float a_x, float a_y) {
    // creates new gui and adds the name to it //
    BaseScene::setupGui(a_x, a_y);
    
    //redrawAmount
    BaseScene::setupGui(a_x, a_y);
    
    float dim = 24;
	float xInit = OFX_UI_GLOBAL_WIDGET_SPACING;
    float length = 320-xInit;
    
    // gui = new ofxUICanvas(0, 0, length+xInit, ofGetHeight());
    
    //gui->addWidgetDown(new ofxUIRangeSlider(length, dim, 0 , 10000 , pointCloudMinZ , pointCloudMaxZ, "POINT CLOUD Z RANGE")) ;
    int width = 300 ;
    int height = 18 ;
    
    gui->addSlider( "Mask Fade Amount" , 0.0 , 255.0 , maskFadeAmount , width , height ) ; 
    gui->addSlider( "Beat Decay Amount" , 0.0f , 0.25f , &decayAmount ) ; 
    
    ofAddListener( gui->newGUIEvent, this, &SimpleMaskScene::guiEvent );
    
    BaseScene::loadSettings() ; 
}

//--------------------------------------------------------------
void SimpleMaskScene::guiEvent(ofxUIEventArgs &e) {
    string name = e.widget->getName();
	int kind = e.widget->getKind();
    
    if(name == "Mask Fade Amount" )
	{
		ofxUISlider *slider = (ofxUISlider *) e.widget;
        maskFadeAmount = slider->getScaledValue() ;
	}
    
    BaseScene::guiEvent( e ) ; 
}

/*
//--------------------------------------------------------------
void SimpleMaskScene::activate() {
    BaseScene::activate() ; 
    if(fbo.getWidth() != getWidth() || fbo.getHeight() != getHeight()) {
        fbo.allocate( getWidth() , getHeight(), GL_RGBA ) ;
        fbo.begin() ;
        ofClear( 1 , 1 , 1 , 0 ) ;
        fbo.end() ;
    }
}*/


//--------------------------------------------------------------
void SimpleMaskScene::update() {
    
    BaseScene::update( ) ;
    depthCameraManager->update();
//    if(depthCameraManager->isFrameNew()) {
        depthCameraManager->calculateCVOperations();
        
     //   if( ( ofGetElapsedTimeMillis() - lastAddTime  ) > millisDelay ) {
     //       addContour();
            //cout << "lines.size() = " << lines.size() << " particles.size() = " << particles.size() << endl;
    
    //}
}

//--------------------------------------------------------------
void SimpleMaskScene::draw() {
    
   
    ofSetColor(255, 255, 255);
    
    if (  beatDetector->isBeat( 0 ) )
        offsetAmount = 1.0f ;
    
    fbo.begin() ;
    shader.begin() ;
    shader.setUniform1f("time", ofGetElapsedTimef() );
    shader.setUniform2f("resolution", getWidth()  , getHeight() );
    shader.setUniform1f("low", offsetAmount ) ;
    ofSetColor( 255 ) ;
    ofRect( 0 , 0 , getWidth() , getHeight() ) ;
    shader.end() ;
    fbo.end() ;
    
    ofEnableAlphaBlending() ;
    maskFbo.begin() ;
    ofSetColor( 0 , 0 , 0, maskFadeAmount ) ;
    ofRect( 0 , 0 , getWidth() , getHeight() ) ;
    ofSetColor( 255 , 255 , 255 ) ;
        depthCameraManager->grayImage.draw( 0  , 0 , ofGetWidth(), ofGetHeight()) ;
    ofEnableAlphaBlending() ;
    maskFbo.end() ;
    
    ofSetColor( 255 ) ;
    
    simpleMask.drawMask( fbo.getTextureReference() , maskFbo.getTextureReference() , 0, 0, 1.0f ) ;
    ///fbo.draw( 0 , 0 ) ;
    //maskFbo.draw(0 , 0 ) ;
    
    //depthCameraManager->grayImage.draw( 0  , 0 ) ; //, getWidth() , getHeight() ) ;
    offsetAmount -= decayAmount ;
    if ( offsetAmount < 0 )
        offsetAmount = 0 ; 
}

//--------------------------------------------------------------
void SimpleMaskScene::drawDebug() {
    
}
















