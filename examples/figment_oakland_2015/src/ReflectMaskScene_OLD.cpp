//
//  TestScene.cpp
//  KinectPerformanceV01
//
//  Created by Ben McChesney on 11/6/12.
//
//

#include "ReflectMaskScene.h"

//--------------------------------------------------------------
ReflectMaskScene::ReflectMaskScene() {
    
}

//--------------------------------------------------------------
ReflectMaskScene::~ReflectMaskScene() {
    
}

//--------------------------------------------------------------
void ReflectMaskScene::setup() {
    
}

//--------------------------------------------------------------
void ReflectMaskScene::setupGui(float a_x, float a_y)
{
    // creates new gui and adds the name to it //
    BaseScene::setupGui(a_x, a_y);

	gui.add(rectWidthSlider.setup("RECT WIDTH SLIDER", 50.0f , 5.0f , 125.0f));

   // ofAddListener( gui->newGUIEvent, this, &ReflectMaskScene::guiEvent );
   // loadSettings() ; 
}


//--------------------------------------------------------------
void ReflectMaskScene::activate() {
    

}

//--------------------------------------------------------------
void ReflectMaskScene::deactivate() {
    
    // turn off the gui //
    BaseScene::deactivate();
}

//--------------------------------------------------------------
void ReflectMaskScene::update() {
}

//--------------------------------------------------------------
void ReflectMaskScene::draw() {

	cout << "DRAW !! " << endl; 
	fbo.begin();
	ofSetColor(255, 0, 0); 
	ofRect(0, 0, ofGetWidth(), ofGetHeight()); 
	/*
	ofPushMatrix();

	ofSetRectMode(OF_RECTMODE_CENTER); 

	//ofTranslate(ofGetWidth() / 2, ofGetHeight() / 2); 
	//ofRotateZ( soundManager->beatPerc * 360 );

	int numRectangles = (ofGetWidth() * 1.5) / rectWidthSlider; 
	for (int i = 0; i < numRectangles; i++)
	{
		if (i % 2 == 0)
			ofSetColor(255, 255 , 255 , 255);
		else
			ofSetColor(0, 0, 0, 255); 
	
		float w = i * rectWidthSlider; 
		ofRect(0, 0, w , w ); 
	}


	ofSetRectMode(OF_RECTMODE_CORNER);

	ofPopMatrix(); 
	*/
	fbo.end(); 
}

void ReflectMaskScene::drawDebug() {
}

bool ReflectMaskScene::transitionIn(float delay, float transitionTime)
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

bool ReflectMaskScene::transitionOut(float delay, float transitionTime)
{
	if (BaseScene::transitionOut(delay, transitionTime) == false)
		return false;
	else
	{
		//Tweenzor::add(&drawNumCubes, numCubes, 0.0f, delay, transitionTime, EASE_OUT_QUAD);
	}
	return true;
}
