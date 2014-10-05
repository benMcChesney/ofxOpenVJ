//
//  TestScene.cpp
//  KinectPerformanceV01
//
//  Created by Ben McChesney on 11/6/12.
//
//

#include "Outline2dShatterScene.h"


static bool shouldRemove(ofPtr<ofxBox2dBaseShape>shape) {
    return true ; //!ofRectangle(0, -400, ofGetWidth(), ofGetHeight()+400).inside(shape.get()->getPosition());
}

//--------------------------------------------------------------
Outline2dShatterScene::Outline2dShatterScene() {
    //initialize all values
    startForce = 100.0f;
    decay = 0.5 ;
    currentForce = 0.0f ;
    smoothing = 1.0f ;
    tweenArgs = 0.0f;
    tweenLength = 2.0f ;
    flashAlpha = 0.0f ;
    flashTime = 0.4f ;
    fboFade = 1.0f ;
}

//--------------------------------------------------------------
Outline2dShatterScene::~Outline2dShatterScene() {
    
}

//--------------------------------------------------------------
void Outline2dShatterScene::setup() {
    
    //initialize all values
    startForce = 100.0f;
    decay = 0.5 ;
    currentForce = 0.0f ;
    smoothing = 1.0f ;
    tweenArgs = 0.0f;
    tweenLength = 2.0f ;
    flashAlpha = 0.0f ;
    flashTime = 0.4f ;
    fboFade = 1.0f ;

    //Box2d
    box2d.init();
	box2d.setGravity(0, 20);
	box2d.createGround();
	box2d.setFPS(30.0);
    
    bUseSet1 = true ;
    set1.addColor( ofColor( 249 , 155 , 63), ofToString( ColorPalette::Instance()->palette.size() ) ) ;
    set1.addColor( ofColor( 246 , 88 , 121), ofToString( ColorPalette::Instance()->palette.size() ) ) ;
    set1.addColor( ofColor( 247 , 205 , 109 ), ofToString( ColorPalette::Instance()->palette.size() ) ) ;
    
    set2.addColor( ofColor( 187 , 99 , 190), ofToString( ColorPalette::Instance()->palette.size() ) ) ;
    set2.addColor( ofColor( 92 , 242,  151), ofToString( ColorPalette::Instance()->palette.size() ) ) ;
    set2.addColor( ofColor( 175 , 200  , 112 ), ofToString( ColorPalette::Instance()->palette.size() ) ) ;
    bDoCreateShapes = false ;
    
    
    fbo.allocate( ofGetScreenWidth() , ofGetScreenHeight() , GL_RGBA32F_ARB ) ;
    fbo.begin() ;
    ofClear( 0 , 0 , 0 , 1 ) ;
    fbo.end() ;

}

void Outline2dShatterScene::upTweenComplete( float * args )
{
    Tweenzor::add( &tweenArgs , 0.0f , 1.0f , 0.0f , tweenLength , EASE_LINEAR );
    Tweenzor::addCompleteListener( Tweenzor::getTween( &tweenArgs ) , this , &Outline2dShatterScene::upTweenComplete ) ;
    
    if( kinectMan->contourFinder.nBlobs > 0 )
        bDoCreateShapes = true ;
    
    Tweenzor::add( &flashAlpha , maxFlash , 0.0f , 0.0f , flashTime , EASE_OUT_EXPO ) ;
    Tweenzor::add( &currentForce , startForce , 0.0f , 0.0f , decay , EASE_LINEAR ) ;
    
}

