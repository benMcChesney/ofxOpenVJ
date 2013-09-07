//
//  PCSDK_Scene.h
//  ofxOpenVJ
//
//  Created by Ben McChesney on 6/5/12.
//
//



#include "PCSDK_Scene.h"
//--------------------------------------------------------------
PCSDK_Scene::PCSDK_Scene() {
    
}

//--------------------------------------------------------------
PCSDK_Scene::~PCSDK_Scene() {
    
}

//--------------------------------------------------------------
void PCSDK_Scene::setup() {
    
    meshHueTimeMultiplier = 0.0f ;
    bToggleTrails = false ;
    extrudeDepth = 100.0f ;
    extrudeNoiseStrength = 0.0f ;
    redrawAlpha = 0.0f ; 
    
    trailFbo.allocate( getWidth() , getHeight() , GL_RGBA ) ;
    trailFbo.begin() ;
    ofClear( 0 , 0, 0, 1 ) ;
    trailFbo.end() ; 
     string path = ofToDataPath( "../../../../ofxOpenVJ/shaders/" ) ;
    shader.load( path + "basic.vert", path + "PointCloud.frag" ) ;
}

//--------------------------------------------------------------
void PCSDK_Scene::setupGui(float a_x, float a_y) {
    // creates new gui and adds the name to it //
    BaseScene::setupGui(a_x, a_y);
    
    float dim = 24;
	float xInit = OFX_UI_GLOBAL_WIDGET_SPACING;
    float length = 320-xInit;
    
   // gui = new ofxUICanvas(0, 0, length+xInit, ofGetHeight());
  
    //gui->addWidgetDown(new ofxUIRangeSlider(length, dim, 0 , 10000 , pointCloudMinZ , pointCloudMaxZ, "POINT CLOUD Z RANGE")) ;
    int width = 300 ;
    int height = 18 ;
    
    gui->addSlider( "MESH TIME HUE MULTIPLIER" , 0.0f , 255.0f , meshHueTimeMultiplier , width, height) ;
    gui->addSlider( "FBO FADE AMOUNT" , 0.0f , 255.0f , fboFadeAmount, width, height) ;
    gui->addWidgetDown(new ofxUIToggle(dim, dim, bToggleTrails , "TOGGLE TRAILS")) ;

    gui->addSlider( "EXTRUDE DEPTH" , 0.0f , 10.0f , extrudeDepth , width, height) ;
    gui->addSlider( "EXTRUDE NOISE STRENGTH" , 0.0f , 500.0f , extrudeNoiseStrength , width, height) ;
    gui->addSlider( "TRIANGLE MAX" , 1.0 ,150.0f  , triangleSizeMax , width, height) ;
    gui->addSlider( "TRIANGLE MIN" , 1.0 ,150.0f  , triangleSizeMin , width, height) ;
      /*
    gui->addWidgetDown(new ofxUISlider(length, dim, 0.0f , 255.0f , meshHueTimeMultiplier , "MESH TIME HUE MULTIPLIER")) ;
    gui->addWidgetDown(new ofxUISlider(length, dim, 0.0f , 255.0f , fboFadeAmount , "FBO FADE AMOUNT")) ;
       gui->addWidgetDown(new ofxUISlider(length, dim, 0.0f , 10.0f , extrudeDepth , "EXTRUDE DEPTH")) ;
    gui->addWidgetDown(new ofxUISlider(length, dim, 0.0f , 500.0f , extrudeNoiseStrength , "EXTRUDE NOISE STRENGTH")) ;
    //gui->addWidgetDown(new ofxUISlider(length, dim, -2000.0f, 2000.0f , zOffset , "Z OFFSET")) ;
    gui->addWidgetDown(new ofxUISlider(length, dim, 1.0 ,150.0f  , triangleSizeMax , "TRIANGLE MAX")) ;
    gui->addWidgetDown(new ofxUISlider(length, dim, 1.0 ,150.0f  , triangleSizeMin , "TRIANGLE MIN")) ;
    */
    ofAddListener( gui->newGUIEvent, this, &PCSDK_Scene::guiEvent );
}

