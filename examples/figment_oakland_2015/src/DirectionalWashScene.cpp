//
//  SimpleScene.cpp
//  simpleExample
//
//  Created by Ben McChesney on 5/15/14.
//
//

#include "DirectionalWashScene.h"

void DirectionalWashScene::setup()
{

}

void DirectionalWashScene::setupGui(float a_x, float a_y)
{
    BaseScene::setupGui( a_x , a_y ) ;

	ofxOpenVJConstants *c = ofxOpenVJConstants::Instance(); 
	/*
	gui.add(rectWidthSlider.setup("RECT WIDTH SLIDER", 150.0f, 50.0f, 400.0f));
    loadSettings() ; 
	*/
	
}

void DirectionalWashScene::update()
{

	BaseScene::update();

}

void DirectionalWashScene::draw()
{
	
}



bool DirectionalWashScene::transitionIn( float delay , float transitionTime )
{
    
    if ( BaseScene::transitionIn( delay , transitionTime ) == false )
        return false ;
    else
    {
        cout << "simple scene transitionin ! " << endl ; 

    }

    return true ;
}

bool DirectionalWashScene::transitionOut( float delay , float transitionTime )
{
    if ( BaseScene::transitionOut( delay , transitionTime ) == false )
        return false ;
    else
    {
        
    }
    return true ;
}

void DirectionalWashScene::drawDebug( )
{
	sceneTransitionTimer.draw(50 , 50);
}

void DirectionalWashScene::activate()
{
    BaseScene::activate() ; 
}

void DirectionalWashScene::deactivate()
{
    BaseScene::deactivate() ; 
}
