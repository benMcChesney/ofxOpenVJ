#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    Tweenzor::init( ) ;
    ofSetFrameRate(60 );
    ofBackground( 0 ) ; 
    set.setup() ;
    
    set.addScene( new Outline2dShatterScene(  set.getNumScenes() , "Outline2dShatterScene" ) ) ;
    
    set.initialize() ;
}

//--------------------------------------------------------------
void ofApp::update(){
    Tweenzor::update( ofGetElapsedTimeMillis() ) ;
    set.update() ;
}

//--------------------------------------------------------------
void ofApp::draw(){
   set.draw( ) ;
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    set.keyPressed( key ) ; 
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::exit( ) {
    set.exit( ) ; 
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