//--------------------------------------------------------------
void PCSDK_Scene::guiEvent(ofxUIEventArgs &e) {
    string name = e.widget->getName();
	int kind = e.widget->getKind();
    
    if(name == "MESH TIME HUE MULTIPLIER" )
	{
		ofxUISlider *slider = (ofxUISlider *) e.widget;
        meshHueTimeMultiplier = slider->getScaledValue() ;
	}
    
    if(name == "FBO FADE AMOUNT" )
	{
		ofxUISlider *slider = (ofxUISlider *) e.widget;
        fboFadeAmount = slider->getScaledValue() ;
	}
    
    if ( name == "TOGGLE TRAILS")
    {
        ofxUIToggle *toggle = (ofxUIToggle *) e.widget;
        bToggleTrails = toggle->getValue() ;
    }
    
    if (name == "EXTRUDE DEPTH" )
	{
		ofxUISlider *slider = (ofxUISlider *) e.widget;
        extrudeDepth = slider->getScaledValue() ;
	}
    
    if (name == "EXTRUDE NOISE STRENGTH" )
	{
		ofxUISlider *slider = (ofxUISlider *) e.widget;
        extrudeNoiseStrength = slider->getScaledValue() ;
	}
  
    if (name == "PC Z" )
	{
		ofxUISlider *slider = (ofxUISlider *) e.widget;
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
void PCSDK_Scene::activate() {
    
}

//--------------------------------------------------------------
void PCSDK_Scene::deactivate() {
    
    // turn off the gui //
    BaseScene::deactivate();
}

//--------------------------------------------------------------
void PCSDK_Scene::update() {
    depthCameraManager->update( );
	depthCameraManager->calculatePointCloud( ) ; 
}

//--------------------------------------------------------------
void PCSDK_Scene::draw() {
    
    ofSetColor( 255 , 255 ,255 ) ;
  
    cameraMan->begin();
    ofPushMatrix() ;
    ofTranslate(0 , 0 , cameraMan->zOffset ) ;
		drawPointCloud( ) ; 
	ofPopMatrix();

    cameraMan->end() ; 
}

void PCSDK_Scene::drawPointCloud( )
{
    int w = depthCameraManager->getWidth() ; 
	int h = depthCameraManager->getHeight() ; 

	ofMesh mesh;
	mesh.setMode( OF_PRIMITIVE_TRIANGLES );
	//int step = 3;
    //Get out hue offset
    int timeHue = ofGetElapsedTimef() * meshHueTimeMultiplier ;
    timeHue %= 255 ;
    
    ofColor hueOffset = ofColor::fromHsb( timeHue , 255.0f , 255.0f ) ;
	
    float _time = ofGetElapsedTimef() ; 
    float theta = sin ( ofGetElapsedTimef() ) ;
    
    //float center = ( pointCloudMinZ + pointCloudMaxZ ) / 2.0f ;
    
    int numTriangles = 0 ;
    ofPoint closestPoint = ofPoint ( 0 , 0 , 10000.0f ) ;
    
	for(int y = 0; y < h; y+= depthCameraManager->step ) //= pcsdkMan->step )
    {
		for(int x = 0; x < w; x+= depthCameraManager->step ) //= pcsdkMan->step )
        {
			
            float   noiseStep = 0 + ofSignedNoise( _time + x )*  extrudeNoiseStrength * extrudeDepth ;             
            float diff = low ; 
            
			//if( pcsdkMan->getDistanceAt(x, y) > 0)
           // {
                ofVec3f vertex = depthCameraManager->getWorldCoordAt(x,y) ;

                if ( vertex.z > depthCameraManager->pointCloudMinZ && vertex.z < depthCameraManager->pointCloudMaxZ )
                {
                //    if ( vertex.z < closestPoint.z )
                //        closestPoint = vertex ;
                    float zOffset = noiseStep ;
                   // vertex.z += zOffset ;
                    
                    float index = x + y * h ;
                    float offset = ofSignedNoise( ofGetElapsedTimef() + index ) * ( low * 10.0f ) ;  ;
                    if ( numTriangles % 2 == 0 )
                        offset *= -1 ; 
                    
                    offset *= low ;
                    
                    float kinectHue = depthCameraManager->getColorAt( x , y ).getHue() ;
                    //float ofMap(float value, float inputMin, float inputMax, float outputMin, float outputMax, bool clamp) {
                    float hue = ((int)(ofGetElapsedTimef() * meshHueTimeMultiplier )) % 255  + kinectHue ; 
                    
                    float zHueOffset = ofMap( vertex.z , depthCameraManager->pointCloudMinZ , depthCameraManager->pointCloudMaxZ ,  0 , 254.0f ) ;
                    hue += zHueOffset ; 
                    
                    while ( hue > 254 )
                    {
                        hue -= 255.0f ;
                    }
                
                    
//                    unsigned char _b = _col.getBrightness() ;
                    //ofColor col = ofColor::fromHsb( hue  , _col.getSaturation() ,  _b  ) ;
                  //  if ( _b < kinectMan->minimumPixBrightness )
                  //      _col.setBrightness( kinectMan->minimumPixBrightness ) ;
                   
                    //_col.setHue( zHueOffset ) ;
                    //_col.setSaturation( 255 ) ;
                    
                    ofColor _col = ofColor::fromHsb( hue , 255 , 250 ) ; //pcsdkMan->minimumPixBrightness ) ;
                    //cout << "hue : " << hue << endl ;
                    ofVec3f _v = vertex ;
                    mesh.addVertex( vertex );
                    mesh.addColor( _col );

               
                    vertex.x -= offset * ( 1.0 + diff ) * triangleSizeMax + triangleSizeMin ;
                    vertex.y += offset * ( 1.0f + diff  ) * triangleSizeMax + triangleSizeMin ;
                    mesh.addVertex( vertex );
                    mesh.addColor( _col );
                    
                    _v.x += offset * ( 1.0 + diff ) * triangleSizeMax + triangleSizeMin ;
                    _v.y += offset * ( 1.0f + diff ) * triangleSizeMax + triangleSizeMin ;
                    mesh.addVertex( _v );
                    mesh.addColor( _col );

                    numTriangles++ ;
              }
			//}
		}
	}
	//glPointSize(5);
    
    
    ofPushMatrix();
    
    // the projected points are 'upside down' and 'backwards'
    ofEnableBlendMode( OF_BLENDMODE_ADD ) ; 
    ofScale(1, -1, -1 * depthCameraManager->zScale );
        //ofTranslate( 0.0f , 0.0f , zOffset ) ;
        glEnable(GL_DEPTH_TEST);
		
        mesh.draw( );
        glDisable(GL_DEPTH_TEST);
    ofPopMatrix();

}
