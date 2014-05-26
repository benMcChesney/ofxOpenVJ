#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup() {

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
    
    // init reference vars before gui gets them //
    bDrawGui    = false;
    bAutoSceneSwitch = false;
    bKinectCamGui = true;
    activeSceneIndex = 0;

    lastSceneChangedTime = 0.0f ;
    sceneDelayTime = 5.0f ;

    beatDetector.enableBeatDetect() ;
    beatDetector.setBeatValue( 120 ) ; 
    float guiY = 0 ;
    gui = new ofxUICanvas( 10, guiY, 320, ofGetHeight() - guiY - 10 );
    setupMainGui();
    gui->loadSettings("GUI/mainGuiSettings.xml");
    gui->setVisible( bDrawGui );
   
    //A few ifdefs to make sure there's not a gap in the GUIs
    float guiX = 340 ; 
#ifdef USE_KINECT
    // KinectManager //
    kinectMan.setupGui(guiX, guiY);
    kinectMan.close();
    kinectMan.open();
    kinectMan.loadSettings();
    kinectMan.gui->setVisible(bDrawGui);
    guiX = 670 ; 
#endif
    
    cameraManager.setup();
    cameraManager.setupGui( guiX , guiY);
    cameraManager.loadSettings();
    cameraManager.gui->setVisible( false );
    
#ifndef USE_KINECT
    guiX = 670 ; 
#endif
    //Add a new scene in one line of code
    scenes.push_back( new SimpleScene((int)scenes.size(), "SimpleScene" ) ) ;
    scenes.push_back( new TestScene((int)scenes.size(), "TestScene" ) ) ;
    //scenes.push_back( new TriangleKinectShader((int)scenes.size(), "TriangleKinectShader" ) ) ;
    setSceneBounds();
    
    for(int i = 0; i < scenes.size(); i++) {
        Scenes::registerScene(scenes[i]->index, scenes[i]->name);
#ifdef USE_KINECT
        scenes[i]->kinectMan        = &kinectMan;
#endif
        scenes[i]->beatDetector     = &beatDetector;
        scenes[i]->cameraMan        = &cameraManager;
        scenes[i]->setup();
        scenes[i]->setupGui(guiX, guiY);
        scenes[i]->loadSettings();
        scenes[i]->deactivate();
    }
    
    Scenes::toString();
    
    setSceneBounds();
    setDrawGuis( true );
    // activate the first scene //
    scenes[activeSceneIndex]->activate();

#ifdef USE_SYPHON
    outputSyphonServer.setName( "ofxOpenVJ" ) ;
#endif

    
}

//--------------------------------------------------------------
void testApp::exit() {
    bool bAutoSave = ((ofxUIToggle*)gui->getWidget("B_AUTO_SAVE"))->getValue();
    
    for(int i = 0; i < scenes.size(); i++ ) {
        if(bAutoSave) scenes[i]->saveSettings();
        delete scenes[i];
        scenes[i] = NULL;
    }
    scenes.clear();
    
    if(bAutoSave) {
        gui->saveSettings( "GUI/mainGuiSettings.xml" );
#ifdef USE_KINECT
        kinectMan.saveSettings();
#endif
        cameraManager.saveSettings();
    }
    
#ifdef USE_KINECT
    kinectMan.close();
#endif
    
    delete gui; gui = NULL;
    
}

void testApp::audioReceived(float* input, int bufferSize, int nChannels)
{
    beatDetector.update( input ) ; 
    //fftManager.audioReceived( input , bufferSize , nChannels ) ;
}

