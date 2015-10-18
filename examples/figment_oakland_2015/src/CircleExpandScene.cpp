//
//  SimpleScene.cpp
//  simpleExample
//
//  Created by Ben McChesney on 5/15/14.
//
//

#include "CircleExpandScene.h"

void CircleExpandScene::setup()
{

}

void CircleExpandScene::setupGui(float a_x, float a_y)
{
    BaseScene::setupGui( a_x , a_y ) ;

	ofxOpenVJConstants *c = ofxOpenVJConstants::Instance(); 
	/*
	gui.add(rectWidthSlider.setup("RECT WIDTH SLIDER", 150.0f, 50.0f, 400.0f));
    loadSettings() ; 
	*/
	
}

void CircleExpandScene::update()
{

	BaseScene::update();

}

void CircleExpandScene::draw()
{
	
}



bool CircleExpandScene::transitionIn( float delay , float transitionTime )
{
    
    if ( BaseScene::transitionIn( delay , transitionTime ) == false )
        return false ;
    else
    {
        cout << "simple scene transitionin ! " << endl ; 

    }

    return true ;
}

bool CircleExpandScene::transitionOut( float delay , float transitionTime )
{
    if ( BaseScene::transitionOut( delay , transitionTime ) == false )
        return false ;
    else
    {
        
    }
    return true ;
}

void CircleExpandScene::drawDebug( )
{
	sceneTransitionTimer.draw(50 , 50);
}

void CircleExpandScene::activate()
{
    BaseScene::activate() ; 
}

void CircleExpandScene::deactivate()
{
    BaseScene::deactivate() ; 
}
