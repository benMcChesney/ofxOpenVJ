//
//  SimpleScene.cpp
//  simpleExample
//
//  Created by Ben McChesney on 5/15/14.
//
//

#include "TileTextureScene.h"

void TileTextureScene::setup()
{
	dir = ofDirectory("tileTextureImages"); 
	dir.sort(); 
	dir.listDir(); 
	for (int i = 0; i < dir.size(); i++)
	{
		images.push_back(new ofImage());
		images[i]->loadImage(dir.getPath(i));
	}
	activeIndex = 0; 
	

	
}

void TileTextureScene::setupGui(float a_x, float a_y)
{
    BaseScene::setupGui( a_x , a_y ) ;

	ofxOpenVJConstants *c = ofxOpenVJConstants::Instance(); 
	/*
	gui.add(rectWidthSlider.setup("RECT WIDTH SLIDER", 150.0f, 50.0f, 400.0f));
	*/

	gui.add(numCopies.setup("NUM COPIES", 2, 1, 10)); 
	gui.add(nextImage.setup("NEXT IMAGE")); 
	gui.add(prevImage.setup("PREV IMAGE")); 
	gui.add(minTextureScale.setup("MIN TEX SCALE", 0.9, 0.25, 1.0)); 
	gui.add(maxTextureScale.setup("MAX TEX SCALE", 1.05, 0.35, 1.5));

    loadSettings() ; 

	nextImage.addListener(this, &TileTextureScene::nextImageHandler);
	prevImage.addListener(this, &TileTextureScene::prevImageHandler);
}

void TileTextureScene::update()
{

	BaseScene::update();

}

void TileTextureScene::draw()
{
	ofSetColor(255);
	ofImage * img = images[activeIndex]; 

	float width = ofGetWidth() / numCopies; 

	float s = ofMap(soundManager->beatPerc, 0.0f, 1.0f, minTextureScale, maxTextureScale ,  true);
	for (int y = 0; y < numCopies; y++)
	{
		for (int x = 0; x < numCopies; x++)
		{
			ofPushMatrix(); 
				ofTranslate(x * width, y * width ); 
				ofTranslate(width / 2, width / 2); 
				ofScale(s, s, 1); 
				img->draw( -width/2 , -width/2, width , width ); 
			ofPopMatrix(); 
		}
	}
}

void TileTextureScene::nextImageHandler()
{
	offsetImageByIndex(1);
}
void TileTextureScene::prevImageHandler()
{
	offsetImageByIndex(-1);
}

void TileTextureScene::offsetImageByIndex(int index)
{
	//cout << "offsetImageByIndex at the beginning " << activeIndex;
	int newIndex = index + activeIndex;
	int maxIndex = images.size() - 1;
	if (newIndex < 0)
		newIndex = maxIndex;

	if (newIndex > maxIndex)
		newIndex = 0;

	activeIndex = newIndex; // ofWrap(index, 0, loadedImages.size());
							//	cout << "offsetImageByIndex at the end " << activeIndex;

}

bool TileTextureScene::transitionIn( float delay , float transitionTime )
{
    
    if ( BaseScene::transitionIn( delay , transitionTime ) == false )
        return false ;
    else
    {
        cout << "simple scene transitionin ! " << endl ; 

    }

    return true ;
}

bool TileTextureScene::transitionOut( float delay , float transitionTime )
{
    if ( BaseScene::transitionOut( delay , transitionTime ) == false )
        return false ;
    else
    {
        
    }
    return true ;
}

void TileTextureScene::drawDebug( )
{
	sceneTransitionTimer.draw(50 , 50);
}

void TileTextureScene::activate()
{
    BaseScene::activate() ; 
}

void TileTextureScene::deactivate()
{
    BaseScene::deactivate() ; 
}
