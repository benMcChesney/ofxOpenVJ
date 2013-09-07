//
//  PCSDK_CV_Scene.h
//  ofxOpenVJ
//
//  Created by Ben McChesney on 6/6/12.
//
//


#include "PCSDK_CV_Scene.h"
//--------------------------------------------------------------
PCSDK_CV_Scene::PCSDK_CV_Scene() {
    
}

//--------------------------------------------------------------
PCSDK_CV_Scene::~PCSDK_CV_Scene() {
    
}

//--------------------------------------------------------------
void PCSDK_CV_Scene::setup() {
    
}

//--------------------------------------------------------------
void PCSDK_CV_Scene::setupGui(float a_x, float a_y) {
    // creates new gui and adds the name to it //
    BaseScene::setupGui(a_x, a_y);
    
    float dim = 24;
	float xInit = OFX_UI_GLOBAL_WIDGET_SPACING;
    float length = 320-xInit;
  
	int width = 300 ;
    int height = 18 ;
 
    ofAddListener( gui->newGUIEvent, this, &PCSDK_CV_Scene::guiEvent );
}

//--------------------------------------------------------------
void PCSDK_CV_Scene::guiEvent(ofxUIEventArgs &e) {
    string name = e.widget->getName();
	int kind = e.widget->getKind();
}

//--------------------------------------------------------------
void PCSDK_CV_Scene::activate() {
    
}

//--------------------------------------------------------------
void PCSDK_CV_Scene::deactivate() {
    
    // turn off the gui //
    BaseScene::deactivate();
}

//--------------------------------------------------------------
void PCSDK_CV_Scene::update() {
    depthCameraManager->update( );
	depthCameraManager->calculateCVOperations() ;
}

//--------------------------------------------------------------
void PCSDK_CV_Scene::draw() {


}

