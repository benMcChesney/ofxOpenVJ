#include "KinectV2Manager.h"


void KinectV2Manager::setup( ) 
{
	kinect.initSensor();
	kinect.initColorStream(true) ;
	kinect.initDepthStream(true) ;
	//kinect.initBodyIndexStream() ;
	//kinect.initSkeletonStream(true);

	//simple start
	kinect.start();

	grayImage.allocate(kinect.getDepthTexture().getWidth() , kinect.getDepthTexture().getHeight() );
	grayThreshNear.allocate(kinect.getDepthTexture().getWidth() , kinect.getDepthTexture().getHeight() );
	grayThreshFar.allocate(kinect.getDepthTexture().getWidth() , kinect.getDepthTexture().getHeight() ) ;
		cout << " kinect .getWidth()  ?" << kinect.getDepthTexture().getWidth() << endl ;

}

bool KinectV2Manager::isConnected()
{
	return true ; 
}

void KinectV2Manager::update( ) 
{
	kinect.update();
}

void KinectV2Manager::draw( ) 
{

	ofBackground(0, 255);
	
	kinect.draw(0,0);

	kinect.drawDepth(0, 0);
	kinect.drawBodyIndex(500, 0);
}

void KinectV2Manager::setupGui(float a_x, float a_y) 
{
    gui = new ofxUIScrollableCanvas( a_x, a_y, 320, ofGetHeight() + 300 - a_y );
    
    float GUI_WIDGET_WIDTH = 300;
    float GUI_SLIDER_HEIGHT = 16;
    
    gui->addWidgetDown(new ofxUILabel("Kinect Settings", OFX_UI_FONT_LARGE));
    gui->addSpacer(GUI_WIDGET_WIDTH, 2);

    gui->addWidgetDown( new ofxUIBaseDraws(128, 96, &kinect.getDepthTexture() , "Depth Texture") );
    


    gui->addWidgetRight( new ofxUIBaseDraws(128, 96, ((ofxCvGrayscaleImage*) &grayImage), "Open CV Texture") );
    
    gui->addWidgetDown( new ofxUIToggle("BTHRESH_WITH_CV", false, 16, 16) );
    gui->addWidgetDown( new ofxUIToggle("FIND HOLES", false, 16, 16) );
   
    gui->addRangeSlider("CLIPPING RANGE", 500.0, 4000.0f , 500.0, 4000.0f , GUI_WIDGET_WIDTH, GUI_SLIDER_HEIGHT);
   
    gui->addRangeSlider("ThreshSlider", 0.0, 7500.0, 50.0, 1000.0, GUI_WIDGET_WIDTH, GUI_SLIDER_HEIGHT);
    
    gui->addSlider("Kinect FOV", 1, 179, 70, GUI_WIDGET_WIDTH, GUI_SLIDER_HEIGHT);
    
    gui->addSpacer( GUI_WIDGET_WIDTH, 1);

    gui->addSlider("Mesh Step", 1, 20, 4, GUI_WIDGET_WIDTH, GUI_SLIDER_HEIGHT);
    
    gui->addRangeSlider("POINT CLOUD RANGE", 0.0 , 10000.0 , pointCloudMinZ , pointCloudMaxZ ) ;
    gui->addSlider("POINT CLOUD Z", -2000 , 2000 , 4, GUI_WIDGET_WIDTH, GUI_SLIDER_HEIGHT);

    
    gui->addSpacer( GUI_WIDGET_WIDTH, 1);
    gui->addWidgetDown(new ofxUILabel("INVERT AXES", OFX_UI_FONT_MEDIUM));
    gui->addWidgetDown( new ofxUILabelToggle("X AXIS", false, 90, 30, 0, 0) );
    gui->addWidgetRight( new ofxUILabelToggle("Y AXIS", false, 90, 30, 0, 0) );
  //  gui->addWidgetRight( new ofxUILabelToggle("Z AXIS", false, 90, 30, 0, 0) );
    
    gui->addWidgetDown(new ofxUIRotarySlider(64, -180.f, 180.f, 0.f, "Y AXIS ROT"));
	gui->addWidgetDown( new ofxUIRangeSlider( "BLOB SIZE" , 30 * 30 , ( kinect.getDepthTexture().getWidth() * kinect.getDepthTexture().getHeight() ) * .75 , minBlobSize , maxBlobSize ,  GUI_WIDGET_WIDTH, GUI_SLIDER_HEIGHT ) )  ;
    
    gui->addSlider( "MIN PIXEL BRIGHTNESS" , 0 , 255 , minimumPixBrightness , GUI_WIDGET_WIDTH , GUI_SLIDER_HEIGHT ) ;
    gui->addSpacer( GUI_WIDGET_WIDTH, 1);
  
    gui->setScrollArea(a_x, a_y, 320, ofGetHeight() - 10 - a_y);
    
    ofAddListener( gui->newGUIEvent, this, &KinectV2Manager::guiEvent );
}


