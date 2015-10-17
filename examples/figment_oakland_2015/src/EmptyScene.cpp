//
//  SimpleScene.cpp
//  simpleExample
//
//  Created by Ben McChesney on 5/15/14.
//
//

#include "EmptyScene.h"

void EmptyScene::setup()
{

}

void EmptyScene::setupGui(float a_x, float a_y)
{
    BaseScene::setupGui( a_x , a_y ) ;

	ofxOpenVJConstants *c = ofxOpenVJConstants::Instance(); 
	/*
	gui.add(rectWidthSlider.setup("RECT WIDTH SLIDER", 150.0f, 50.0f, 400.0f));
    loadSettings() ; 
	*/
	
}

void EmptyScene::update()
{

	BaseScene::update();

}

void EmptyScene::draw()
{
	
}



bool EmptyScene::transitionIn( float delay , float transitionTime )
{
    
    if ( BaseScene::transitionIn( delay , transitionTime ) == false )
        return false ;
    else
    {
        cout << "simple scene transitionin ! " << endl ; 

    }

    return true ;
}

bool EmptyScene::transitionOut( float delay , float transitionTime )
{
    if ( BaseScene::transitionOut( delay , transitionTime ) == false )
        return false ;
    else
    {
        
    }
    return true ;
}

void EmptyScene::drawDebug( )
{
	sceneTransitionTimer.draw(50 , 50);
}

void EmptyScene::activate()
{
    BaseScene::activate() ; 
}

void EmptyScene::deactivate()
{
    BaseScene::deactivate() ; 
}
