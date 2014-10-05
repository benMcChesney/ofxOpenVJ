//
//  TestScene.cpp
//  KinectPerformanceV01
//
//  Created by Nick Hardeman on 11/6/12.
//
//

#include "TriangleKinectScene.h"

//--------------------------------------------------------------
TriangleKinectScene::TriangleKinectScene() {
    
}

//--------------------------------------------------------------
TriangleKinectScene::~TriangleKinectScene() {
    
}

//--------------------------------------------------------------
void TriangleKinectScene::setup() {
    
    meshHueTimeMultiplier = 0.0f ;
}

//--------------------------------------------------------------
void TriangleKinectScene::setupGui(float a_x, float a_y) {
    // creates new gui and adds the name to it //
    BaseScene::setupGui(a_x, a_y);
    
    gui->addLabel( name ) ;
    
    float dim = 24;
	float xInit = OFX_UI_GLOBAL_WIDGET_SPACING;
    float length = 320-xInit;
    
    int width = 300 ;
    int height = 18 ;
    
    gui->addSlider( "MESH TIME HUE MULTIPLIER" , 0.0f , 255.0f , meshHueTimeMultiplier , width, height) ;
    gui->addSlider( "TRIANGLE MAX" , 1.0 ,150.0f  , triangleSizeMax , width, height) ;
    gui->addSlider( "TRIANGLE MIN" , 1.0 ,150.0f  , triangleSizeMin , width, height) ;
    
    
    ofAddListener( gui->newGUIEvent, this, &TriangleKinectScene::guiEvent );
}

//--------------------------------------------------------------
void TriangleKinectScene::guiEvent(ofxUIEventArgs &e) {
    
    BaseScene::guiEvent( e ) ;
    string name = e.widget->getName();
	int kind = e.widget->getKind();
    
    if(name == "MESH TIME HUE MULTIPLIER" )
	{
		ofxUISlider *slider = (ofxUISlider *) e.widget;
        meshHueTimeMultiplier = slider->getScaledValue() ;
	}
    

    if (name ==  "TRIANGLE MAX" )
	{
		ofxUISlider *slider = (ofxUISlider *) e.widget;
        triangleSizeMax = slider->getScaledValue() ;
	}
    
    if (name == "TRIANGLE MIN" )
	{
		ofxUISlider *slider = (ofxUISlider *) e.widget;
        triangleSizeMin = slider->getScaledValue() ;
	}
}


//--------------------------------------------------------------
void TriangleKinectScene::update()
{
    BaseScene::update() ;
    depthCameraManager->update( );
	depthCameraManager->calculatePointCloud( ) ;
}

//--------------------------------------------------------------
void TriangleKinectScene::draw() {

   // ofBackground(0 ) ;
   // ofClear( 1 , 1 , 1 , 0 ) ;
    ofSetColor( 255 , 255 ,255 ) ;

    cameraManager->begin();
        ofPushMatrix() ;
            drawPointCloud();
        ofPopMatrix();
    cameraManager->end() ;
}

void TriangleKinectScene::drawPointCloud( )
{
    int w = 640;
	int h = 480;
	ofMesh mesh;
	mesh.setMode( OF_PRIMITIVE_TRIANGLES );
	int step = 3;
    //Get out hue offset
    int timeHue = ofGetElapsedTimef() * meshHueTimeMultiplier ;
    timeHue %= 255 ;
    
    ofColor hueOffset = ofColor::fromHsb( timeHue , 255.0f , 255.0f ) ;
	
    float _time = ofGetElapsedTimef() ; 
    float theta = sin ( ofGetElapsedTimef() ) ;
    
    //float center = ( pointCloudMinZ + pointCloudMaxZ ) / 2.0f ;
    
    int numTriangles = 0 ;
    ofPoint closestPoint = ofPoint ( 0 , 0 , 10000.0f ) ;
    
    for(int y = 0; y < h; y += step)
    {
		for(int x = 0; x < w; x += step)
        {

            float   noiseStep =  ofSignedNoise( _time + x ) ;
            float diff = soundManager->beatDetector.isLow()  ;
            
            ofVec3f vertex = depthCameraManager->getWorldCoordAt(x, y) ;
            if ( vertex.z > depthCameraManager->pointCloudMinZ && vertex.z < depthCameraManager->pointCloudMaxZ )
            {
                if ( vertex.z < closestPoint.z )
                    closestPoint = vertex ;
                float zOffset = noiseStep ;
                
                float index = x + y * h ;
                float offset = ofSignedNoise( ofGetElapsedTimef() + index ) ;
                if ( numTriangles % 2 == 0 )
                    offset *= -1 ; 
                
                float kinectHue = depthCameraManager->getColorAt( x , y ).getHue() ;
                float hue = ((int)(ofGetElapsedTimef() * meshHueTimeMultiplier )) % 255  + kinectHue ; 
                
                float zHueOffset = ofMap( vertex.z , depthCameraManager->pointCloudMinZ , depthCameraManager->pointCloudMaxZ ,  0 , 254.0f ) ;
                hue += zHueOffset ; 
                
                while ( hue > 254 )
                {
                    hue -= 255.0f ;
                }
            
                
                float size = ( 1.0 + diff ) * triangleSizeMax + triangleSizeMin ;
                
                ofColor _col = ofColor::fromHsb( hue , 255 , depthCameraManager->minimumPixBrightness , alpha * 255.0f ) ;
                ofVec3f _v = vertex ;
                _v.x -= size/2 ;
                _v.y -= size/2 ;
                mesh.addVertex( vertex );
                mesh.addColor( _col );

           
                vertex.x -= offset * size - size/2;
                vertex.y += offset * size - size/2;
                mesh.addVertex( vertex );
                mesh.addColor( _col );
                
                _v.x += offset * size - size/2 ;
                _v.y += offset * size - size/2 ;
                mesh.addVertex( _v );
                mesh.addColor( _col );

                numTriangles++ ;
            }
		}
	}
	glPointSize(3);
    
    
    ofPushMatrix();
    
    // the projected points are 'upside down' and 'backwards'
    ofEnableBlendMode(OF_BLENDMODE_ADD ) ;
    //ofScale(1, 1, -1 * worldScale );
    ofPushMatrix();
        ofScale( depthCameraManager->scale , -depthCameraManager->scale , -depthCameraManager->scale );
        ofTranslate( 0 , 0 , depthCameraManager->pointCloudZOffset ) ;
        glEnable(GL_DEPTH_TEST);
        mesh.draw( );
        glDisable(GL_DEPTH_TEST);
    ofPopMatrix();

}

bool TriangleKinectScene::transitionIn( float delay , float transitionTime )
{
    if ( BaseScene::transitionIn( delay , transitionTime ) == false )
        return false ;
    else
    {
        worldScale = 5.0f;
        alpha = 0.0f ;
        Tweenzor::add( &worldScale , 5.0f , 1.0f , delay , transitionTime ) ;
        Tweenzor::add( &alpha , 0.0f , 1.0f , delay , transitionTime ) ;
    }
    
    return true ;
}

bool TriangleKinectScene::transitionOut( float delay , float transitionTime )
{
    if ( BaseScene::transitionOut( delay , transitionTime ) == false )
        return false ;
    else
    {
        Tweenzor::add( &worldScale , 1.0f , 5.0f , delay , transitionTime ) ;
        Tweenzor::add( &alpha , 1.0f , 0.0f , delay , transitionTime ) ;
    }
    return true ;
}