//--------------------------------------------------------------
void testApp::update() {
       
    if ( bAutoSceneSwitch == true )
    {
        //cout << " is " << ofGetElapsedTimef() << " > " << ( lastSceneChangedTime ) << " + " <<  sceneDelayTime  << " ? " << endl ;
        if ( (int)ofGetFrameNum() % (int)sceneDelayTime == 0 ) // ofGetElapsedTimef() > ( lastSceneChangedTime + sceneDelayTime ) )
        {
            int lastSceneIndex = activeSceneIndex ; 
            activeSceneIndex++ ;
            if(activeSceneIndex > scenes.size()-1) activeSceneIndex=0;
            
            lastSceneChangedTime = ofGetElapsedTimef() ;
            //cout << "new lastScene changed time "  << lastSceneChangedTime << endl ;
    
            scenes[lastSceneIndex]->deactivate();
           
            if(bDrawGui) scenes[activeSceneIndex]->gui->setVisible(true);
            scenes[activeSceneIndex]->activate();

        }
    }
    
    Tweenzor::update ( ofGetElapsedTimeMillis() ) ;
#ifdef USE_KINECT
    kinectMan.update();
#endif
    cameraManager.update();
	if(Scenes::isValidIndex( activeSceneIndex ))
    {
        scenes[activeSceneIndex]->update();
    }
    
    
    ((ofxUIToggle*)gui->getWidget("LOW"))->setValue( beatDetector.isLow() ) ;
    ((ofxUIToggle*)gui->getWidget("MID"))->setValue( beatDetector.isMid() ) ;
    ((ofxUIToggle*)gui->getWidget("HIGH"))->setValue( beatDetector.isHigh() ) ;
}

//--------------------------------------------------------------
void testApp::draw() {


    if(Scenes::isValidIndex( activeSceneIndex )) {
        scenes[activeSceneIndex]->draw();
    }
     
    ofSetColor(255);
    
#ifdef USE_SYPHON
    outputSyphonServer.publishScreen() ;
#endif
    
}

//--------------------------------------------------------------
void testApp::setupMainGui() {
    float guiW = 300;
    
    gui->setPadding(10);
    
    gui->addWidgetDown(new ofxUILabel("Main Settings", OFX_UI_FONT_LARGE));
    
    gui->addSpacer(guiW, 2);
    
    gui->addWidgetDown( new ofxUIButton("B_SAVE", false, 16, 16) );
    gui->addWidgetRight( new ofxUIToggle("B_AUTO_SAVE", false, 16, 16) );
    
    gui->addSpacer(guiW, 1);
    gui->addWidgetDown(new ofxUIFPS(OFX_UI_FONT_SMALL));
    gui->addWidgetRight( new ofxUIButton("B_DRAW_GUI", false, 16, 16) );
    gui->addWidgetDown( new ofxUIToggle("B_DRAW_Kinect_Gui", false, 16, 16) );
    
    gui->addSpacer(guiW, 1);
    gui->addWidgetDown( new ofxUIToggle("FULLSCREEN", false, 16, 16) );
    gui->addWidgetRight( new ofxUIToggle("B_SHOVE_OVER", false, 16, 16) );
    gui->addWidgetDown( new ofxUITextInput( "Projector Width", "1920", 120, 16) );
    gui->addWidgetRight( new ofxUITextInput( "Projector Height", "1080", 120, 16) );
    
    gui->addSpacer(guiW, 1);
    gui->addWidgetDown( new ofxUIToggle("B_AUTO_SCENE_SWITCH", false, 16, 16) );
    
    gui->addWidgetDown( new ofxUIMinimalSlider("SCENE DELAY TIME", 0.0f , 120.0f, sceneDelayTime , guiW-50, 16.f ) );

    gui->addSpectrum("FFT" , beatDetector.getSmoothedFFT() , FFT_BINS ) ;
    gui->addToggle( "LOW" , false ) ;
    gui->addWidgetRight( new ofxUIToggle( "MID" , false , 16 , 16 ) ) ;
    gui->addWidgetRight( new ofxUIToggle( "HIGH" , false , 16 , 16 ) ) ;
    gui->addSlider( "BEAT VALUE" , 0 , 255 , &beatValue ) ;
    ofAddListener( gui->newGUIEvent, this, &testApp::guiEvent );
}

