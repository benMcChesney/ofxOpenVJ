//
//  NeonLightTunnelScene.cpp
//  NeonLightTunnelScene
//
//  Created by Ben McChesney on 5/15/14.
//
//

#include "IronManTunnelShaderScene.h"

void IronManTunnelShaderScene::setup()
{
	fbo.allocate(getWidth(), getHeight(), GL_RGBA);
	fbo.begin();
	ofClear(1, 1, 1, 0);
	fbo.end();

	string path = BaseScene::getDefaultShaderDirectory();
	loadShaders(); 
}

void IronManTunnelShaderScene::setupGui(float a_x, float a_y)
{
    BaseScene::setupGui( a_x , a_y ) ;

	ofxOpenVJConstants *c = ofxOpenVJConstants::Instance(); 
	gui.add( reloadShader.setup("RELOAD SHADER"));
	reloadShader.addListener(this, &IronManTunnelShaderScene::loadShaders );


	gui.add( maxBrightness.setup( "MAX BRIGHTNESS" , 0.001 , 0.00001 , 1.0  ) ) ;
	gui.add(lowBrightnessFactor.setup("LOW BRIGHTNESS F", 0.01, 0.0001, 0.01));
	gui.add(beatJumpOffset.setup("BEAT JUMP OFFSET", 1.0f, 0.0f, 10.0f));
	gui.add(tunnelSpeed.setup("TUNNEL SPEED", 2.0, 0.0, 2.0 ));
	/*
	gui.add(rectWidthSlider.setup("RECT WIDTH SLIDER", 150.0f, 50.0f, 400.0f));
	*/
    loadSettings() ; 
	
	
}

void IronManTunnelShaderScene::loadShaders()
{
	shader.load("Shaders/ironManTunnel.vert", "Shaders/ironManTunnel.frag");
}



void IronManTunnelShaderScene::update()
{

	BaseScene::update();

}

void IronManTunnelShaderScene::draw()
{
	ofSetColor(255); 
	ofPushMatrix();
		fbo.begin();
			shader.begin();
		
			shader.setUniform1f("time", ofGetElapsedTimef());
			shader.setUniform1f("beat", soundManager->beatPerc );

			shader.setUniform2f("resolution", getWidth(), getHeight());
			shader.setUniform1f("low", soundManager->beatTracker.getBand(0));
			shader.setUniform1f("medium", soundManager->beatTracker.isSnare());
			shader.setUniform1f("high", soundManager->beatTracker.isHat()); 

			shader.setUniform1f("maxBrightness",  maxBrightness );
			shader.setUniform1f("lowBrightnessFactor", lowBrightnessFactor);
			shader.setUniform1f("tunnelSpeed", tunnelSpeed);
			shader.setUniform1f("beatJumpOffset", beatJumpOffset);
			
			ofSetColor(255);
			ofRect(0, 0, getWidth(), getHeight());
			shader.end();

		
			ofSetColor(255, 255, 255, 255); 
		fbo.draw(0, 0);

		fbo.end();

		ofEnableAlphaBlending();
		ofSetColor(255, 255, 255 );

		ofPushMatrix();
			ofSetColor(255, 255, 255, 255);
			fbo.draw(0, 0);
		ofPopMatrix();

	ofPopMatrix();
}



bool IronManTunnelShaderScene::transitionIn( float delay , float transitionTime )
{
    
    if ( BaseScene::transitionIn( delay , transitionTime ) == false )
        return false ;
    else
    {
        cout << "simple scene transitionin ! " << endl ; 

    }

    return true ;
}

bool IronManTunnelShaderScene::transitionOut( float delay , float transitionTime )
{
    if ( BaseScene::transitionOut( delay , transitionTime ) == false )
        return false ;
    else
    {
        
    }
    return true ;
}

void IronManTunnelShaderScene::drawDebug( )
{
	sceneTransitionTimer.draw(50 , 50);
}

void IronManTunnelShaderScene::activate()
{
    BaseScene::activate() ; 
}

void IronManTunnelShaderScene::deactivate()
{
    BaseScene::deactivate() ; 
}
