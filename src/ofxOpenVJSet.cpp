//
//  ofxOpenVJSet.cpp
//  simpleExample
//
//  Created by Ben McChesney on 6/1/14.
//
//

#include "ofxOpenVJSet.h"

//--------------------------------------------------------------
void ofxOpenVJSet::setup() {
    
    ofEnableSmoothing();
	ofEnableAlphaBlending();
    
    ofSetSmoothLighting(true);
    
    // init reference vars before gui gets them //
    bDrawGui    = false;
    bAutoSceneSwitch = false;
    bKinectCamGui = true;
    activeSceneIndex = 0;
    
    beatDetector.enableBeatDetect() ;
    //beatDetector.setBeatValue( 120 ) ;
    float guiY = 0 ;
    gui = new ofxUICanvas( 10, guiY, 320, ofGetHeight() - guiY - 10 );
    setupMainGui();
    gui->loadSettings("GUI/mainGuiSettings.xml");
    gui->setVisible( bDrawGui );
    
    //A few ifdefs to make sure there's not a gap in the GUIs
    float guiX = 340 ;

    ofAddListener( ofxOpenVJEvents::Instance()->SCENE_TRANSITION_IN_COMPLETE , this , &ofxOpenVJSet::sceneTransitionInHandler ) ;
    ofAddListener( ofxOpenVJEvents::Instance()->SCENE_TRANSITION_OUT_COMPLETE , this , &ofxOpenVJSet::sceneTransitionOutHandler ) ;
    
    cameraManager.setup();
    cameraManager.setupGui( 670 , guiY);
    cameraManager.loadSettings();
    cameraManager.gui->setVisible( false );
    
    sceneTimer.setup( 5000 , "SCENE TIMER" ) ; 
    ofAddListener( sceneTimer.TIMER_COMPLETE , this , &ofxOpenVJSet::sceneTimerComplete ) ;
  
}

void ofxOpenVJSet::initKinectV1( )
{
	#ifdef USE_KINECT
    // KinectManager //
	depthCameraManager = new KinectManager() ;
  //  depthCameraManage
    depthCameraManager->setupGui(340, 0 );
    depthCameraManager->close();
    depthCameraManager->open();
    depthCameraManager->loadSettings();
    depthCameraManager->gui->setVisible(bDrawGui);
    //guiX = 670 ;
    #endif
}


void ofxOpenVJSet::initKinectV2( ) 
{
#ifdef USE_KINECT_V2
	depthCameraManager = new KinectV2Manager() ;
	((KinectV2Manager*)depthCameraManager)->setup( ) ;
	depthCameraManager->setupGui( 340 , 0 ) ;
	depthCameraManager->loadSettings() ; 
	//depthCameraManager->gui->setVisible( bDrawGui ) ; 
#endif

}

void ofxOpenVJSet::addScene( BaseScene * scene )
{
    scenes.push_back( scene );
    ofLogVerbose() << "added scene # " << scenes.size()  << " - " << scene->name ;
}

void ofxOpenVJSet::initialize( )
{
    float guiY = 0 ;
    setSceneBounds();
    for(int i = 0; i < scenes.size(); i++) {
        Scenes::registerScene(scenes[i]->index, scenes[i]->name);
#ifdef USE_KINECT
        scenes[i]->depthCameraManager        = depthCameraManager;
#endif

#ifdef USE_KINECT_V2
		scenes[i]->depthCameraManager = depthCameraManager ; 
#endif
        scenes[i]->beatDetector     = &beatDetector;
        scenes[i]->cameraManager        = &cameraManager;
        scenes[i]->setup();
        scenes[i]->setupGui( 340 + 670 , guiY);
        scenes[i]->loadSettings();
        scenes[i]->deactivate();
    }
    
    Scenes::toString();
    
    
    setDrawGuis( true );
    // activate the first scene //
    scenes[activeSceneIndex]->transitionIn( setDelayTime , setTransitionTime );
    
    
    gui->loadSettings( "GUI/mainGuiSettings.xml" );
#ifdef USE_KINECT
    depthCameraManager->loadSettings();
#endif
    cameraManager.loadSettings();
}

