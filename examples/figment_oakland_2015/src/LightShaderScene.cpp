//
//  SimpleScene.cpp
//  simpleExample
//
//  Created by Ben McChesney on 5/15/14.
//
//

#include "LightShaderScene.h"

void LightShaderScene::setup()
{
	fbo.allocate(getWidth(), getHeight(), GL_RGBA);
	fbo.begin();
	ofClear(1, 1, 1, 0);
	fbo.end();

	string path = BaseScene::getDefaultShaderDirectory();

	cout << "attemping to load shaders.... " << endl; 
	loadShaders(); 

	cout << "after load shaders.... " << endl;
}

void LightShaderScene::setupGui(float a_x, float a_y)
{
    BaseScene::setupGui( a_x , a_y ) ;

	ofxOpenVJConstants *c = ofxOpenVJConstants::Instance(); 
	gui.add(lightIntensity.setup("LIGHT INTENSITY", 0.25f, 0.0f, 6.0f)); 
	gui.add(reloadShader.setup("RELOAD SHADER"));
	reloadShader.addListener(this, &LightShaderScene::loadShaders);
	/*
	gui.add(rectWidthSlider.setup("RECT WIDTH SLIDER", 150.0f, 50.0f, 400.0f));
	*/
	loadSettings();


}

void LightShaderScene::loadShaders()
{
	shader.load("Shaders/lightreveal.vert", "Shaders/lightreveal.frag");
}


void LightShaderScene::update()
{

	BaseScene::update();

}

void LightShaderScene::draw()
{
	ofSetColor(255); 
	ofPushMatrix();
		fbo.begin();
			shader.begin();
			//we want to pass in some varrying values to animate our type / color

		
			shader.setUniform1f("time", ofGetElapsedTimef());
			shader.setUniform1f("beat", soundManager->beatPerc );

			shader.setUniform2f("resolution", getWidth(), getHeight());
			shader.setUniform1f("low", soundManager->beatTracker.getBand(0));
			shader.setUniform1f("medium", soundManager->beatTracker.isSnare());
			shader.setUniform1f("high", soundManager->beatTracker.isHat()); 
			shader.setUniform1f("beatSin2", soundManager->bpmTapper.sin2);
			shader.setUniform1f("beatSin4", soundManager->bpmTapper.sin4);
			shader.setUniform1f("beatSin8", soundManager->bpmTapper.sin8);
			shader.setUniform1f("intensity", lightIntensity);
			
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



bool LightShaderScene::transitionIn( float delay , float transitionTime )
{
    
    if ( BaseScene::transitionIn( delay , transitionTime ) == false )
        return false ;
    else
    {
        cout << "simple scene transitionin ! " << endl ; 

    }

    return true ;
}

bool LightShaderScene::transitionOut( float delay , float transitionTime )
{
    if ( BaseScene::transitionOut( delay , transitionTime ) == false )
        return false ;
    else
    {
        
    }
    return true ;
}

void LightShaderScene::drawDebug( )
{
	sceneTransitionTimer.draw(50 , 50);
}

void LightShaderScene::activate()
{
    BaseScene::activate() ; 
}

void LightShaderScene::deactivate()
{
    BaseScene::deactivate() ; 
}
