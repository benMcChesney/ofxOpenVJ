//
//  SimpleScene.cpp
//  simpleExample
//
//  Created by Ben McChesney on 5/15/14.
//
//

#include "ReflectMaskScene.h"

void ReflectMaskScene::setup()
{
	drawOffset = 0;
	lastBeatPerc = 0.0f; 
	bFirstWhite = true;

	mask.setup("Shaders/composite_rgb", ofRectangle(0, 0, ofGetWidth(), ofGetHeight())); 
	maskFbo.allocate(1920, 1080, GL_RGB); 
	maskFbo.begin(); 
	ofClear(0, 0, 0, 1); 
	maskFbo.end(); 
}

void ReflectMaskScene::setupGui(float a_x, float a_y)
{
    BaseScene::setupGui( a_x , a_y ) ;

    
	ofxOpenVJConstants *c = ofxOpenVJConstants::Instance(); 
	gui.add(rectWidthSlider.setup("RECT WIDTH SLIDER", 150.0f, 50.0f, 400.0f));


    loadSettings() ; 

	int numRectangles = (ofGetWidth() * 1.5 ) / (rectWidthSlider);


	for (int i = 0 ; i < numRectangles ; i++ )
	{
		bool bEven = (i % 2 == 0); 
		ofColor c = ofColor::white ; 
		if (bEven)
			c = ofColor::black; 

		float w = (i * rectWidthSlider); 
		squares.push_back(new TileSquare(c, w, (-w / 2) ) ); 
	}

	

	gui.add(nextImage.setup("NEXT IMAGE")); 
	gui.add(prevImage.setup("PREV IMAGE"));
		
	nextImage.addListener(this, &ReflectMaskScene::nextImageHandler); 
	prevImage.addListener(this, &ReflectMaskScene::prevImageHandler);
}



void ReflectMaskScene::nextImageHandler()
{
	offsetImageByIndex(1); 

}

void ReflectMaskScene::prevImageHandler()
{
	offsetImageByIndex(-1);
}

void ReflectMaskScene::offsetImageByIndex(int index)
{
	cout << "offsetImageByIndex at the beginning " << activeIndex; 
	int newIndex = index + activeIndex; 
	int maxIndex = loadedImages.size() - 1; 
	if (newIndex < 0)
		newIndex = maxIndex ;

	if (newIndex > maxIndex)
		newIndex = 0; 

	activeIndex = newIndex; // ofWrap(index, 0, loadedImages.size());
//	cout << "offsetImageByIndex at the end " << activeIndex;

}

void ReflectMaskScene::update()
{

	BaseScene::update();

}

void ReflectMaskScene::draw()
{
	drawOffset = (soundManager->bpmTapper.beatPerc() * rectWidthSlider / 2); // soundManager->beatTracker.isSnare();

	if ( lastBeatPerc > soundManager->bpmTapper.beatPerc())
	{

		ofColor c = ofColor::white; 
		bool bWhite = ( squares[0]->color.r > 128 ); 
		if ( bWhite )
			c = ofColor::black; 

		//cout << "colors[0] is :" << squares[0]->color <<  " bWhite ? " << bWhite << endl; 
		squares.insert( squares.begin() , new TileSquare( c, 0, 0 ));
		squares.pop_back(); 
	}

  //cout << "DRAW !! " << endl; 


	maskFbo.begin();
	ofClear(0, 0, 0, 1);

	ofClear(0, 0, 0, 1); 
	
	ofPushMatrix();
	ofTranslate(ofGetWidth() / 2, ofGetHeight() / 2); 
	ofRotateZ(45); //. (drawOffset / rectWidthSlider)  * 360.0f );

	//if (drawOffset > (rectWidthSlider/2))
	//	drawOffset -= rectWidthSlider/2;

	float maxDrawX = 2000.0f; 

	float curDrawX = maxDrawX + drawOffset; 

	int numRectangles = 20; // curDrawX / (rectWidthSlider);


	bool bEven = bFirstWhite ; 
	float w = drawOffset; 
	
	for (int i = (squares.size()-1) ; i > 0 ; i--)
	{
		ofSetColor(squares[i]->color); 
		float w = (i * rectWidthSlider) + drawOffset ; 
		ofRect( -w/2 -drawOffset/2  , -w/2 - drawOffset / 2, w + drawOffset , w + drawOffset);
	}
	

	ofColor color = ofColor::black; 
	if ( squares[ 0 ]->color.g > 128 ) 
		color = ofColor::white; 

	//ofSetColor( ofColor( 255 , 0 , 0 ) ); 
	ofSetColor(color); 
	w = soundManager->bpmTapper.beatPerc() * rectWidthSlider ; // drawOffset;
	ofRect( -w/2, -w / 2 ,w, w );
	
	ofPopMatrix(); 
	
	maskFbo.end(); 
	ofSetColor(ofColor::white); 

	ofTexture tex = loadedImages[activeIndex].getTextureReference(); 
	ofPushMatrix(); 
	ofTranslate(ofGetWidth(), 0 ); 
	ofScale(-1, 1, 1); 
	tex.draw(0, 0); 
	ofPopMatrix();

	mask.drawMask( tex , maskFbo.getTextureReference(), 0, 0, 1.0f); 

	//loadedImages[activeIndex].draw(0, 0, 1920 , 1080);
	

	lastBeatPerc = soundManager->bpmTapper.beatPerc(); 
}


void ReflectMaskScene::loadContentFromDir(string path)
{
	
	dir.allowExt("jpg");
	dir.allowExt("png"); 
	dir = ofDirectory(path);
	dir.listDir();
	cout << " dir size : " << dir.size() << endl;

	for (int i = 0; i < dir.size(); i++)
	{
		loadedImages.push_back(ofImage());
		cout << "loading : " << dir.getPath(i) << endl;
		loadedImages[i].loadImage(dir.getPath(i));
	}
	activeIndex = 0;
}

bool ReflectMaskScene::transitionIn( float delay , float transitionTime )
{
    
    if ( BaseScene::transitionIn( delay , transitionTime ) == false )
        return false ;
    else
    {
        cout << "simple scene transitionin ! " << endl ; 

    }

    return true ;
}

bool ReflectMaskScene::transitionOut( float delay , float transitionTime )
{
    if ( BaseScene::transitionOut( delay , transitionTime ) == false )
        return false ;
    else
    {
        
    }
    return true ;
}

void ReflectMaskScene::drawDebug( )
{
	sceneTransitionTimer.draw(50 , 50);
}

void ReflectMaskScene::activate()
{
    BaseScene::activate() ; 
}

void ReflectMaskScene::deactivate()
{
    BaseScene::deactivate() ; 
}
