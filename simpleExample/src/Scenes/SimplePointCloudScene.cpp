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
void SimplePointCloudScene::activate() {
    
}

//--------------------------------------------------------------
void SimplePointCloudScene::deactivate() {
    
    // turn off the gui //
    BaseScene::deactivate();
}

//--------------------------------------------------------------
void SimplePointCloudScene::update() {
    kinectMan->update( );
}

//--------------------------------------------------------------
void SimplePointCloudScene::draw() {

    ofSetColor( 255 , 255 ,255 ) ;
  
    ofPushMatrix() ;
        cameraMan->begin();
        //Let's draw the point cloud
        int w = kinectMan->getWidth() ;
        int h = kinectMan->getHeight();
        ofMesh mesh;
        mesh.setMode( OF_PRIMITIVE_POINTS );
        int step = (int)pixelStep ;
        
        float _time = ofGetElapsedTimef() * zTimeMultiplier ;
        
        for(int y = 0; y < h; y += step)
        {
            for(int x = 0; x < w; x += step)
            {
                if( kinectMan->kinect.getDistanceAt(x, y) > 0)
                {
                    ofPoint vertex = kinectMan->getWorldCoordAt(x, y) ;
                    //only draw the points that are in range
                    if ( vertex.z > kinectMan->pointCloudMinZ && vertex.z < kinectMan->pointCloudMaxZ )
                    {
                        //Some generative always changing offsets here
                        float noiseZOffset = ofSignedNoise( _time + x , _time + y ) *  zNoiseAmount ;
                        vertex.z += noiseZOffset ;
                        
                        //Adjusting the color a bit makes sure that it can be seen on the dark background
                        ofColor pixelColor = kinectMan->kinect.getColorAt( x , y ) ; 
                        ofColor col = ofColor::fromHsb( pixelColor.getHue() , pixelColor.getSaturation() , kinectMan->minimumPixBrightness ) ;
                        mesh.addVertex( vertex );
                        mesh.addColor( col );
                    }
                }
            }
        }
        glPointSize(pointSize);
        
        
        ofPushMatrix();
            // the projected points are 'upside down' and 'backwards'
            ofScale( kinectMan->scale , -kinectMan->scale, -kinectMan->scale );
            ofTranslate( 0 , 0 , kinectMan->pointCloudZOffset ) ; 
            glEnable(GL_DEPTH_TEST);
            mesh.draw( );
            glDisable(GL_DEPTH_TEST);
        ofPopMatrix();

        cameraMan->end() ;
    ofPopMatrix();

}
