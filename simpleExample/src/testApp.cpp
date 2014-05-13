#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup() {

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
	
    // init reference vars before gui gets them //
    fboShoveX   = 0;
    bShoveOver  = false;
    bDrawGui    = false;
    bAutoSceneSwitch = false;
    bKinectCamGui = true;
    activeSceneIndex = 0;

    lastSceneChangedTime = 0.0f ;
    sceneDelayTime = 5.0f ;
    
    int bufferSize = 512;
    fftManager.setup( true ) ;
    fftManager.setupOSCReceiver( 12345 ) ; 

    
    float guiY = 0 ;
    gui = new ofxUICanvas( 10, guiY, 320, ofGetHeight() - guiY - 10 );
    setupMainGui();
    gui->loadSettings("GUI/mainGuiSettings.xml");
    gui->setVisible( bDrawGui );
   
    
    // KinectManager //
    kinectMan.setupGui(340, guiY);
    kinectMan.close();
    kinectMan.open();
    kinectMan.loadSettings();
    kinectMan.gui->setVisible(bDrawGui);
    
    
    cameraManager.setup();
    cameraManager.setupGui(670, guiY);
    cameraManager.loadSettings();
    cameraManager.gui->setVisible(bDrawGui);
    
    //Point Cloud Scenes
    
    scenes.push_back( new TriangleKinectShader((int)scenes.size(), "TriangleKinectShader" ) ) ;
    scenes.push_back( new TestScene((int)scenes.size(), "TestScene" ) ) ;
    setSceneBounds();
    
    for(int i = 0; i < scenes.size(); i++) {
        Scenes::registerScene(scenes[i]->index, scenes[i]->name);
        scenes[i]->kinectMan    = &kinectMan;
        scenes[i]->fft          = &fftManager;
        scenes[i]->cameraMan    = &cameraManager;
        scenes[i]->setup();
        scenes[i]->setupGui(1000, guiY);
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
    
    bug.loadImage( "bug.png" ) ;
    bug.setAnchorPercent( 0.5 , 0.5 ) ;
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
        kinectMan.saveSettings();
        cameraManager.saveSettings();
    }
        
    kinectMan.close();
    
    delete gui; gui = NULL;
    
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

    fftManager.update() ;
    kinectMan.update();
    cameraManager.update();
    cameraManager.updateFft( fftManager.lowRange , fftManager.midRange , fftManager.highRange ) ; 
	if(Scenes::isValidIndex( activeSceneIndex ))
    {
        scenes[activeSceneIndex]->update();
        scenes[activeSceneIndex]->low = fftManager.lowRange ;
        scenes[activeSceneIndex]->mid = fftManager.midRange ;
        scenes[activeSceneIndex]->high = fftManager.highRange ;
    }
}

//--------------------------------------------------------------
void testApp::draw() {

    fbo.begin();
    ofClear(0);
    if(Scenes::isValidIndex( activeSceneIndex )) {
        scenes[activeSceneIndex]->draw();
    }
    fbo.end();
    
    ofSetColor(255);
    ofDisableAlphaBlending();
    if(bShoveOver) fbo.draw(fboShoveX, 0);
    else fbo.draw(0, 0);
    ofEnableAlphaBlending();
    
    ofSetColor( 255 ) ; 
    bug.draw( ofGetWidth() / 2  , 35 ) ;
    
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
    gui->addWidgetDown( new ofxUIMinimalSlider("FBO SHOVE X", 1200.f, 1920.f, &fboShoveX, guiW-50, 16.f ) );
    gui->addWidgetDown( new ofxUITextInput( "Projector Width", "1920", 120, 16) );
    gui->addWidgetRight( new ofxUITextInput( "Projector Height", "1080", 120, 16) );
    
    gui->addSpacer(guiW, 1);
    gui->addWidgetDown( new ofxUIToggle("B_AUTO_SCENE_SWITCH", false, 16, 16) );
    
    gui->addWidgetDown( new ofxUIMinimalSlider("SCENE DELAY TIME", 0.0f , 120.0f, sceneDelayTime , guiW-50, 16.f ) );
    gui->addWidgetDown( new ofxUIMinimalSlider("FFT INTERPOLATION", 0.0f , 1.0f, fftManager.lerpAmount , guiW-50, 16.f ) );

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
    } else if (name == "B_SHOVE_OVER") {
        bShoveOver = ((ofxUIToggle*)gui->getWidget("B_SHOVE_OVER"))->getValue();
        setSceneBounds();
    } else if (name == "B_AUTO_SCENE_SWITCH") {
        bAutoSceneSwitch = ((ofxUIToggle*)gui->getWidget("B_AUTO_SCENE_SWITCH"))->getValue();
    } else if (name == "FULLSCREEN" ) {
        bool bSetFullscreen = ((ofxUIToggle*)gui->getWidget("FULLSCREEN"))->getValue();
        ofSetFullscreen( bSetFullscreen );
    } else if (name == "Projector Width" || name == "Projector Height") {
        setSceneBounds();
    } else if ( name == "FFT INTERPOLATION" )
        fftManager.lerpAmount =  ((ofxUIMinimalSlider*)gui->getWidget("FFT INTERPOLATION"))->getScaledValue() ;
    else if ( name == "SCENE DELAY TIME" )
    {
        sceneDelayTime =  ((ofxUIMinimalSlider*)gui->getWidget("SCENE DELAY TIME"))->getScaledValue() * 30 ;
        //cout << "scene delay time is now : " << sceneDelayTime << endl ;
        lastSceneChangedTime = ofGetElapsedTimef() ; 
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
    if ( kinectMan.gui != NULL )
        kinectMan.gui->setVisible( bDrawGui );
    if(cameraManager.gui != NULL)
        cameraManager.gui->setVisible(bDrawGui);

}

//--------------------------------------------------------------
void testApp::setSceneBounds() {
    int pw = ofToInt( ((ofxUITextInput*)gui->getWidget("Projector Width"))->getTextString() );
    int ph = ofToInt( ((ofxUITextInput*)gui->getWidget("Projector Height"))->getTextString() );
    
    if(!bShoveOver) {
        pw = ofGetWidth();
        ph = ofGetHeight();
    }
    fbo.allocate(pw, ph);
    
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