//--------------------------------------------------------------
void ofxOpenVJSet::exit() {
    
    for(int i = 0; i < scenes.size(); i++ )
    {
        
        delete scenes[i];
        scenes[i] = NULL;
    }
    scenes.clear();
    
#ifdef USE_KINECT
    depthCameraManager->close();
#endif
    
    delete gui; gui = NULL;
    
}

void ofxOpenVJSet::audioReceived(float* input, int bufferSize, int nChannels)
{
    beatDetector.update( input ) ;
    
}

//--------------------------------------------------------------
void ofxOpenVJSet::update() {
    
    sceneTimer.update() ; 
      
#ifdef USE_KINECT
    depthCameraManager->update();
#endif
    cameraManager.update();
    
    for ( auto scene = scenes.begin() ; scene != scenes.end() ; scene++ )
    {
        if ( (*scene)->bVisible == true )
            (*scene)->update();
    
    }
    
//    ((ofxUISpectrum*)gui->getWidget("FFT")))->set
    
    ((ofxUIToggle*)gui->getWidget("KICK"))->setValue( beatDetector.isKick() ) ;
    ((ofxUIToggle*)gui->getWidget("SNARE"))->setValue( beatDetector.isSnare() ) ;
    ((ofxUIToggle*)gui->getWidget("HAT"))->setValue( beatDetector.isHat() ) ;
    
   // ((ofxUIToggle*)gui->getWidget("SNARE"))->setValue( beatDetector.isSnare() ) ;
   // ((ofxUIToggle*)gui->getWidget("KICK"))->setValue( beatDetector.isKick() );
   // ((ofxUIToggle*)gui->getWidget("HAT"))->setValue( beatDetector.isHat() ) ;
   // ((ofxUILabel*)gui->getWidget("BPM"))->setLabel( "BPM : " + ofToString( beatDetector.getBeatValue() ) ) ;
}

//--------------------------------------------------------------
void ofxOpenVJSet::draw() {
    
    
    for ( auto scene = scenes.begin() ; scene != scenes.end() ; scene++ )
    {
        if ( (*scene)->bVisible == true )
            (*scene)->draw();
    }
    
    ofSetColor(255);
    
#ifdef USE_SYPHON
    //   outputSyphonServer.publishScreen() ;
#endif

    if ( bDrawDebug == true )
    {
        for ( auto scene = scenes.begin() ; scene != scenes.end() ; scene++ )
        {
           // if ( (*scene)->isVisible() == true )
                (*scene)->drawDebug();
        }
    }
}

void ofxOpenVJSet::sceneTimerComplete( int & args ) 
{
    if ( !bAutoSceneSwitch ) return ; 
    
    int lastSceneIndex = activeSceneIndex ;
    //Handy ofWrap function 
    activeSceneIndex = ofWrap( activeSceneIndex+1 , 0 , scenes.size() ) ;
    
    scenes[lastSceneIndex]->transitionOut( setDelayTime , setTransitionTime );
    //scenes[lastSceneIndex]->deactivate();
   
    if(bDrawGui)
        scenes[activeSceneIndex]->gui->setVisible(true);
   
    scenes[activeSceneIndex]->transitionIn( setDelayTime , setTransitionTime );
}

