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

}

BaseScene::~BaseScene()
{
    if(gui != NULL) { delete gui; gui = NULL;}
    cout << "BaseScene " << name << "->deconstructor()" << endl;
};

void BaseScene::setupGui(float a_x , float a_y )
{
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














