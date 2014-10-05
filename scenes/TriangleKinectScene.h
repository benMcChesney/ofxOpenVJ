//
//  TestScene.h
//  KinectPerformanceV01
//
//  Created by Ben Mcchesney on 11/6/12.
//
//

#pragma once 
#include "BaseScene.h"
#include "ofxTweenzor.h"

class TriangleKinectScene : public BaseScene {
public:
    TriangleKinectScene();
    TriangleKinectScene( int a_index, string a_name ):BaseScene( a_index, a_name ) {}
    ~TriangleKinectScene();
    
    void setup();
    void setupGui(float a_x=0, float a_y=0);
    void guiEvent(ofxUIEventArgs &e);

    void update();
    void draw();
    void drawPointCloud( ) ;
    
    float meshHueTimeMultiplier ;
    float meshHueRangeMin , meshHueRangeMax ;
    
    float triangleSizeMax ;
    float triangleSizeMin ;
    
    bool transitionIn( float delay , float transitionTime );
    bool transitionOut( float delay , float transitionTime ) ;
    
    float worldScale ;
    float alpha ; 
    

};