//--------------------------------------------------------------
void ofxOpenVJSet::setupMainGui() {
    float guiW = 300;
    
    gui->setPadding(10);
    
    gui->addWidgetDown(new ofxUILabel("Main Settings", OFX_UI_FONT_LARGE));
    
    gui->addSpacer(guiW, 2);
   
    gui->addButton( "SAVE SETTINGS" , false ) ;
    gui->addButton( "LOAD SETTINGS" , false ) ;
    
    gui->addSpacer(guiW, 1);
    gui->addWidgetDown(new ofxUIFPS(OFX_UI_FONT_SMALL));
    gui->addWidgetRight( new ofxUIButton("B_DRAW_GUI", false, 16, 16) );
    
    gui->addSpacer(guiW, 1);
    gui->addWidgetDown( new ofxUIToggle("FULLSCREEN", false, 16, 16) );
    gui->addWidgetRight( new ofxUIToggle("B_SHOVE_OVER", false, 16, 16) );
    gui->addWidgetDown( new ofxUITextInput( "Projector Width", "1920", 120, 16) );
    gui->addWidgetRight( new ofxUITextInput( "Projector Height", "1080", 120, 16) );
    gui->addToggle( "DRAW DEBUG INFO" , &bDrawDebug ) ; 
    gui->addSpacer(guiW, 1);
    gui->addWidgetDown( new ofxUIToggle("B_AUTO_SCENE_SWITCH", false, 16, 16) );
    
    gui->addSlider("SCENE DELAY TIME", 0.0f , 120.0f, 30.0f  );
    gui->addSlider("SET TRANSITION TIME", 0.1f , 2.0f , &setTransitionTime ) ;
    gui->addSlider("SET DELAY TIME", 0.1f , 4.0f , &setDelayTime ) ;

    
    
    gui->addSpectrum("FFT" , beatDetector.getSmoothedFFT() , 32 ) ;
    
    gui->addToggle( "KICK" , false ) ;
    gui->addToggle( "SNARE" , false ) ;
    gui->addToggle( "HAT" , false ) ;
//    gui->addNumberDialer("BPM", 30, 200, 120, 0 ) ;
    //gui->addLabel("BPM" , "NONE" ) ;
    ofAddListener( gui->newGUIEvent, this, &ofxOpenVJSet::guiEvent );
    
    
}

//--------------------------------------------------------------
void ofxOpenVJSet::guiEvent( ofxUIEventArgs& e ) {
    string name = e.widget->getName();
    
    if ( name == "LOAD SETTINGS" && e.getButton()->getValue() == true )
        gui->loadSettings("GUI/mainGuiSettings.xml");
    
    if ( name == "SAVE SETTINGS" && e.getButton()->getValue() == true )
        gui->saveSettings( "GUI/mainGuiSettings.xml" );
    
    if(name == "B_SAVE" ) {
        gui->saveSettings( "GUI/mainGuiSettings.xml" );
    } else if (name == "B_DRAW_GUI" || name == "B_DRAW_Kinect_Gui") {
        bDrawGui        = ((ofxUIToggle*)gui->getWidget("B_DRAW_GUI"))->getValue();
        bKinectCamGui   = ((ofxUIToggle*)gui->getWidget("B_DRAW_Kinect_Gui"))->getValue();
        setDrawGuis( bDrawGui );
    } else if (name == "B_AUTO_SCENE_SWITCH" ) {
        bAutoSceneSwitch = e.getToggle()->getValue() ; 
        if ( bAutoSceneSwitch )
            sceneTimer.start( true , true ) ;
        else
            sceneTimer.stop() ; 
    } else if (name == "FULLSCREEN" ) {
        bool bSetFullscreen = ((ofxUIToggle*)gui->getWidget("FULLSCREEN"))->getValue();
        ofSetFullscreen( bSetFullscreen );
    } else if (name == "Projector Width" || name == "Projector Height") {
        setSceneBounds();
    } else if ( name == "SCENE DELAY TIME" )
    {
        float timeInSeconds = e.getSlider()->getScaledValue() ;
        sceneTimer.delayMillis = timeInSeconds * 1000.0f ;
        if ( sceneTimer.bIsRunning )
            sceneTimer.start( true , true ) ;
    } 
    
}

//--------------------------------------------------------------
void ofxOpenVJSet::setDrawGuis( bool bDraw ) {
    ((ofxUIToggle*)gui->getWidget("B_DRAW_GUI"))->setValue(bDraw);
    bDrawGui = ((ofxUIToggle*)gui->getWidget("B_DRAW_GUI"))->getValue();
    
    if(Scenes::isValidIndex( activeSceneIndex )) {
        scenes[activeSceneIndex]->gui->setVisible(bDrawGui);
    }
    
    
    gui->setVisible(bDrawGui);
#ifdef USE_KINECT
    if ( depthCameraManager != NULL && depthCameraManager->gui != NULL )
        depthCameraManager->gui->setVisible( bDrawGui );
#endif
    if(cameraManager.gui != NULL)
        cameraManager.gui->setVisible(bDrawGui);
    
}

