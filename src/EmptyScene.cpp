//
//  TestScene.cpp
//  KinectPerformanceV01
//
//  Created by Ben McChesney on 11/6/12.
//
//

#include "EmptyScene.h"

//--------------------------------------------------------------
EmptyScene::EmptyScene() {
    
}

//--------------------------------------------------------------
EmptyScene::~EmptyScene() {
    
}

//--------------------------------------------------------------
void EmptyScene::setup() {
    
}

//--------------------------------------------------------------
void EmptyScene::setupGui(float a_x, float a_y)
{
    // creates new gui and adds the name to it //
    BaseScene::setupGui(a_x, a_y);
    
   // ofAddListener( gui->newGUIEvent, this, &EmptyScene::guiEvent );
   // loadSettings() ; 
}

void EmptyScene::newBeatHandler()
{

}

//--------------------------------------------------------------
void EmptyScene::activate() {
    

}

//--------------------------------------------------------------
void EmptyScene::deactivate() {
    
    // turn off the gui //
    BaseScene::deactivate();
}

//--------------------------------------------------------------
void EmptyScene::update() {
}

//--------------------------------------------------------------
void EmptyScene::draw() {
}

void EmptyScene::drawDebug() {
}

bool EmptyScene::transitionIn(float delay, float transitionTime)
{

	if (BaseScene::transitionIn(delay, transitionTime) == false)
		return false;
	else
	{
		cout << "simple scene transitionin ! " << endl;
		//Build the scene out
		//Tweenzor::add(&drawNumCubes, 0.0f, (float)numCubes, delay, transitionTime, EASE_OUT_QUAD);
	}

	return true;
}

bool EmptyScene::transitionOut(float delay, float transitionTime)
{
	if (BaseScene::transitionOut(delay, transitionTime) == false)
		return false;
	else
	{
		//Tweenzor::add(&drawNumCubes, numCubes, 0.0f, delay, transitionTime, EASE_OUT_QUAD);
	}
	return true;
}
