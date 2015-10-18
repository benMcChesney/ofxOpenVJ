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
    */

	gui.add(manualCreateShape.setup("CREATE SHAPE")); 
	gui.add(bRandomShape.setup("RANDOM SHAPES", false));
	gui.add(bSquareShape.setup("SQUARE SHAPES", false));
	gui.add(bDiamondShape.setup("DIAMOND SHAPES", false));
	gui.add(bTriangleShape.setup("TRIANGLE SHAPES", false));
	gui.add(bCircleShape.setup("CIRCLE SHAPES", false));
	
	manualCreateShape.addListener(this, &CircleExpandScene::manualCreateShapeListener);
		 
	loadSettings() ; 
	
	
}

void  CircleExpandScene::manualCreateShapeListener()
{
	Shape s = Shape(); // Shape(1.0f, 5.0f, ofColor(255), Shape::SQUARE);

	Shape::ShapeType st = s.getRandomShapeType();
	float r = ofGetWidth() / 2; 
	if (bRandomShape == true)
	{

	}

	if (bSquareShape)
	{
		st = Shape::SQUARE;
	}
	if (bDiamondShape)
	{
		st = Shape::DIAMOND;
	}

	if (bTriangleShape)
	{ 
		st = Shape::TRIANGLE;
	}

	if (bCircleShape)
	{
		st = Shape::CIRCLE;
	}

	float aspectRatio = 9.0f / 16.0f ;
	switch (st)
	{
		
		case Shape::SQUARE:
			r = ofGetWidth() ; 
			break;

		case Shape::CIRCLE:
			r = ( ofGetWidth() *.5 ) * aspectRatio ;
			break;

		case Shape::DIAMOND:
			r = (ofGetWidth() * 2.0f) * aspectRatio ; 
			break;

		case Shape::TRIANGLE:
			r = ofGetWidth() * 2.65 ; 
			break;
	}

	shapes.push_back(new Shape(1.0f, r , ofColor::fromHsb(ofGetFrameNum() % 255, 255, 255), st , soundManager->getSecondsFromBPM() ));

	int index = shapes.size() - 1;
	Tweenzor::add(&shapes[index]->radius, 1.0f, shapes[index]->maxRadius, 0.0f, soundManager->getSecondsFromBPM(), EASE_LINEAR);
	Tweenzor::addCompleteListener(Tweenzor::getTween(&shapes[index]->radius), shapes[index], &Shape::tweenCompleteHandler);
}

void CircleExpandScene::newBeatHandler()
{
	manualCreateShapeListener();
}

void CircleExpandScene::update( )
{

	BaseScene::update();
	for (auto shape = shapes.begin(); shape != shapes.end(); shape++)
	{
		if ((*shape)->bRemove == true)
		{
			delete (*shape); 
			shape = shapes.erase(shape); 
		}
	}
}

void CircleExpandScene::draw()
{
	ofPushMatrix(); 
	ofTranslate(ofGetWidth() / 2, ofGetHeight() / 2); 

	for (auto shape = shapes.begin(); shape != shapes.end(); shape++)
	{
		(*shape)->draw(); 
	}

	ofPopMatrix(); 
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
