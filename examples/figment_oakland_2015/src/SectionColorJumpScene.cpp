//
//  SimpleScene.cpp
//  simpleExample
//
//  Created by Ben McChesney on 5/15/14.
//
//

#include "SectionColorJumpScene.h"

void SectionColorJumpScene::setup()
{

}

void SectionColorJumpScene::setupGui(float a_x, float a_y)
{
    BaseScene::setupGui( a_x , a_y ) ;

	ofxOpenVJConstants *c = ofxOpenVJConstants::Instance(); 

	gui.add(numSegments.setup("NUM SEGMENTS", 3, 1, 10)); 
	gui.add(bStep.setup("STEP", false)); 
	gui.add(bSequence.setup("SEQUENCE", true)); 
	gui.add(bHorizontal.setup("HORIZONTAL", false)); 

	gui.add(hueSequenceStep.setup("HUE STEP", 0.1, 0.01, 16.0f)); 
	
	gui.add(segmentColorHue.setup("HUE COLOR HUE", 215.0f, 0.0f, 255.0f));
	gui.add(segmentColorBrightness.setup("HUE COLOR BRIGHTNESS", 215.0f, 0.0f, 255.0f));
	gui.add(segmentColorSaturation.setup("HUE COLOR SATURATION", 215.0f, 0.0f, 255.0f));
	
	gui.add(angleStep.setup("ANGLE STEP of 15", 3, 0, 6 )); 
	gui.add(resetAngle.setup("RESET ANGLE")); 

	resetAngle.addListener(this, &SectionColorJumpScene::resetAngleListener); 
	curAngle = 0; 
	
	loadSettings(); 

	curSegment = 0; 
	segmentColor = ofColor::fromHsb(segmentColorHue, segmentColorBrightness, segmentColorSaturation); 
	/*segmentColorSaturation
	gui.add(rectWidthSlider.setup("RECT WIDTH SLIDER", 150.0f, 50.0f, 400.0f));
   
	*/
	loadSettings();
}

void SectionColorJumpScene::resetAngleListener()
{
	curAngle = 0; 
}

void SectionColorJumpScene::update()
{

	BaseScene::update();

	float hue = segmentColor.getHue();
	hue += hueSequenceStep;
	segmentColor = ofColor::fromHsb(hue, segmentColorBrightness, segmentColorSaturation);

	/*
	if (soundManager->lastBeatPerc > soundManager->beatPerc)
	{
		//Beat !
		cout << "BEAT!" << endl;

	}*/

	if (bSequence == true)
	{
		//curSegment =
		curSegment = ofxOpenVJUtils::Instance()->getFrameAtNormalized( soundManager->beatPerc, numSegments); 
	}

}

void SectionColorJumpScene::newBeatHandler()
{
	cout << "SectionColorJumpScene::newBeatHandler! @" << ofGetElapsedTimef() << endl;
	curSegment++;

	if (curSegment >= numSegments)
	{
		curSegment = 0;
	}

	curAngle += ( angleStep * 15 ) ; 
}

void SectionColorJumpScene::draw()
{
	ofPushMatrix(); 

		ofTranslate(ofGetWidth() / 2, ofGetHeight() / 2 ); 
		ofRotateZ( curAngle ); 
		ofRectangle r = ofRectangle( 0 , 0 , ofGetWidth() / ( numSegments * 2 ) ,  ofGetHeight() );
		ofTranslate(-ofGetWidth() / 2, -ofGetHeight() / 2); 
		if (bHorizontal)
		{
			//ofRotateZ( ofGetElapsedTimef() ); 
			r.width = ofGetWidth(); 
			r.height = ofGetHeight() / (numSegments * 2); 
			drawHorizontalBars(r);
		}
		else
		{
			drawVerticalBars( r ); 
		}
		

		ofPushMatrix(); 

			if (bHorizontal) 
			{
				ofTranslate( 0 , ofGetHeight() ) ;
				ofScale(1, -1, 1);
			}
			else
			{
				ofTranslate(ofGetWidth(), 0);
				ofScale(-1, 1, 1);
			}
			if (bHorizontal)
			{
				drawHorizontalBars(r);
			}
			else
			{
				drawVerticalBars(r);
			}
		ofPopMatrix(); 

	ofPopMatrix(); 
}

void SectionColorJumpScene::drawVerticalBars( ofRectangle r )
{
	for (int i = 0; i < numSegments; i++)
	{
		if (i == curSegment)
		{
			ofSetColor(segmentColor);
			ofRect(i * r.width, -r.height * 2 , r.width , r.height * 4);
		}
	}
}


void SectionColorJumpScene::drawHorizontalBars(ofRectangle r)
{
	for (int i = 0; i < numSegments; i++)
	{
		if (i == curSegment)
		{
			ofSetColor(segmentColor);
			ofRect( -r.width*2 , i * r.height, r.width * 4 , r.height );
		}
	}
}

bool SectionColorJumpScene::transitionIn( float delay , float transitionTime )
{
    
    if ( BaseScene::transitionIn( delay , transitionTime ) == false )
        return false ;
    else
    {
        cout << "simple scene transitionin ! " << endl ; 

    }

    return true ;
}

bool SectionColorJumpScene::transitionOut( float delay , float transitionTime )
{
    if ( BaseScene::transitionOut( delay , transitionTime ) == false )
        return false ;
    else
    {
        
    }
    return true ;
}

void SectionColorJumpScene::drawDebug( )
{
	sceneTransitionTimer.draw(50 , 50);
}

void SectionColorJumpScene::activate()
{
    BaseScene::activate() ; 
}

void SectionColorJumpScene::deactivate()
{
    BaseScene::deactivate() ; 
}
