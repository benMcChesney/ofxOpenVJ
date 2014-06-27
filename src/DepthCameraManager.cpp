#include "DepthCameraManager.h"

DepthCameraManager::DepthCameraManager()
{

}
    
void DepthCameraManager::open( )
{

} 

void DepthCameraManager::close()
{

}

bool DepthCameraManager::isConnected()
{
	return false ; 
}
    
void DepthCameraManager::update()
{

}

void DepthCameraManager::draw()
{

}

void DepthCameraManager::drawDebug()
{ 

}
    
bool DepthCameraManager::isFrameNew()
{
	return false ; 
}


ofVec3f DepthCameraManager::getWorldCoordAt( int x, int y )
{
	return ofVec3f( ) ; 
}
    
ofColor DepthCameraManager::getColorAt( int x , int y ) 
{
	return ofColor::white ; 
}

void DepthCameraManager::calculateCVOperations()
{

}

void DepthCameraManager::calculatePointCloud()
{

}
    
void DepthCameraManager::guiEvent(ofxUIEventArgs &e)
{

}

void DepthCameraManager::setupGui(float a_x, float a_y)
{

}

void DepthCameraManager::loadSettings(){
}

void DepthCameraManager::saveSettings(){ 
}