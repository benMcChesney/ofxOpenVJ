//
//  BaseScene.cpp
//  simpleExample
//
//  Created by Ben McChesney on 6/1/14.
//
//

#include "BaseScene.h"

BaseScene::BaseScene() { index = -1 ;  }
BaseScene::BaseScene( int a_index, string a_name )
{
    index = a_index;
    name = a_name;
    bTransitionIn = false ;
    bTransitionOut = false ;
    tweenArgs = 0.0f ; 
    bVisible = false ;
}

BaseScene::~BaseScene()
{
  /*  if(gui != NULL) { delete gui; gui = NULL;}
    cout << "BaseScene " << name << "->deconstructor()" << endl;*/
};

void BaseScene::drawGui()
{
	if (bDrawGui)
		gui.draw();
}

void BaseScene::setupGui(float a_x , float a_y )
{
	//Non Gui things that happen every scene
	setupCompositor();
    sceneTransitionTimer.setup( 500 , name + " timer" ) ;
    ofAddListener( sceneTransitionTimer.TIMER_COMPLETE , this , &BaseScene::sceneTransitionTimerComplete ) ;

	//GUI Things
	gui.setDefaultWidth(ofxOpenVJConstants::Instance()->GUI_WIDGET_WIDTH); 
	gui.setDefaultHeight(ofxOpenVJConstants::Instance()->GUI_WIDGET_HEIGHT);

	gui.setup(name + " Scene Settings" , getSettingsPath() );
	gui.setBackgroundColor(ofxOpenVJConstants::Instance()->GUI_WIDGET_BG_COLOR); 
	gui.setPosition(a_x, a_y); 
	gui.setWidthElements(320);
}

bool BaseScene::transitionIn( float delay , float transitionTime )
{
    if ( bTransitionIn == true  )
        return false ;
    activate() ; 
    bTransitionIn = true ;
    bTransitionOut = false ;
    //Tweenzor is in seconds, ofxSimpleTimer is in milliseconds...
    sceneTransitionTimer.setup( (delay + transitionTime) * 1000.0f ) ;
    sceneTransitionTimer.start( false , true ) ; 
    
    ofLogNotice() << " BaseScene :: " << name << " transition IN ! " << endl ; 
    //tweenArgs = 0.0f ;
    /*
     
     ///TODO : how to get BaseScene to trigger it's own tween with compelte listener
    baseTweenArgs = 0.0f ;
    Tweenzor::add( &baseTweenArgs , 0.0f , 1.0f , delay , transitionTime ) ;
    Tweenzor::addCompleteListener( Tweenzor::getTween( &baseTweenArgs ) , this , &BaseScene::transitionInComplete ) ;
     */
    return true ;
}


void BaseScene::update()
{
	sceneTransitionTimer.update(); 
	alphaStackUpdate(calcAlpha); 
	if (soundManager->lastBeatPerc > soundManager->beatPerc)
	{
		newBeatHandler(); 
	}
}

void BaseScene::newBeatHandler()
{
	cout << "BaseScene::newBeatHandler! @" << ofGetElapsedTimef() << endl; 
}

bool BaseScene::transitionOut( float delay , float transitionTime )
{
    if ( bTransitionOut == true  )
        return false ;
    
	bDrawGui = false; 
    ofLogNotice() << " BaseScene :: " << name << " transition OUT ! " << endl ;
    
    bTransitionOut = true ;
    bTransitionIn = false ;
    tweenArgs = 0.0f ;
    sceneTransitionTimer.setup( (delay + transitionTime) * 1000.0f ) ;
    sceneTransitionTimer.start( false , true ) ;
   
    return true ; 
}


void BaseScene::drawDebug()
{
    stringstream ss ;
    ss << "SCENE : " << name << " - visible ? " << bVisible << endl << "Transitioning in? : " << bTransitionIn << endl << "Transitioning out? : " << bTransitionOut << endl ;
    
    //if ( isVisible() )
    int y = 20 + 80 * index ;
    sceneTransitionTimer.draw( 50 , y ) ;
    
    ofDrawBitmapStringHighlight( ss.str() , 50 , y + 40  ) ;
}

void BaseScene::transitionInComplete (  )
{
    ofLogNotice() << " BaseScene :: " << name << " transition IN  COMPLETE! " << endl ;
    bTransitionIn = false ;
    tweenArgs = 0.0f ;
}

void BaseScene::transitionOutComplete(  )
{
    ofLogNotice() << " BaseScene :: " << name << " transition OUT COMPLETE ! " << bTransitionIn <<  endl ;
    bTransitionOut = false ;
    tweenArgs = 0.0f ;
    //baseTweenArgs = 0.0f ;
    deactivate() ;
}

void BaseScene::sceneTransitionTimerComplete ( int & args )
{
    ofLogNotice()  << name << " sceneTransitionTimerComplete()! " << endl ;
    sceneTransitionTimer.reset() ; 
    if ( bTransitionIn == true )
    {
        ofxOpenVJEventArgs args = ofxOpenVJEventArgs( name );
        ofNotifyEvent( ofxOpenVJEvents::Instance()->SCENE_TRANSITION_IN_COMPLETE , args ) ;
    }
    if ( bTransitionOut == true )
    {
        ofxOpenVJEventArgs args = ofxOpenVJEventArgs( name );
        ofNotifyEvent( ofxOpenVJEvents::Instance()->SCENE_TRANSITION_OUT_COMPLETE , args ) ;
        //transitionOutComplete ( ) ;
    }
}

void BaseScene::activate( )
{
    bVisible = true ;
};

void BaseScene::deactivate()
{
    bVisible = false ;
	bDrawGui = false;
};

void BaseScene::loadSettings()
{
	gui.loadFromFile(getSettingsPath()); 
}


void BaseScene::saveSettings()
{
	gui.saveToFile(getSettingsPath());
};


string BaseScene::getSettingsPath()
{
	stringstream ss;
	ss << "/GUI/" << name << "_Scene.xml";
	return ss.str(); 
}

void BaseScene::setupCompositor()
{
	fbo.allocate(ofGetWidth(), ofGetHeight(), GL_RGBA); 

	fbo.begin(); 
	ofClear(0, 0, 0, 1); 
	fbo.end(); 
}














