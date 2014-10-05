//
//  PCSDK_TronLines.cpp
//  KinectPerformanceV01
//
//  Created by Ben McChesney on 7/25/2013.
//
//

#include "RippleTunnelScene.h"
//--------------------------------------------------------------
RippleTunnelScene::RippleTunnelScene()
{
    
}

//-------------------------------------------------------------
RippleTunnelScene::~RippleTunnelScene() {
    
}

//--------------------------------------------------------------
void RippleTunnelScene::setup()
{
    
    alpha = 0.0f ;
    fbo.allocate( getWidth() , getHeight(), GL_RGBA ) ;
    fbo.begin() ;
    ofClear( 1 , 1 , 1 , 0 ) ;
    fbo.end() ;
    
    string path = BaseScene::getDefaultShaderDirectory() ;

    shader.load( path +"basic.vert", path+"RippleTunnel.frag" ) ;
}


//--------------------------------------------------------------
void RippleTunnelScene::setupGui(float a_x, float a_y) {
    // creates new gui and adds the name to it //
    BaseScene::setupGui(a_x, a_y);
    
    float dim = 24;
	float xInit = OFX_UI_GLOBAL_WIDGET_SPACING;
    float length = 320-xInit;
    
    
    ofAddListener( gui->newGUIEvent, this, &RippleTunnelScene::guiEvent );
}

//--------------------------------------------------------------
void RippleTunnelScene::guiEvent(ofxUIEventArgs &e) {
    string name = e.widget->getName();
	int kind = e.widget->getKind();
    
 
    BaseScene::guiEvent( e ) ;
    

}

//--------------------------------------------------------------
void RippleTunnelScene::update() {
    
    BaseScene::update( ) ;

}

//--------------------------------------------------------------
void RippleTunnelScene::draw() {

    ofSetColor( 255 , 255 ,255 , alpha * 255.0f ) ;


    ofPushMatrix() ;
    fbo.begin() ;
    shader.begin();
    //we want to pass in some varrying values to animate our type / color
    shader.setUniform1f("time", ofGetElapsedTimef() );

    shader.setUniform2f("resolution",getWidth() , getHeight() );
    
    ofSetColor( 255 , 255 , 255 ) ;
    ofRect( 0 ,0, getWidth() , getHeight() ) ;
    shader.end() ;
    
    ofEnableBlendMode( OF_BLENDMODE_ADD ) ;
    ofSetColor( 255 , 255 , 255 , 120 ) ;
    // for ( int i = 0 ; i < 2 ; i++ )
    fbo.draw( 0 , 0 ) ;
    
    fbo.end() ;
    
    ofEnableAlphaBlending() ;
    ofSetColor( 255 , 255 , 255 , alpha * 255.0f );
    ofPushMatrix() ;
    fbo.draw( 0 , 0 ) ;
    ofPopMatrix( ) ;
    
	ofPopMatrix();

}


bool RippleTunnelScene::transitionIn( float delay , float transitionTime )
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

bool RippleTunnelScene::transitionOut( float delay , float transitionTime )
{
    if ( BaseScene::transitionOut( delay , transitionTime ) == false )
        return false ;
    else
    {
        Tweenzor::add( &alpha , alpha , 0.0f , delay , transitionTime ) ;
    }
    return true ;
}
