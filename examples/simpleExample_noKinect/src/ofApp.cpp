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
	

	

	//set.initKinectV1();
	set.setup( bufferSize );


	//set.addScene( new ColorOutlineScene((int)set.getNumScenes(), "ColorOutlineScene" ) ) ;
	set.addScene(new SimpleScene((int)set.getNumScenes(), "Simple Scene"));
	set.addScene(new TestScene((int)set.getNumScenes(), "Test Scene"));
//	set.addScene(new RippleTunnelScene((int)set.getNumScenes(), "RippleTunnelScene"));
	//set.addScene(new TriangleKinectScene((int)set.getNumScenes(), "TriangleKinectScene"));
	//set.addScene(new SimplePointCloudScene((int)set.getNumScenes(), "SimplePointCloudScene"));
	//set.addScene(new SimpleOpenCVScene((int)set.getNumScenes(), "SimpleOpenCVScene"));
	//set.addScene(new SimpleMaskScene((int)set.getNumScenes(), "SimpleMaskScene"));
	//set.addScene(new TronLines((int)set.getNumScenes(), "TronLines"));
	set.initialize();

	ofSoundStreamSetup(0, 1, this, 44100, set.getSoundManager()->beatTracker.getBufferSize() , 4);

}

//--------------------------------------------------------------
void ofApp::update(){
	Tweenzor::update(ofGetElapsedTimeMillis());
	set.update();
	//beat.update(ofGetElapsedTimeMillis());
}

//--------------------------------------------------------------
void ofApp::draw(){
	set.draw();

	//ofBackground(0); 
	set.getSoundManager()->drawFFTBands(400, 400, 400, 200);
	drawFFTBands(400, 0, 400, 200);
}


void ofApp::drawFFTBands(float x, float y, float width, float height)
{
	ofPushMatrix();

	/*
	//HighHat / Snare / Kick + Space 
	float widthPerBand = width / ((float)(FFT_SUBBANDS + 4.0));

	ofEnableAlphaBlending();
	ofSetColor(255, 215);
	ofNoFill();
	ofSetLineWidth(2);
	ofRect(x, y, width, height);
	ofFill();
	ofSetLineWidth(1);

	int totalBands = (FFT_SUBBANDS + 4);

	int h = -height / 2.0f;
	//ofTranslate(0, height ); 
	for (int i = 0; i < FFT_SUBBANDS; i++)
	{

		ofRect(x + (i * widthPerBand), y + height, widthPerBand, beat.getBand(i) *h);
	}

	ofSetColor(255, 0, 0, 215);
	ofRect(x + ((FFT_SUBBANDS + 1)* widthPerBand), y + height, widthPerBand, beat.isKick() * h);
	ofDrawBitmapStringHighlight("K", x + (FFT_SUBBANDS + 1) * widthPerBand, y + height + 1);

	ofSetColor(0, 255, 0, 215);
	ofRect(x + ((FFT_SUBBANDS + 2) * widthPerBand), y + height, widthPerBand, beat.isSnare() * h);
	ofDrawBitmapStringHighlight("S", x + (FFT_SUBBANDS + 2) * widthPerBand, y + height + 1);

	ofSetColor(0, 0, 255, 215);
	ofRect(x + ((FFT_SUBBANDS + 3) * widthPerBand), y + height, widthPerBand, beat.isHat() * h);
	ofDrawBitmapStringHighlight("H", x + (FFT_SUBBANDS + 3) * widthPerBand, y + height + 1);

	ofPopMatrix();
	*/


}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	set.keyPressed(key); 
}



void ofApp::audioReceived(float* input, int bufferSize, int nChannels)
{
	set.audioReceived(input, bufferSize, nChannels);
	//beat.audioReceived(input, bufferSize, nChannels); 
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
