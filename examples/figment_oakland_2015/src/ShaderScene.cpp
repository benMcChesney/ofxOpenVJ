//
//  SimpleScene.cpp
//  simpleExample
//
//  Created by Ben McChesney on 5/15/14.
//
//

#include "ShaderScene.h"

void ShaderScene::setup()
{
	fbo.allocate(getWidth(), getHeight(), GL_RGBA);
	fbo.begin();
	ofClear(1, 1, 1, 0);
	fbo.end();

	string path = BaseScene::getDefaultShaderDirectory();

	cout << "attemping to load shaders.... " << endl; 
	shader.load("Shaders/lightreveal.vert", "Shaders/lightreveal.frag");

	cout << "after load shaders.... " << endl;
}

void ShaderScene::setupGui(float a_x, float a_y)
{
    BaseScene::setupGui( a_x , a_y ) ;

	ofxOpenVJConstants *c = ofxOpenVJConstants::Instance(); 

	
	/*
	gui.add(rectWidthSlider.setup("RECT WIDTH SLIDER", 150.0f, 50.0f, 400.0f));
    loadSettings() ; 
	*/
	
}

void ShaderScene::update()
{

	BaseScene::update();

}

void ShaderScene::draw()
{
	ofSetColor(255); 
	ofPushMatrix();
		fbo.begin();
			shader.begin();
			//we want to pass in some varrying values to animate our type / color

		
			shader.setUniform1f("time", ofGetElapsedTimef());
			shader.setUniform1f("beat", soundManager->beatPerc );

			shader.setUniform2f("resolution", getWidth(), getHeight());
			shader.setUniform1f("low", soundManager->beatTracker.isKick());
			shader.setUniform1f("medium", soundManager->beatTracker.isSnare());
			shader.setUniform1f("high", soundManager->beatTracker.isHat()); 

			ofSetColor(255, 255, 255);
			ofRect(0, 0, getWidth(), getHeight());
			shader.end();

		
		ofSetColor(255, 255, 255);
		// for ( int i = 0 ; i < 2 ; i++ )
		fbo.draw(0, 0);

		fbo.end();

		ofEnableAlphaBlending();
		ofSetColor(255, 255, 255 );

		ofPushMatrix();
		fbo.draw(0, 0);
		ofPopMatrix();

	ofPopMatrix();
}



bool ShaderScene::transitionIn( float delay , float transitionTime )
{
    
    if ( BaseScene::transitionIn( delay , transitionTime ) == false )
        return false ;
    else
    {
        cout << "simple scene transitionin ! " << endl ; 

    }

    return true ;
}

bool ShaderScene::transitionOut( float delay , float transitionTime )
{
    if ( BaseScene::transitionOut( delay , transitionTime ) == false )
        return false ;
    else
    {
        
    }
    return true ;
}

void ShaderScene::drawDebug( )
{
	sceneTransitionTimer.draw(50 , 50);
}

void ShaderScene::activate()
{
    BaseScene::activate() ; 
}

void ShaderScene::deactivate()
{
    BaseScene::deactivate() ; 
}
