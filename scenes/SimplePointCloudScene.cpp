//
//  TestScene.cpp
//  KinectPerformanceV01
//
//  Created by Ben McChesney on 11/6/12.
//
//

#include "SimplePointCloudScene.h"

//--------------------------------------------------------------
SimplePointCloudScene::SimplePointCloudScene() {
    
}

//--------------------------------------------------------------
SimplePointCloudScene::~SimplePointCloudScene() {
    
}

//--------------------------------------------------------------
void SimplePointCloudScene::setup() {
    worldScale = 1.0f ;
    alpha = 255.0f ;
}

//--------------------------------------------------------------
void SimplePointCloudScene::setupGui(float a_x, float a_y) {
    // creates new gui and adds the name to it //
    BaseScene::setupGui(a_x, a_y);

    gui->addSlider("Z TIME MULTIPLIER", 0.1f , 5.0f , &zTimeMultiplier ) ;
    gui->addSlider("Z NOISE AMOUNT", 0.0f , 50.0f , &zNoiseAmount ) ;
    gui->addSlider("PIXEL STEP" , 1.0f , 6.0f , &pixelStep ) ;
    gui->addSlider("POINT SIZE" , 1.0f , 10.0f , &pointSize ) ;
    ofAddListener( gui->newGUIEvent, this, &SimplePointCloudScene::guiEvent );
    loadSettings() ; 
}

//--------------------------------------------------------------
void SimplePointCloudScene::guiEvent(ofxUIEventArgs &e) {
    
    BaseScene::guiEvent( e ) ; 

 }

//--------------------------------------------------------------
void SimplePointCloudScene::update() {
    BaseScene::update( ) ; 
    depthCameraManager->update( );
    
}

//--------------------------------------------------------------
void SimplePointCloudScene::draw() {

    
    if ( !depthCameraManager->isConnected() )
        return ;
    
    ofSetColor( 255 , 255 ,255 ) ;

    ofPushMatrix() ;
        cameraManager->begin();
    
        //Let's draw the point cloud
        int w = depthCameraManager->getWidth() ;
        int h = depthCameraManager->getHeight();
        ofMesh mesh;
        mesh.setMode( OF_PRIMITIVE_POINTS );
        int step = (int)pixelStep ;
        
        float _time = ofGetElapsedTimef() * zTimeMultiplier ;
        
        for(int y = 0; y < h; y += step)
        {
            for(int x = 0; x < w; x += step)
            {
                ofPoint vertex = depthCameraManager->getWorldCoordAt(x, y) ;
                if( vertex.z > 0 )
                {
                    //only draw the points that are in range
                    if ( vertex.z > depthCameraManager->pointCloudMinZ && vertex.z < depthCameraManager->pointCloudMaxZ )
                    {
                        //Some generative always changing offsets here
                        float noiseZOffset = ofSignedNoise( _time + x , _time + y ) *  zNoiseAmount ;
                        vertex.z += noiseZOffset ;
                        
                        //Adjusting the color a bit makes sure that it can be seen on the dark background
                        ofColor pixelColor = depthCameraManager->getColorAt( x , y ) ; 
                        ofColor col = ofColor::fromHsb( pixelColor.getHue() , pixelColor.getSaturation() , depthCameraManager->minimumPixBrightness ) ;
                        col.a = alpha ; 
                        mesh.addVertex( vertex );
                        mesh.addColor( col );
                    }
                }
            }
        }
        glPointSize(pointSize);
        
        
        ofPushMatrix();
            // the projected points are 'upside down' and 'backwards'
            ofScale( depthCameraManager->scale * worldScale , -depthCameraManager->scale * worldScale , -depthCameraManager->scale * worldScale );
            ofTranslate( 0 , 0 , depthCameraManager->pointCloudZOffset ) ; 
            glEnable(GL_DEPTH_TEST);
            mesh.draw( );
            glDisable(GL_DEPTH_TEST);
        ofPopMatrix();

        cameraManager->end() ;
    ofPopMatrix();

}




bool SimplePointCloudScene::transitionIn( float delay , float transitionTime )
{
    
    if ( BaseScene::transitionIn( delay , transitionTime ) == false )
        return false ;
    else
    {
        cout << name << " transitionin ! " << endl ;
        worldScale = 20.0f ;
        //Build the scene out
        Tweenzor::add( &alpha , 0.0f , 255.0f , delay , transitionTime , EASE_OUT_QUAD ) ;
        Tweenzor::add( &worldScale, worldScale , 1.0f , delay, transitionTime, EASE_OUT_QUAD ) ; 
    }
    
    return true ;
}

bool SimplePointCloudScene::transitionOut( float delay , float transitionTime )
{
    if ( BaseScene::transitionOut( delay , transitionTime ) == false )
        return false ;
    else
    {
        Tweenzor::add( &alpha , alpha , 0.0f , delay , transitionTime , EASE_OUT_QUAD ) ;
        Tweenzor::add( &worldScale, worldScale , 20.0f , delay, transitionTime, EASE_OUT_QUAD ) ;
    }
    return true ;
}

