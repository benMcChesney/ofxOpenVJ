#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	//Basic initialization of all components
    Tweenzor::init( ) ;
    
	ofBackground(255*.15);
	ofSetFrameRate(60);
	ofSetVerticalSync(true);
	ofSetEscapeQuitsApp(false);
    
    ofSetWindowTitle( "ofxOpenVJ Example" ) ; 
	ofEnableSmoothing();
	ofEnableAlphaBlending();
    
    ofSetSmoothLighting(true);
    
    //ofSetLogLevel(OF_LOG_SILENT);
    ofSetLogLevel(OF_LOG_VERBOSE ) ; 
	
    int bufferSize = 512;
	ofSoundStreamSetup(0, 1, this, 44100, bufferSize, 4);
    
    set.setup() ;
	set.initKinectV2() ; 
    set.addScene( new SimpleKinectV2Scene((int)set.getNumScenes(), "SimpleKinectV2Scene" ) ) ;
    
    set.initialize() ; 
    
}

void ofApp::audioReceived(float* input, int bufferSize, int nChannels)
{
    set.audioReceived( input , bufferSize, nChannels ) ;
}

//--------------------------------------------------------------
void ofApp::update(){
	set.update( ) ; 
}

//--------------------------------------------------------------
void ofApp::draw(){
	set.draw( ) ; 
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
	 set.keyPressed( key ) ; 
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}

void ofApp::exit( ) 
{
	set.exit();
}