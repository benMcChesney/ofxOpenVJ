//
//  NeonLightTunnelScene.cpp
//  NeonLightTunnelScene
//
//  Created by Ben McChesney on 5/15/14.
//
//

#include "CellLifeShaderScene.h"

void CellLifeShaderScene::setup()
{
	fbo.allocate(getWidth(), getHeight(), GL_RGBA);
	fbo.begin();
	ofClear(1, 1, 1, 0);
	fbo.end();

	string path = BaseScene::getDefaultShaderDirectory();
	loadShaders(); 
}

void CellLifeShaderScene::setupGui(float a_x, float a_y)
{
    BaseScene::setupGui( a_x , a_y ) ;

	ofxOpenVJConstants *c = ofxOpenVJConstants::Instance(); 
	gui.add( reloadShader.setup("RELOAD SHADER"));
	reloadShader.addListener(this, &CellLifeShaderScene::loadShaders );
	gui.add(cellScale.setup("CELL SIZE", 64., 2., 200.0)); 

	gui.add( maxCellScale.setup( "MAX CELL SIZE" , 64.0f , 0.2 , 200.0f )) ;
	gui.add(minCellScale.setup("MIN CELL SIZE", 64.0f, 0.2, 200.0f)); 

	gui.add(bBeatCellScale.setup("CELL BEAT SCALE", false));
	gui.add(colorMin.setup("COLOR MIN", 0.2f, 0.0f, 1.0f)); 
	/*
	gui.add(rectWidthSlider.setup("RECT WIDTH SLIDER", 150.0f, 50.0f, 400.0f));
	*/
    loadSettings() ; 
	
	
}

void CellLifeShaderScene::loadShaders()
{
	shader.load("Shaders/cellLifeShader.vert", "Shaders/cellLifeShader.frag");
}



void CellLifeShaderScene::update()
{

	BaseScene::update();

}

void CellLifeShaderScene::draw()
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
			shader.setUniform1f("colorMin", colorMin); 
			if ( !bBeatCellScale)
				shader.setUniform1f("cellScale", cellScale); 
			else
			{
				cellScale = ofMap(soundManager->beatPerc, 0.0f, 1.0f, minCellScale, maxCellScale, true); 
				shader.setUniform1f("cellScale", cellScale);
			}
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



bool CellLifeShaderScene::transitionIn( float delay , float transitionTime )
{
    
    if ( BaseScene::transitionIn( delay , transitionTime ) == false )
        return false ;
    else
    {
        cout << "simple scene transitionin ! " << endl ; 

    }

    return true ;
}

bool CellLifeShaderScene::transitionOut( float delay , float transitionTime )
{
    if ( BaseScene::transitionOut( delay , transitionTime ) == false )
        return false ;
    else
    {
        
    }
    return true ;
}

void CellLifeShaderScene::drawDebug( )
{
	sceneTransitionTimer.draw(50 , 50);
}

void CellLifeShaderScene::activate()
{
    BaseScene::activate() ; 
}

void CellLifeShaderScene::deactivate()
{
    BaseScene::deactivate() ; 
}
