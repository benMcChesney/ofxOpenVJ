#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

	//Basic initialization of all components
	Tweenzor::init();

	ofBackground(20);
	ofSetFrameRate(60);
	ofSetVerticalSync(true);
	ofSetEscapeQuitsApp(false);

	ofSetWindowTitle("ofxOpenVJ Example");
	ofEnableSmoothing();
	ofEnableAlphaBlending();

	ofSetSmoothLighting(true);

	//ofSetLogLevel(OF_LOG_SILENT);
	ofSetLogLevel(OF_LOG_WARNING);

	int bufferSize = 512;
	ofSoundStreamSetup(0, 1, this, 44100, bufferSize, 4);
	

	//set.initKinectV1();
	set.setup( bufferSize );


	//set.addScene( new ColorOutlineScene((int)set.getNumScenes(), "ColorOutlineScene" ) ) ;
	set.addScene(new SimpleScene((int)set.getNumScenes(), "Simple Scene"));
	set.addScene(new RippleTunnelScene((int)set.getNumScenes(), "RippleTunnelScene"));
	//set.addScene(new TriangleKinectScene((int)set.getNumScenes(), "TriangleKinectScene"));
	//set.addScene(new SimplePointCloudScene((int)set.getNumScenes(), "SimplePointCloudScene"));
	//set.addScene(new SimpleOpenCVScene((int)set.getNumScenes(), "SimpleOpenCVScene"));
	//set.addScene(new SimpleMaskScene((int)set.getNumScenes(), "SimpleMaskScene"));
	//set.addScene(new TronLines((int)set.getNumScenes(), "TronLines"));
	set.initialize();

}

//--------------------------------------------------------------
void ofApp::update(){
	Tweenzor::update(ofGetElapsedTimeMillis());
	set.update();
}

//--------------------------------------------------------------
void ofApp::draw(){
	set.draw();

	set.getSoundManager()->draw();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	set.draw();
}

void ofApp::audioReceived(float* input, int bufferSize, int nChannels)
{
	cout << " audio received !@" << endl;
	set.audioReceived(input, bufferSize, nChannels);
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

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
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

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
