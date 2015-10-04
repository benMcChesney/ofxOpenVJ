//
//  SoundManager.cpp
//  scenePlayground
//
//  Created by Ben McChesney on 9/7/14.
//
//
#include "CompositorManager.h"
#include "ofxOpenVJConstants.h"


void CompositorManager::setup ( )
{
	setupGui(); 
}

void CompositorManager::setupGui()
{
	ofxOpenVJConstants * c = ofxOpenVJConstants::Instance();  
	gui.setDefaultWidth( c->GUI_WIDGET_WIDTH ); 
	gui.setDefaultHeight( c->GUI_WIDGET_HEIGHT );
	
	gui.setup("Compositor Settings", "GUI/compositorManager.xml" );
	gui.setTextColor( ofColor( 128, 128, 128 ) ); 
	gui.add( channels.setup("RENDER CHANNELS", ofColor(255, 255, 255, 255), ofColor(0, 0, 0, 0), ofColor(255, 255, 255, 255) ) ) ;
	gui.setPosition( c->GUI_WIDGET_WIDTH * 2 , 0 );


}

void CompositorManager::update( )
{
	
}


void CompositorManager::drawScene( ofFbo * fbo , ofColor clearColor )
{
	ofPushStyle(); 
	
		ofSetColor(channels);
		fbo->draw(0, 0); 
	ofPopStyle(); 
}

