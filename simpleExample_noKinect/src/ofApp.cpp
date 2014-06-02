#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetFrameRate( 60 ) ;
    ofBackground( 0 ) ;
    Tweenzor::init( ) ;
    
    set.setup() ;
    
    set.addScene( new TestScene( set.getNumScenes() , "TEST SCENE" ) ) ;
    set.addScene( new SimpleScene( set.getNumScenes() , "SIMPLE SCENE" ) ) ;
    
    set.initialize(); 
}

//--------------------------------------------------------------
void ofApp::update(){
    Tweenzor::update( ofGetElapsedTimeMillis() ) ;
    
    set.update() ;
}

//--------------------------------------------------------------
void ofApp::draw(){
    set.draw() ; 
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    set.keyPressed( key ) ; 
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
void ofApp::windowResized(int w, int h){
    set.setSceneBounds( ); 
}

void ofApp::exit( )
{
    set.exit() ; 
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
