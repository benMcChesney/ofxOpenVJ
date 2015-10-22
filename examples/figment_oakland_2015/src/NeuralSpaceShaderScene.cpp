//
//  SimpleScene.cpp
//  simpleExample
//
//  Created by Ben McChesney on 5/15/14.
//
//

#include "NeuralSpaceShaderScene.h"

void NeuralSpaceShaderScene::setup()
{
	fbo.allocate(getWidth(), getHeight(), GL_RGBA);
	fbo.begin();
	ofClear(1, 1, 1, 0);
	fbo.end();

	string path = BaseScene::getDefaultShaderDirectory();

	cout << "attemping to load shaders.... " << endl; 
	reloadShaderHandler(); 
	setupCompositor(); 
	cout << "after load shaders.... " << endl;
}

void NeuralSpaceShaderScene::setupGui(float a_x, float a_y)
{
    BaseScene::setupGui( a_x , a_y ) ;

	ofxOpenVJConstants *c = ofxOpenVJConstants::Instance(); 

	gui.add(spaceMovement.setup("SPACE MOVEMENT", 25.0, 0.0, 40.0)); 
	gui.add(reloadShader.setup("RELOAD SHADER")); 
	gui.add( flowAmount.setup("FLOW AMOUNT", 0.0005, 0.0005, 0.005)); 

	reloadShader.addListener(this, &NeuralSpaceShaderScene::reloadShaderHandler); 
	/*
	gui.add(rectWidthSlider.setup("RECT WIDTH SLIDER", 150.0f, 50.0f, 400.0f));
    loadSettings() ; 
	*/
}


void NeuralSpaceShaderScene::reloadShaderHandler()
{
	shader.load("Shaders/neuralSpace.vert", "Shaders/neuralSpace.frag");
}

void NeuralSpaceShaderScene::update()
{

	BaseScene::update();

}

void NeuralSpaceShaderScene::draw()
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
			shader.setUniform1f("spaceMovement", spaceMovement );
			
			shader.setUniform1f("beatSin2", soundManager->bpmTapper.sin2);
			shader.setUniform1f("beatSin4", soundManager->bpmTapper.sin4);
			shader.setUniform1f("beatSin8", soundManager->bpmTapper.sin8);
			shader.setUniform1f("flowAmount", flowAmount);
			
			
			
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



bool NeuralSpaceShaderScene::transitionIn( float delay , float transitionTime )
{
    
    if ( BaseScene::transitionIn( delay , transitionTime ) == false )
        return false ;
    else
    {
        cout << "simple scene transitionin ! " << endl ; 

    }

    return true ;
}

bool NeuralSpaceShaderScene::transitionOut( float delay , float transitionTime )
{
    if ( BaseScene::transitionOut( delay , transitionTime ) == false )
        return false ;
    else
    {
        
    }
    return true ;
}

void NeuralSpaceShaderScene::drawDebug( )
{
	sceneTransitionTimer.draw(50 , 50);
}

void NeuralSpaceShaderScene::activate()
{
    BaseScene::activate() ; 
}

void NeuralSpaceShaderScene::deactivate()
{
    BaseScene::deactivate() ; 
}
