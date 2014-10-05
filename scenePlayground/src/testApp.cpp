#include "testApp.h"

#define USE_KINECT 3
//--------------------------------------------------------------
void testApp::setup() {

    //Basic initialization of all components
    Tweenzor::init( ) ;
    
	ofBackground(255 );
	ofSetFrameRate(60);
	ofSetVerticalSync(true);
	ofSetEscapeQuitsApp(false);
    
    ofSetWindowTitle( "ofxOpenVJ Example" ) ; 
	ofEnableSmoothing();
	ofEnableAlphaBlending();
    
    ofSetSmoothLighting(true);
    
    //ofSetLogLevel(OF_LOG_SILENT);
    ofSetLogLevel(OF_LOG_WARNING ) ;
	
    int bufferSize = 512;
	ofSoundStreamSetup(0, 1, this, 44100, bufferSize, 4);
    
    set.initKinectV1( );
    set.setup() ;


    //set.addScene( new ColorOutlineScene((int)set.getNumScenes(), "ColorOutlineScene" ) ) ;
    set.addScene( new RippleTunnelScene((int)set.getNumScenes(), "RippleTunnelScene" ) ) ;
    set.addScene( new TriangleKinectScene((int)set.getNumScenes(), "TriangleKinectScene" ) ) ;
    set.addScene( new SimplePointCloudScene((int)set.getNumScenes(), "SimplePointCloudScene" ) ) ;
    set.addScene( new SimpleOpenCVScene((int)set.getNumScenes(), "SimpleOpenCVScene" ) ) ;
    set.addScene( new SimpleMaskScene((int)set.getNumScenes(), "SimpleMaskScene" ) ) ;
    set.addScene( new TronLines( (int)set.getNumScenes(), "TronLines" ) ) ;
    set.initialize() ; 
    
}
	
//--------------------------------------------------------------
void testApp::update()
{
    Tweenzor::update( ofGetElapsedTimeMillis() ) ; 
    set.update() ;
}

void testApp::draw( )
{
    set.draw( ) ; 
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){
    set.keyPressed( key ) ; 
}

//--------------------------------------------------------------
void testApp::exit()
{
    set.exit();
}

void testApp::audioReceived(float* input, int bufferSize, int nChannels)
{
    set.audioReceived( input , bufferSize, nChannels ) ;
}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){
	set.setSceneBounds( ) ;
}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){ 

}
