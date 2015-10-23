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
	

	
	ofxOpenVJConstants::Instance()->colorPalette.addColor( ofColor( 64, 89, 82), "PURP" );
	ofxOpenVJConstants::Instance()->colorPalette.addColor(ofColor(156, 155, 122), "BRIGHT RED");
	ofxOpenVJConstants::Instance()->colorPalette.addColor(ofColor(255, 211, 147), "ORANGEY RED");
	ofxOpenVJConstants::Instance()->colorPalette.addColor(ofColor(255, 151, 79), "ORANGEY");
	ofxOpenVJConstants::Instance()->colorPalette.addColor(ofColor(245, 79, 41), "GREEN SLATE");
	//set.initKinectV1();
	set.setup( bufferSize );


	//set.addScene( new ColorOutlineScene((int)set.getNumScenes(), "ColorOutlineScene" ) ) ;
	//set.addScene(new RadialFftScene((int)set.getNumScenes(), "RadialFftScene"));
	//Intro
	set.addScene(new LightShaderScene((int)set.getNumScenes(), "LightShaderScene"));
	set.addScene(new CircleExpandScene((int)set.getNumScenes(), "CircleExpandScene"));
	set.addScene(new NeonLightTunnelScene((int)set.getNumScenes(), "NeonLightTunnelScene"));
	set.addScene(new AnimatedTileTextureScene((int)set.getNumScenes(), "Wave Tiles", "waves_gifs"));
	//texture tile for intro for build / fast beat 
	//HiRoller
	set.addScene(new MRSFractalShaderScene((int)set.getNumScenes(), "MRSFractalShaderScene"));
	set.addScene(new FractalTunnelScene((int)set.getNumScenes(), "FractalTunnelScene"));
	set.addScene(new SectionColorJumpScene((int)set.getNumScenes(), "SectionColorJumpScene")); 
	set.addScene(new AnimatedTileTextureScene((int)set.getNumScenes(), "Dance Tiles", "dance_gifs"));

	//Distant
	set.addScene(new NeuralSpaceShaderScene((int)set.getNumScenes(), "NeuralSpaceShaderScene"));
	set.addScene(new ReflectMaskScene((int)set.getNumScenes(), "ReflectMaskScene", "distant_images"));
	set.addScene(new AnimatedTileTextureScene((int)set.getNumScenes(), "Destroy Tiles", "destroy_gifs"));
	//reflectmask scene "distant" objects
	//then back into space
	//Tile TExture of... something ? kits / planes / things in the sky ?

	//with friends
	//animatedTileTexture driving / motion gifs
	set.addScene(new AnimatedTileTextureScene( (int)set.getNumScenes(), "Driving Tiles" , "driving_gifs" ));
	set.addScene(new GridMosiacFractalScene((int)set.getNumScenes(), "GridMosiacFractalScene"));
	set.addScene(new CellLifeShaderScene((int)set.getNumScenes(), "CellLifeShaderScene"));
	set.addScene(new IronManTunnelShaderScene((int)set.getNumScenes(), "IronManTunnelShaderScene"));
	
	//Solitaire
	//set.addScene(new ReflectMaskScene((int)set.getNumScenes(), "ReflectMaskScene" , "distant_images" ));
	//set.addScene(new AnimatedTileTextureScene(, "AnimatedTileTextureScene"));
//	((AnimatedTileTextureScene*)set.getSceneAt(set.getNumScenes() - 1))->loadContentFromFolder("animatedTileTextures"); 

	set.addScene(new TileTextureScene((int)set.getNumScenes(), "TileTextureScene"));
	
	//set.addScene(new SimpleScene((int)set.getNumScenes(), "SimpleScene"));
	

	//set.addScene(new TestScene((int)set.getNumScenes(), "Test Scene"));
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