//--------------------------------------------------------------
void Outline2dShatterScene::setupGui(float a_x, float a_y)
{
    // creates new gui and adds the name to it //
    BaseScene::setupGui(a_x, a_y);
    
    startForce = 100.0f;
    decay = 0.5 ;
    currentForce = 0.0f ;
    smoothing = 1.0f ;
    tweenArgs = 0.0f;
    tweenLength = 2.0f ;
    flashAlpha = 0.0f ;
    flashTime = 0.4f ;
    fboFade = 1.0f ;

    gui->addLabel( "TIMING PARAMS" ) ; 
    gui->addSlider( "CYCLE TIME" , 1.0f, 10.0f ,&tweenLength ) ;
    gui->addSlider( "FLASH TIME" , 0.0001f , 0.45f , &flashTime ) ;
    gui->addSlider( "MAX FLASH" , 1.0f , 255.0f , &maxFlash ) ;
    gui->addSpacer() ;
    gui->addLabel("PARTICLE PARAMS" ) ; 
    gui->addSlider("DENSITY", 0.0f, 1.0f , &density ) ;
    gui->addSlider("BOUNCE" , 0.0f , 1.0f , &bounce ) ;
    gui->addSlider("FRICTION", 0.0f, 1.0f,  &friction ) ;
    gui->addSlider( "REPULSE DECAY" , 0.1f , 1.0f , &decay )  ;
    gui->addSlider( "REPULSE FORCE" , 0.1f , 1.0f , &startForce )  ;
    
    gui->addSpacer() ; 
    gui->addSlider("SMOOTHING", 0.0f , 12.0f , &smoothing ) ;
    gui->addSlider("FBO FADE", 0.0f , 255.0f , &fboFade ) ;
    
    ofAddListener( gui->newGUIEvent, this, &Outline2dShatterScene::guiEvent );
    loadSettings() ; 
}

//--------------------------------------------------------------
void Outline2dShatterScene::guiEvent(ofxUIEventArgs &e) {
    
    BaseScene::guiEvent( e ) ; 

 }

//--------------------------------------------------------------
void Outline2dShatterScene::activate() {
    
    //BaseScene::activate() ;
    Tweenzor::add( &tweenArgs , 0.0f , 1.0f , 0.0f , tweenLength , EASE_LINEAR );
    Tweenzor::addCompleteListener( Tweenzor::getTween( &tweenArgs ) , this , &Outline2dShatterScene::upTweenComplete ) ;
}

//--------------------------------------------------------------
void Outline2dShatterScene::deactivate() {
    
    // turn off the gui //
    BaseScene::deactivate();
    Tweenzor::removeCompleteListener(  Tweenzor::getTween( &tweenArgs )  ) ;
    Tweenzor::removeTween( &tweenArgs  ) ;
    
}