//--------------------------------------------------------------
void ofxOpenVJSet::setSceneBounds() {
    int pw = ofToInt( ((ofxUITextInput*)gui->getWidget("Projector Width"))->getTextString() );
    int ph = ofToInt( ((ofxUITextInput*)gui->getWidget("Projector Height"))->getTextString() );
    
    for(int i = 0; i < scenes.size(); i++ ) {
        scenes[i]->setBounds(pw, ph);
    }
}

void ofxOpenVJSet::sceneTransitionInHandler( ofxOpenVJEventArgs &args )
{
    //cout << " TOP LEVEL sceneTransitionInHandler " << args.name << endl ;
    for ( auto scene = scenes.begin() ; scene != scenes.end() ; scene++ )
    {
        if ( args.name.compare( (*scene)->name ) == 0 )
        {
            cout << "sceneTransitionInHandler '" << args.name << "' " << endl ;
            (*scene)->transitionInComplete() ;
            break ; 
        }
    }
}

void ofxOpenVJSet::sceneTransitionOutHandler( ofxOpenVJEventArgs &args )
{
    //cout << " TOP LEVEL sceneTransitionOutHandler " << args.name << endl ;
    for ( auto scene = scenes.begin() ; scene != scenes.end() ; scene++ )
    {
        if ( args.name.compare( (*scene)->name ) == 0 )
        {
            cout << "sceneTransitionOutHandler '" << args.name << "'" << endl ;
            (*scene)->transitionOutComplete() ;
            break ; 
        }
    }
}


//--------------------------------------------------------------
void ofxOpenVJSet::keyPressed(int key)
{	
    switch ( key )
    {
        case 'f':
        case 'F':
        {
            ((ofxUIToggle*)gui->getWidget("FULLSCREEN"))->toggleValue();
            bool bSetFullscreen = ((ofxUIToggle*)gui->getWidget("FULLSCREEN"))->getValue();
            ofSetFullscreen( bSetFullscreen );
        }
            break ; 
    
        case 'g':
        case 'G':
        {
            ((ofxUIToggle*)gui->getWidget("B_DRAW_GUI"))->toggleValue();
            bDrawGui = ((ofxUIToggle*)gui->getWidget("B_DRAW_GUI"))->getValue();
            setDrawGuis( bDrawGui );
        }
            break ;
    
        case OF_KEY_RIGHT :
        {
            if(  !bAutoSceneSwitch )
            {
                transitionToRelativeIndex( 1 ) ; 
            }
        }
            break;
            
        case OF_KEY_LEFT :
        {
            if(!bAutoSceneSwitch )
            {
                transitionToRelativeIndex( -1 ) ;
            }
        }
            break;
    }
}

void ofxOpenVJSet::transitionToRelativeIndex ( int indexOffset ) 
{
    if ( scenes[activeSceneIndex]->transitionOut( setDelayTime, setTransitionTime ) == true )
    {
        //Wrap it so the indices don't become invalid
        ofLogNotice() << "[" << activeSceneIndex << "] is OUT" << endl ;
        activeSceneIndex += indexOffset ; 
        activeSceneIndex = ofWrap( activeSceneIndex , 0 , scenes.size() ) ;
        
        ofLogNotice() << "[" << activeSceneIndex << "] is IN" << endl ; 
        
        if(bDrawGui)
            scenes[activeSceneIndex]->gui->setVisible(true);
        scenes[activeSceneIndex]->transitionIn( setDelayTime, setTransitionTime ) ;
    }
    else
    {
        ofLogNotice() << "scene[" << activeSceneIndex << "] ( " << scenes[activeSceneIndex]->name << " ) cannot transitionOut ! " << endl ;
    }
}


