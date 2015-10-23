//
//  SimpleScene.cpp
//  simpleExample
//
//  Created by Ben McChesney on 5/15/14.
//
//

#include "AnimatedTileTextureScene.h"

void AnimatedTileTextureScene::setup()
{
	/*dir = ofDirectory("animatedTileTextures"); 
	dir.sort(); 
	dir.listDir(); 
	for (int i = 0; i < dir.size(); i++)
	{
		textures.push_back(new ofxGIF::fiGifLoader());
		textures[i]->load(dir.getPath(i));
	}
	activeIndex = 0; */
}

void AnimatedTileTextureScene::loadContentFromFolder(string path)
{
	dir = ofDirectory(path);
	cout << "loading directory " << path << endl;
	dir.sort();
	dir.listDir();
	for (int i = 0; i < dir.size(); i++)
	{
		cout << "loading... " << dir.getPath(i) << endl;
		textures.push_back(new ofxGIF::fiGifLoader());
		textures[i]->load(dir.getPath(i));
	}
	activeIndex = 0;
}

void AnimatedTileTextureScene::setupGui(float a_x, float a_y)
{
    BaseScene::setupGui( a_x , a_y ) ;

	ofxOpenVJConstants *c = ofxOpenVJConstants::Instance(); 
	/*
	gui.add(rectWidthSlider.setup("RECT WIDTH SLIDER", 150.0f, 50.0f, 400.0f));
	*/

	gui.add(numCopies.setup("NUM COPIES", 2, 1, 10)); 
	gui.add(nextImage.setup("NEXT IMAGE")); 
	gui.add(prevImage.setup("PREV IMAGE")); 
	gui.add(minTextureScale.setup("MIN TEX SCALE", 1.00, 0.25, 1.0)); 
	gui.add(maxTextureScale.setup("MAX TEX SCALE", 1.02, 0.35, 1.5));

	gui.add( bAutoChangeImageOnBeat.setup("AUTO CHANGE IMAGE", true));
	gui.add(beatsUntilChange.setup("NUM BEATS ON AUTO", 4, 1, 16)); 
	curBeats = 0; 

    loadSettings() ; 

	nextImage.addListener(this, &AnimatedTileTextureScene::nextImageHandler);
	prevImage.addListener(this, &AnimatedTileTextureScene::prevImageHandler);
}

void AnimatedTileTextureScene::newBeatHandler()
{
	curBeats++; 
	if (curBeats >= beatsUntilChange)
	{
		curBeats = 0; 
		nextImageHandler(); 
	}

	
}

void AnimatedTileTextureScene::update()
{

	BaseScene::update();

}

void AnimatedTileTextureScene::draw()
{
	ofSetColor(255);
	ofxGIF::fiGifLoader * img = textures[activeIndex];

	float width = ofGetWidth() / numCopies; 
	float height = ofGetHeight() / numCopies; 
	float s = ofMap(soundManager->beatPerc, 0.0f, 1.0f, minTextureScale, maxTextureScale ,  true);
	for (int y = 0; y < numCopies; y++)
	{
		for (int x = 0; x < numCopies; x++)
		{
			ofPushMatrix(); 
				ofTranslate(x * width, y * height ); 
				ofTranslate(width / 2, height / 2); 
				ofScale(s, s, 1); 


				int frame = floor(ofMap( soundManager->beatPerc , 0.0f, 1.0f, 0, (img->pages.size()-1) , true));
				img->pages[frame].draw( -width/2 , -height/2, width , height ); 
			ofPopMatrix(); 
		}
	}
}

void AnimatedTileTextureScene::nextImageHandler()
{
	offsetImageByIndex(1);
}
void AnimatedTileTextureScene::prevImageHandler()
{
	offsetImageByIndex(-1);
}

void AnimatedTileTextureScene::offsetImageByIndex(int index)
{
	//cout << "offsetImageByIndex at the beginning " << activeIndex;
	int newIndex = index + activeIndex;
	int maxIndex = textures.size() - 1;
	if (newIndex < 0)
		newIndex = maxIndex;

	if (newIndex > maxIndex)
		newIndex = 0;

	activeIndex = newIndex; // ofWrap(index, 0, loadedImages.size());
							//	cout << "offsetImageByIndex at the end " << activeIndex;

}

bool AnimatedTileTextureScene::transitionIn( float delay , float transitionTime )
{
    
    if ( BaseScene::transitionIn( delay , transitionTime ) == false )
        return false ;
    else
    {
        cout << "simple scene transitionin ! " << endl ; 

    }

    return true ;
}

bool AnimatedTileTextureScene::transitionOut( float delay , float transitionTime )
{
    if ( BaseScene::transitionOut( delay , transitionTime ) == false )
        return false ;
    else
    {
        
    }
    return true ;
}

void AnimatedTileTextureScene::drawDebug( )
{
	sceneTransitionTimer.draw(50 , 50);
}

void AnimatedTileTextureScene::activate()
{
    BaseScene::activate() ; 
}

void AnimatedTileTextureScene::deactivate()
{
    BaseScene::deactivate() ; 
}
