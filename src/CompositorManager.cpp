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
	fbo.allocate(ofGetWidth(), ofGetHeight(), GL_RGBA); 
	fbo.begin(); 
		ofClear(0, 0, 0, 1); 
	fbo.end();

	glitch.setup(&fbo); 
	//ofxPostGlitch glitch  ; 
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

	
	glitches.push_back(new GlitchGuiMap("CONVERGENCE", OFXPOSTGLITCH_CONVERGENCE)); 
	glitches.push_back(new GlitchGuiMap("SHAKER", OFXPOSTGLITCH_SHAKER));
	glitches.push_back(new GlitchGuiMap("TWIST", OFXPOSTGLITCH_TWIST));
	
	for (auto fx = glitches.begin(); fx != glitches.end(); fx++)
	{
		gui.add((*fx)->toggle.setup( (*fx)->label , false )); 
	}

}

void CompositorManager::update( )
{
	
}


void CompositorManager::drawScene( ofFbo * sceneFbo , ofColor clearColor )
{
	ofPushStyle(); 
		ofSetColor( ofColor::white );
		sceneFbo->draw(0, 0);
	ofPopStyle(); 
}

void CompositorManager::beginDraw( )
{
	fbo.begin();
	ofClear(0, 0, 0, 1);
}

void CompositorManager::endDraw()
{
	fbo.end(); 

	ofPushStyle();
		ofSetColor( channels );
		glitch.generateFx(); 

		for (auto fx = glitches.begin(); fx != glitches.end(); fx++)
		{
			glitch.setFx( (*fx)->type, (*fx)->toggle ); 
		}

		fbo.draw(0, 0); 
	ofPopStyle();
}