//--------------------------------------------------------------
void Outline2dShatterScene::update()
{
    box2d.update();
    kinectMan->calculateCVOperations() ;
    
    if ( bDoCreateShapes == true )
    {
        bDoCreateShapes = false ;
        ofxCvContourFinder * contourFinder = &kinectMan->contourFinder ;
        if ( contourFinder->blobs.size() > 0 )
        {
            ofRemove( polyShapes , shouldRemove ) ;
            polyColors.clear() ;
            
            int i = 0 ;
            shape.clear() ;
            for ( int p = 0  ; p < contourFinder->blobs[i].pts.size() ; p++ )
            {
                ofPoint pt = kinectMan->cvPointToScreen( contourFinder->blobs[i].pts[ p ] ) ;
                //pt.x = ofMap( pt.x , 0.0f , (float)kinectMan->getWidth() , 0.0f , (float)ofGetWidth() , true ) ;
                //pt.y = ofMap( pt.y , 0.0f , (float)kinectMan->getHeight() , 0.0f , (float)ofGetHeight() , true ) ;
                shape.addVertex( pt ) ;
            }
            
            forceOrigin = kinectMan->cvPointToScreen( contourFinder->blobs[0].centroid ) ;
            //forceOrigin.x = ofMap( forceOrigin.x , 0.0f , (float)kinectMan->getWidth() , 0.0f , (float)ofGetWidth() , true ) ;
            //forceOrigin.y = ofMap( forceOrigin.y , 0.0f , (float)kinectMan->getWidth() , 0.0f , (float)ofGetWidth() , true ) ;
            shape.simplify() ;
            
            // save the outline of the shape
            ofPolyline outline = shape;
            
            // resample shape
            ofPolyline resampled = shape.getResampledBySpacing(25);
            
            // trangleate the shape, return am array of traingles
            vector <TriangleShape> tris = triangulatePolygonWithOutline(resampled, outline);
            
            // add some random points inside
            //addRandomPointsInside(shape, 255);
            
            
            // now loop through all the trainles and make a box2d triangle
            ColorPalette * palette = &set2 ;
            if ( bUseSet1 )
                palette = &set1 ;
            
            bUseSet1 = !bUseSet1 ;
            
            for (int i=0; i<tris.size(); i++) {
                
                //vector <ofPtr<ofColor> >	polyColors ;
                
                ofPtr<ofxBox2dPolygon> triangle = ofPtr<ofxBox2dPolygon>(new ofxBox2dPolygon);
                triangle.get()->addTriangle(tris[i].a, tris[i].b, tris[i].c);
                //   void ofxBox2dBaseShape::setPhysics(float density, float bounce, float friction) {
                triangle.get()->setPhysics( density , bounce, friction ) ;
                triangle.get()->create(box2d.getWorld());
                
                polyShapes.push_back(triangle);
                polyColors.push_back( palette->getRandomColor() ) ;
                
            }
            
            ofPolyline smooth = outline.getSmoothed( smoothing ) ;
            path.clear() ;
            path.moveTo( smooth.getVertices()[0] ) ;
            for ( int i = 1 ; i < smooth.getVertices().size() ; i++ )
            {
                path.lineTo( smooth.getVertices()[i] )  ;
                //outline
            }
            
            path.close() ;
            
            
        }
        
    }
    
    for (int i=0; i<polyShapes.size(); i++)
    {
        //ofSetColor( polyColors[i] ) ;
		polyShapes[i].get()->addRepulsionForce( forceOrigin.x , forceOrigin.y , currentForce );
    }

}

//--------------------------------------------------------------
void Outline2dShatterScene::draw()
{
    ofSetColor(255, 255, 255);
	
    ofSetColor( 25 ) ;
    ofRect( 0 , ofGetHeight() - ( tweenArgs * ofGetHeight() ) , ofGetWidth() , tweenArgs * ofGetHeight() ) ;
    
    ofSetColor( 128 ) ;
    ofRect( 0 , ofGetHeight() - ( tweenArgs * ofGetHeight() ) , ofGetWidth() , 5 ) ;
    ofSetColor( 255 ) ;
    
    if ( tweenArgs < 0.5f )
        path.setFillColor( ofColor(255 , ( 1.0f - (tweenArgs * 2.0f) ) * 128  )) ;
    // ofSetHexColor(255 , ( 1.0f - tweenArgs ) * 255.0f );
	ofFill();
    path.draw( 0 , 0 ) ;
	
	//ofSetHexColor(0x444342);
	ofFill();
    
    fbo.begin() ;
    ofSetColor( 0 , fboFade ) ;
    ofRect( 0 , 0 , ofGetWidth() , ofGetHeight() ) ;
    
	for (int i=0; i<polyShapes.size(); i++)
    {
        ofSetColor( polyColors[i] ) ;
		polyShapes[i].get()->draw();
        ofCircle(polyShapes[i].get()->getPosition(), 3);
	}
    fbo.end() ;
    
    ofSetColor( 255 ) ;
    fbo.draw( 0  ,0 ) ;
    
    ofSetColor( 255 , flashAlpha ) ;
    ofRect(0 , 0, ofGetWidth() , ofGetHeight() ) ;
    
    ofSetColor( 255 ) ;
    ofRect( 0 , 0, ofGetWidth(), 2 ) ;
    
    //kinectMan->kinect.drawDepth( ofGetWidth() - 150 , 10 , 150, 112 );
    //kinectMan->contourFinder.draw( ofGetWidth() - 150 , 10 , 150, 112);

}
