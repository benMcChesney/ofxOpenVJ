//
//  BaseScene.cpp
//  simpleExample
//
//  Created by Ben McChesney on 6/1/14.
//
//

#include "BaseScene.h"

BaseScene::BaseScene() { gui = NULL; index = -1 ;  }
BaseScene::BaseScene( int a_index, string a_name )
{
    index = a_index;
    name = a_name;
    gui=NULL;
    bTransitionIn = false ;
    bTransitionOut = false ;
    //baseTweenArgs = 0.0f ;
    tweenArgs = 0.0f ; 
    bVisible = false ;
}

BaseScene::~BaseScene()
{
    if(gui != NULL) { delete gui; gui = NULL;}
    cout << "BaseScene " << name << "->deconstructor()" << endl;
};

void BaseScene::setupGui(float a_x , float a_y )
{
    sceneTransitionTimer.setup( 500 , name + " timer" ) ;
    ofAddListener( sceneTransitionTimer.TIMER_COMPLETE , this , &BaseScene::sceneTransitionTimerComplete ) ;
    
    gui = new ofxUIScrollableCanvas( a_x, a_y, 320, ofGetHeight() - 10 - a_y );
    gui->addWidgetDown(new ofxUILabel(name+" Scene Settings", OFX_UI_FONT_LARGE));
    gui->addButton( "SAVE SETTINGS" , false ) ;
    gui->addButton( "LOAD SETTINGS" , false ) ;
    gui->addSpacer(300, 2);
};
//virtual void guiEvent( ofxUIEventArgs & e ) { }


//--------------------------------------------------------------
void BaseScene::guiEvent(ofxUIEventArgs &e)
{
    string name = e.widget->getName();
    int kind = e.widget->getKind();
    
    if ( name == "LOAD SETTINGS" && e.getButton()->getValue() == true )
        loadSettings() ;
    
    if ( name == "SAVE SETTINGS" && e.getButton()->getValue() == true )
        saveSettings() ;
    
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
     
     TODO : how to get BaseScene to trigger it's own tween with compelte listener
    baseTweenArgs = 0.0f ;
    Tweenzor::add( &baseTweenArgs , 0.0f , 1.0f , delay , transitionTime ) ;
    Tweenzor::addCompleteListener( Tweenzor::getTween( &baseTweenArgs ) , this , &BaseScene::transitionInComplete ) ;
     */
    return true ;
}




bool BaseScene::transitionOut( float delay , float transitionTime )
{
    if ( bTransitionOut == true  )
        return false ;
    
    if ( gui != NULL )
        gui->setVisible( false ) ; 
    ofLogNotice() << " BaseScene :: " << name << " transition OUT ! " << endl ;
    
    bTransitionOut = true ;
    bTransitionIn = false ;
    tweenArgs = 0.0f ;
    sceneTransitionTimer.setup( (delay + transitionTime) * 1000.0f ) ;
    sceneTransitionTimer.start( false , true ) ;
    /*
    baseTweenArgs = 0.0f ;
    Tweenzor::add( &baseTweenArgs , 0.0f , 1.0f , delay , transitionTime ) ;
    Tweenzor::addCompleteListener( Tweenzor::getTween( &baseTweenArgs ) , this , &BaseScene::transitionOutComplete ) ;*/
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
    cout << " BaseScene :: " << name << " transition IN  COMPLETE! " << endl ;
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
    cout << name << " sceneTransitionTimerComplete()! " << endl ; 
    //sceneTransitionTimer.stop() ;
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
    if(gui != NULL)
    {
        gui->setVisible(false);
    }
};

void BaseScene::loadSettings()
{
    if(gui!=NULL) {
        gui->loadSettings( getXMLSettingsName() );
    }
}

void BaseScene::saveSettings()
{
    if(gui!=NULL) {
        cout << "BaseScene :: saveSettings() : " << getXMLSettingsName() << endl;
        gui->saveSettings( getXMLSettingsName() );
    }
};














