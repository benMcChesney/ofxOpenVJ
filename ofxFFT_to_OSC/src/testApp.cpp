#include "testApp.h"
#include "ofxXmlSettings.h"

//--------------------------------------------------------------
void testApp::setup(){

    
    ofBackground( 80 , 80 , 80 ) ;
    
	int bufferSize = 512;
	ofSoundStreamSetup(0, 1, this, 44100, bufferSize, 4);
    fftManager.setup ( ) ;
    fftManager.setupOfxUI() ; 
    ofSetFrameRate( 30 ) ; 
    
}

//--------------------------------------------------------------
void testApp::update(){
    fftManager.mouseX = mouseX ;
    fftManager.mouseY = mouseY ; 
    fftManager.update ( ) ;
    
}

//--------------------------------------------------------------
void testApp::draw(){
    fftManager.draw ( ) ;
}

void testApp::audioReceived(float* input, int bufferSize, int nChannels)
{
    fftManager.audioReceived( input , bufferSize , nChannels ) ;
}

void testApp::keyPressed  (int key)
{
 
}

void testApp::mouseDragged(int x, int y, int button)
{

}

void testApp::mousePressed(int x, int y, int button)
{

}

void testApp::mouseReleased(int x, int y, int button)
{

}


//--------------------------------------------------------------
void testApp::keyReleased(int key){
	
}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){
	
}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){
	
}
testApp::~testApp()
{
	fftManager.saveSettings();
}