//--------------------------------------------------------------
void testApp::guiEvent( ofxUIEventArgs& e ) {
    string name = e.widget->getName();
    if(name == "B_SAVE" ) {
        gui->saveSettings( "GUI/mainGuiSettings.xml" );
    } else if (name == "B_DRAW_GUI" || name == "B_DRAW_Kinect_Gui") {
        bDrawGui        = ((ofxUIToggle*)gui->getWidget("B_DRAW_GUI"))->getValue();
        bKinectCamGui   = ((ofxUIToggle*)gui->getWidget("B_DRAW_Kinect_Gui"))->getValue();
        setDrawGuis( bDrawGui );
    } else if (name == "B_AUTO_SCENE_SWITCH") {
        bAutoSceneSwitch = ((ofxUIToggle*)gui->getWidget("B_AUTO_SCENE_SWITCH"))->getValue();
    } else if (name == "FULLSCREEN" ) {
        bool bSetFullscreen = ((ofxUIToggle*)gui->getWidget("FULLSCREEN"))->getValue();
        ofSetFullscreen( bSetFullscreen );
    } else if (name == "Projector Width" || name == "Projector Height") {
        setSceneBounds();
    } else if ( name == "SCENE DELAY TIME" )
    {
        sceneDelayTime =  ((ofxUIMinimalSlider*)gui->getWidget("SCENE DELAY TIME"))->getScaledValue() * 30 ;
        //cout << "scene delay time is now : " << sceneDelayTime << endl ;
        lastSceneChangedTime = ofGetElapsedTimef() ; 
    } else if ( name == "BEAT VALUE" )
    {
        beatDetector.setBeatValue( e.getSlider()->getScaledValue() ) ;
        cout << " setting BEAT Value to : "<< e.getSlider()->getScaledValue() << endl ; 
    }
    
}

//--------------------------------------------------------------
void testApp::setDrawGuis( bool bDraw ) {
    ((ofxUIToggle*)gui->getWidget("B_DRAW_GUI"))->setValue(bDraw);
    bDrawGui = ((ofxUIToggle*)gui->getWidget("B_DRAW_GUI"))->getValue();
    
    if(Scenes::isValidIndex( activeSceneIndex )) {
        scenes[activeSceneIndex]->gui->setVisible(bDrawGui);
    }
    

    gui->setVisible(bDrawGui);
#ifdef USE_KINECT
    if ( kinectMan.gui != NULL )
        kinectMan.gui->setVisible( bDrawGui );
#endif
    if(cameraManager.gui != NULL)
        cameraManager.gui->setVisible(bDrawGui);

}

//--------------------------------------------------------------
void testApp::setSceneBounds() {
    int pw = ofToInt( ((ofxUITextInput*)gui->getWidget("Projector Width"))->getTextString() );
    int ph = ofToInt( ((ofxUITextInput*)gui->getWidget("Projector Height"))->getTextString() );
      
    for(int i = 0; i < scenes.size(); i++ ) {
        scenes[i]->setBounds(pw, ph);
    }
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){
	
    if(key == 'f') {
        ((ofxUIToggle*)gui->getWidget("FULLSCREEN"))->toggleValue();
        bool bSetFullscreen = ((ofxUIToggle*)gui->getWidget("FULLSCREEN"))->getValue();
        ofSetFullscreen( bSetFullscreen );
    }
    
    if(key == 'd') {
        ((ofxUIToggle*)gui->getWidget("B_DRAW_GUI"))->toggleValue();
        bDrawGui = ((ofxUIToggle*)gui->getWidget("B_DRAW_GUI"))->getValue();
        setDrawGuis( bDrawGui );
    }
    if(key == OF_KEY_RIGHT && !bAutoSceneSwitch ) {
        scenes[activeSceneIndex]->deactivate();
        activeSceneIndex++;
        if(activeSceneIndex > scenes.size()-1) activeSceneIndex=0;
        if(bDrawGui) scenes[activeSceneIndex]->gui->setVisible(true);
        scenes[activeSceneIndex]->activate();
    }
    if(key == OF_KEY_LEFT && !bAutoSceneSwitch ) {
        scenes[activeSceneIndex]->deactivate();
        activeSceneIndex--;
        if(activeSceneIndex < 0) activeSceneIndex = scenes.size()-1;
        if(bDrawGui) scenes[activeSceneIndex]->gui->setVisible(true);
        scenes[activeSceneIndex]->activate();
    }
    
    if ( key == 's')
    {
        ofSaveScreen( ofToDataPath( ofToString( ofGetUnixTime() )) + ".png" ) ;
    }
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
	setSceneBounds();
}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){ 

}
