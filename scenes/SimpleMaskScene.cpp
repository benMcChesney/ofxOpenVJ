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
    
    string path = BaseScene::getDefaultShaderDirectory() ;
    shader.load( path+"basic.vert",path+"hexagon.frag" ) ;
    //tring path = ofToDataPath( "../../../../ofxOpenVJ/shaders/" ) ;
    
    string maskPath = "../../../../ofxSimpleMask/shaders/" ;
    simpleMask.setup( maskPath+"composite_rgb", ofRectangle( 0 , 0 , ofGetScreenWidth() , ofGetScreenHeight() )) ;
   // shader.load( "shader/basicVertex.vert" , "shader/hexagon.frag" ) ;
    fbo.allocate( ofGetScreenWidth() , ofGetScreenHeight() ) ;
    fbo.begin() ;
    ofClear( 1 , 1 , 1 , 0 ) ;
    fbo.end() ;
    
    alpha = 0.0f ;
    
    maskFbo.allocate( ofGetScreenWidth() , ofGetScreenHeight() ) ;
    maskFbo.begin() ;
    ofClear( 1 , 1 , 1 , 0 ) ;
    maskFbo.end() ;
    
    offsetAmount = 0.0f ; 
}

void SimpleMaskScene::setupGui(float a_x, float a_y) {
    // creates new gui and adds the name to it //
    BaseScene::setupGui(a_x, a_y);
    
    int width = 300 ;
    int height = 18 ;
    
    gui->addSlider( "Mask Fade Amount" , 0.0 , 255.0 , maskFadeAmount , width , height ) ;
    gui->addSlider( "Beat Decay Amount" , 0.0f , 1.0f , &decayAmount ) ;
    
    ofAddListener( gui->newGUIEvent, this, &SimpleMaskScene::guiEvent );
    
    loadSettings() ;
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

bool SimpleMaskScene::transitionIn( float delay , float transitionTime )
{
    if ( BaseScene::transitionIn( delay , transitionTime ) == false )
        return false ;
    else
    {
        alpha = 0.0f;
        Tweenzor::add( &alpha , alpha , 1.0f , delay , transitionTime ) ;
    }
    
    return true ;
}

bool SimpleMaskScene::transitionOut( float delay , float transitionTime )
{
    if ( BaseScene::transitionOut( delay , transitionTime ) == false )
        return false ;
    else
    {
        Tweenzor::add( &alpha , alpha , 0.0f , delay , transitionTime ) ;
    }
    return true ;
}


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
    
    if (  soundManager->beatDetector.isBeat( 0 ) )
        offsetAmount = 1.0f ;
    
    fbo.begin() ;
    shader.begin() ;
    shader.setUniform1f("time", sin ( ofGetElapsedTimef() * 0.7f ) * 8.0f  ) ; //ofGetElapsedTimef() );
    shader.setUniform2f("resolution", getWidth()  , getHeight() );
    shader.setUniform1f("low", 0.1f ) ; //offsetAmount ) ;
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
    
    ofSetColor( 255 , alpha * 255.0f ) ;
    
    simpleMask.drawMask( fbo.getTextureReference() , maskFbo.getTextureReference() , 0, 0, 1.0f ) ;
    ///fbo.draw( 0 , 0 ) ;
    //maskFbo.draw(0 , 0 ) ;
    
    //depthCameraManager->grayImage.draw( 0  , 0 ) ; //, getWidth() , getHeight() ) ;
    offsetAmount -= decayAmount ;
    if ( offsetAmount < 0 )
        offsetAmount = 0 ; 
}