//--------------------------------------------------------------
void KinectV2Manager::calculateCVOperations() {
    // make sure to only call this if isFrameNew() == true //
    //if(!kinect.isConnected()) return;
    
    // load grayscale depth image from the kinect source
	grayImage.setFromPixels(kinect.getDepthPixelsRef() ) ; //, kinect.width, kinect.height);
    
    if(inverseAxes.x == -1) {
        grayImage.mirror(false, true);
    }
    
    // we do two thresholds - one for the far plane and one for the near plane
    // we then do a cvAnd to get the pixels which are a union of the two thresholds
    
    grayThreshNear = grayImage;
    grayThreshFar = grayImage;
    grayThreshNear.threshold(nearThreshCV, true);
    grayThreshFar.threshold(farThreshCV);
    cvAnd(grayThreshNear.getCvImage(), grayThreshFar.getCvImage(), grayImage.getCvImage(), NULL);

    
    // update the cv images
    grayImage.flagImageChanged();
    
    // find contours which are between the size of 20 pixels and 1/3 the w*h pixels.
    // also, find holes is set to true so we will get interior contours as well....
//    findContours( ofxCvGrayscaleImage&  input,
//                 int minArea,
//                 int maxArea,
//                 int nConsidered,
//                 bool bFindHoles,
//                 bool bUseApproximation)
    
    
    contourFinder.findContours(grayImage, minBlobSize , maxBlobSize , maxBlobs , bFindHoles );
}

//--------------------------------------------------------------
void KinectV2Manager::guiEvent(ofxUIEventArgs &e) {
    string ename = e.widget->getName();
    
    if ( ename == "LOAD SETTINGS" && e.getButton()->getValue() == true )
        loadSettings() ;
    
    if ( ename == "SAVE SETTINGS" && e.getButton()->getValue() == true )
        saveSettings() ;
    
    if (e.widget->getName() == "Mesh Offset X") {
        ofxUISlider *slider = (ofxUISlider *) e.widget;
        offsetVec.x = slider->getScaledValue();
    } else if (e.widget->getName() == "Mesh Offset Y") {
        ofxUISlider *slider = (ofxUISlider *) e.widget;
        offsetVec.y = slider->getScaledValue();
    } else if (e.widget->getName() == "Mesh Offset Z") {
        ofxUISlider *slider = (ofxUISlider *) e.widget;
        offsetVec.z = slider->getScaledValue();
    } else if (e.widget->getName() == "Kinect FOV" ) {
        ofxUISlider* slider = (ofxUISlider*) e.widget;
        kinectFOV = slider->getScaledValue();
    }
    
	/*
	    gui->addRangeSlider("CLIPPING RANGE", 0.0, 10000.0f , 0, 10000.0f , GUI_WIDGET_WIDTH, GUI_SLIDER_HEIGHT);
    float nearClipping, farClipping;
	*/
    if(e.widget->getName() == "CLIPPING RANGE" ) 
	{
		
        ofxUIRangeSlider* slider = (ofxUIRangeSlider*) e.widget;
        float nearClip   = slider->getScaledValueLow();
        float farClip    = slider->getScaledValueHigh();
		cout << " RANFE IS NOW : " << nearClip << "< -> " << farClip << endl ; 
		kinect.setDepthClipping( nearClip , farClip ) ; 
    } else if (e.widget->getName() == "X AXIS" ) {
        ofxUILabelToggle* toggle = (ofxUILabelToggle*) e.widget;
        //cout << "invert x axis " << toggle->getValue() << endl;
        inverseAxes.x = toggle->getValue() == 1 ? -1 : 1;
    } else if (e.widget->getName() == "Y AXIS" ) {
        ofxUILabelToggle* toggle = (ofxUILabelToggle*) e.widget;
        //cout << "invert x axis " << toggle->getValue() << endl;
        inverseAxes.y = toggle->getValue() == 1 ? -1 : 1;
    } else if (e.widget->getName() == "Z AXIS" ) {
        ofxUILabelToggle* toggle = (ofxUILabelToggle*) e.widget;
        //cout << "invert x axis " << toggle->getValue() << endl;
        inverseAxes.z = toggle->getValue() == 1 ? -1 : 1;
    } else if (e.widget->getName() == "Mesh Step") {
        ofxUISlider* slider = (ofxUISlider*) e.widget;
        step = slider->getScaledValue();
    } else if (e.widget->getName() == "Y AXIS ROT" ) {
        ofxUIRotarySlider* slider = (ofxUIRotarySlider*) e.widget;
        axesRotation.y = slider->getScaledValue();
    } else if (ename == "DEPTH RANGE") {
        ofxUIRangeSlider* slider = (ofxUIRangeSlider*) e.widget;
        nearThreshCV    = 255-slider->getScaledValueLow();
        farThreshCV     = 255-slider->getScaledValueHigh();
    } else if (ename == "POINT CLOUD RANGE") {
        ofxUIRangeSlider* slider = (ofxUIRangeSlider*) e.widget;
        pointCloudMinZ    = slider->getScaledValueLow();
        pointCloudMaxZ     = slider->getScaledValueHigh();
    } else if (e.widget->getName() == "POINT CLOUD Z") {
        pointCloudZOffset = ((ofxUISlider *) e.widget)->getScaledValue() ;
    } else if (e.widget->getName() == "FIND HOLES")
    {
        ofxUILabelToggle* toggle = (ofxUILabelToggle*) e.widget;
        bFindHoles = toggle->getValue() ;
    } else if (e.widget->getName() == "BLOB SIZE" )
    {
       ofxUIRangeSlider* slider = (ofxUIRangeSlider*) e.widget;
        minBlobSize = slider->getScaledValueLow() ;
        maxBlobSize = slider->getScaledValueHigh() ; 
    } else if (e.widget->getName() == "MIN PIXEL BRIGHTNESS"  )
    {
        ofxUISlider* slider = (ofxUISlider*) e.widget;
        minimumPixBrightness = slider->getScaledValue() ;
    } else if ( e.getName() == "MAX BLOBS" )
        maxBlobs = (int)e.getSlider()->getScaledValue();
        //gui->addSlider("POINT CLOUD Z", -2000 , 2000 , 4, GUI_WIDGET_WIDTH, GUI_SLIDER_HEIGHT);
}