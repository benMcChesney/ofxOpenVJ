//
//  ofxOpenVJSet.cpp
//  simpleExample
//
//  Created by Ben McChesney on 6/1/14.
//
//

#include "ofxOpenVJSet.h"

//--------------------------------------------------------------
void ofxOpenVJSet::setup( int bufferSize ) {
    
    ofEnableSmoothing();
	ofEnableAlphaBlending();
    
    ofSetSmoothLighting(true);
    
    // init reference vars before gui gets them //
    bKinectCamGui = true;
    activeSceneIndex = 0;
    
    soundManager.setup( bufferSize ) ;
	compositorManager.setup(); 

    float guiY = 0 ;
	gui.setup();
    setupMainGui();

    ofAddListener( ofxOpenVJEvents::Instance()->SCENE_TRANSITION_IN_COMPLETE , this , &ofxOpenVJSet::sceneTransitionInHandler ) ;
    ofAddListener( ofxOpenVJEvents::Instance()->SCENE_TRANSITION_OUT_COMPLETE , this , &ofxOpenVJSet::sceneTransitionOutHandler ) ;
    
	/*
    cameraManager.setup();
    cameraManager.setupGui( 670 , guiY);
    cameraManager.loadSettings();
    cameraManager.gui->setVisible( false );
    */

    sceneTimer.setup( 5000 , "SCENE TIMER" ) ; 
    ofAddListener( sceneTimer.TIMER_COMPLETE , this , &ofxOpenVJSet::sceneTimerComplete ) ;
    ofShowCursor() ;
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
    ofLogNotice() << "added scene # " << scenes.size()  << " - " << scene->name ;
}

void ofxOpenVJSet::initialize( )
{
    float guiY = 0 ;
    setSceneBounds();
    for(int i = 0; i < scenes.size(); i++)
	{
        Scenes::registerScene(scenes[i]->index, scenes[i]->name);
#ifdef USE_KINECT
        scenes[i]->depthCameraManager        = depthCameraManager;
#endif

#ifdef USE_KINECT_V2
		scenes[i]->depthCameraManager = depthCameraManager ; 
#endif
        scenes[i]->soundManager     = &soundManager;
		scenes[i]->compositorManager = &compositorManager;
        //scenes[i]->cameraManager        = &cameraManager;
        scenes[i]->setup();
        scenes[i]->setupGui( 340 + 670 , guiY);
        scenes[i]->loadSettings();
        scenes[i]->deactivate();
    }
    
    Scenes::toString();
    
    
    setDrawGuis( true );
    // activate the first scene //
    scenes[activeSceneIndex]->transitionIn( setDelayTime , setTransitionTime );
    
    
    //gui->loadFromFile( "GUI/mainGuiSettings.xml" );
#ifdef USE_KINECT
    depthCameraManager->loadSettings();
#endif
    //cameraManager.loadSettings();
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
    
   // delete gui; gui = NULL;
    
}

void ofxOpenVJSet::audioReceived(float* input, int bufferSize, int nChannels)
{
    soundManager.audioReceived( input , bufferSize , nChannels ) ;
    
}

//--------------------------------------------------------------
void ofxOpenVJSet::update() {
    
    sceneTimer.update() ; 
      
#ifdef USE_KINECT
    depthCameraManager->update();
#endif
    //cameraManager.update();
    soundManager.update() ;
	compositorManager.update(); 
    
    for ( auto scene = scenes.begin() ; scene != scenes.end() ; scene++ )
    {
        if ( (*scene)->bVisible == true )
            (*scene)->update();
    
    }
    
    
}

//--------------------------------------------------------------
void ofxOpenVJSet::draw() {
    
    
    for ( auto scene = scenes.begin() ; scene != scenes.end() ; scene++ )
    {
		if ((*scene)->bVisible == true)
		{
			(*scene)->draw();
			compositorManager.drawScene( &(*scene)->fbo , ofColor( 0 , 0 , 0 , 1 )  ); 
		}
    }
    
    ofSetColor(255);

    
#ifdef USE_SYPHON
    //   outputSyphonServer.publishScreen() ;
#endif


	if (bDrawGui == true)
	{
		for (auto scene = scenes.begin(); scene != scenes.end(); scene++)
		{
			// if ( (*scene)->isVisible() == true )
			(*scene)->drawGui();
		}
		compositorManager.gui.draw(); 
		gui.draw(); 
		getSoundManager()->drawFFTBands( 0 , 0 , ofxOpenVJConstants::Instance()->GUI_WIDGET_WIDTH , 200);
	}

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
   	scenes[activeSceneIndex]->bDrawGui = bDrawGui;
   
    scenes[activeSceneIndex]->transitionIn( setDelayTime , setTransitionTime );
}

//--------------------------------------------------------------
void ofxOpenVJSet::setupMainGui() {
    float guiW = 300;
 
	ofxOpenVJConstants *c = ofxOpenVJConstants::Instance();
	
	gui.setWidthElements(c->GUI_WIDGET_WIDTH); 
	gui.setDefaultHeight(c->GUI_WIDGET_HEIGHT); 
	gui.setDefaultWidth(c->GUI_WIDGET_WIDTH); 
	gui.setup("ofxOpenVJ Settings" , "GUI/mainGuiSettings.xml" );

	
	gui.setPosition ( c->GUI_WIDGET_WIDTH, 0); 
	gui.setBackgroundColor(c->GUI_WIDGET_BG_COLOR); 
	gui.add(projectorWidth.setup("WIDTH", 1920, 50, 3840));
	gui.add(projectorHeight.setup("HEIGHT", 1080, 50, 1400));
	gui.add(bDrawDebug.setup("DRAW DEBUG" , false ));
	gui.add(bAutoSceneSwitch.setup("AUTO SCENE SWITCH", false ));	
	gui.add(setTransitionTime.setup("SET TRANSITION TIME", 0.5f, 0.1f, 3.0f ));
	gui.add(setDelayTime.setup("SET DELAY TIME", 0.2f, 0.1f, 4.0f ));

}

/*
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
    
}*/

//--------------------------------------------------------------
void ofxOpenVJSet::setDrawGuis( bool bDraw ) {

    if(Scenes::isValidIndex( activeSceneIndex )) {
		scenes[activeSceneIndex]->bDrawGui = bDraw; 
    }
    
	bDrawGui = bDraw; 

#ifdef USE_KINECT
    if ( depthCameraManager != NULL && depthCameraManager->gui != NULL )
        depthCameraManager->gui->setVisible( bDrawGui );
#endif
   // if(cameraManager.gui != NULL)
   //     cameraManager.gui->setVisible(bDrawGui);
    
    
    if ( bDraw )
        ofShowCursor() ;
    else
        ofHideCursor() ; 
}

//--------------------------------------------------------------
void ofxOpenVJSet::setSceneBounds()
{
    for(int i = 0; i < scenes.size(); i++ ) {
        scenes[i]->setBounds( projectorWidth , projectorHeight );
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
    
        case 'g':
        case 'G':
        {
			bDrawGui = !bDrawGui; 
            setDrawGuis( bDrawGui );
			cout << "bDrawGui should be :" << bDrawGui << endl;
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
        
		//if (bDrawGui)
			scenes[activeSceneIndex]->bDrawGui = bDrawGui; 
        scenes[activeSceneIndex]->transitionIn( setDelayTime, setTransitionTime ) ;
    }
    else
    {
        ofLogNotice() << "scene[" << activeSceneIndex << "] ( " << scenes[activeSceneIndex]->name << " ) cannot transitionOut ! " << endl ;
    }
}


