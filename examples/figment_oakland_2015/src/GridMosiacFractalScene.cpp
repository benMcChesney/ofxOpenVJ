//
//  NeonLightTunnelScene.cpp
//  NeonLightTunnelScene
//
//  Created by Ben McChesney on 5/15/14.
//
//

#include "GridMosiacFractalScene.h"

void GridMosiacFractalScene::setup()
{
	fbo.allocate(getWidth(), getHeight(), GL_RGBA);
	fbo.begin();
	ofClear(1, 1, 1, 0);
	fbo.end();

	string path = BaseScene::getDefaultShaderDirectory();
	loadShaders(); 
}

void GridMosiacFractalScene::setupGui(float a_x, float a_y)
{
    BaseScene::setupGui( a_x , a_y ) ;

	ofxOpenVJConstants *c = ofxOpenVJConstants::Instance(); 
	gui.add( reloadShader.setup("RELOAD SHADER"));
	reloadShader.addListener(this, &GridMosiacFractalScene::loadShaders );
	/*
	gui.add(rectWidthSlider.setup("RECT WIDTH SLIDER", 150.0f, 50.0f, 400.0f));
	*/
    loadSettings() ; 
	
	
}

void GridMosiacFractalScene::loadShaders()
{
	shader.load("Shaders/gridMosiacFractal.vert", "Shaders/gridMosiacFractal.frag");
}



void GridMosiacFractalScene::update()
{

	BaseScene::update();

}

void GridMosiacFractalScene::draw()
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
			shader.setUniform1f("beatSin2", soundManager->bpmTapper.sin2);
			shader.setUniform1f("beatSin4", soundManager->bpmTapper.sin4);
			shader.setUniform1f("beatSin8", soundManager->bpmTapper.sin8);
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



bool GridMosiacFractalScene::transitionIn( float delay , float transitionTime )
{
    
    if ( BaseScene::transitionIn( delay , transitionTime ) == false )
        return false ;
    else
    {
        cout << "simple scene transitionin ! " << endl ; 

    }

    return true ;
}

bool GridMosiacFractalScene::transitionOut( float delay , float transitionTime )
{
    if ( BaseScene::transitionOut( delay , transitionTime ) == false )
        return false ;
    else
    {
        
    }
    return true ;
}

void GridMosiacFractalScene::drawDebug( )
{
	sceneTransitionTimer.draw(50 , 50);
}

void GridMosiacFractalScene::activate()
{
    BaseScene::activate() ; 
}

void GridMosiacFractalScene::deactivate()
{
    BaseScene::deactivate() ; 
}
