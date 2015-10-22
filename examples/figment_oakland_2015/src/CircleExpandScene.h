//
//  SimpleScene.h
//  simpleExample
//
//  Created by Ben McChesney on 5/15/14.
//
//

#pragma once

#include "BaseScene.h"

class Shape
{
public :
	enum ShapeType
	{
		SQUARE, CIRCLE, DIAMOND, TRIANGLE
	};

	Shape() { }
	//1.0f , 5.0f , ofColor( 255 ) , Shape::SQUARE
	Shape( float _radius, float _maxRadius, ofColor _color, Shape::ShapeType _type , float _duration  )
	{
		radius = _radius; 
		maxRadius = _maxRadius;
		color = _color;
		bRemove = false ; 
		type = _type; 
		duration = _duration; 
	}


	float duration; 
	float radius; 
	float maxRadius; 
	ofColor color;
	bool bRemove; 
	ShapeType type; 

	void update()
	{
		
	}
	void draw()
	{
		ofPushMatrix(); 
		ofPushStyle(); 
			ofSetColor(color); 
			switch (type)
			{
				case SQUARE : 
					ofSetRectMode(OF_RECTMODE_CENTER); 
					ofRect(0, 0, radius, radius); 
					ofSetRectMode(OF_RECTMODE_CORNER);
					break; 

				case CIRCLE:
					ofCircle(0, 0, radius, radius); 
					break;

				case DIAMOND:
					ofRotateZ(45); 
					ofSetRectMode(OF_RECTMODE_CENTER);
					ofRect(0, 0, radius, radius);
					ofSetRectMode(OF_RECTMODE_CORNER);
					break;

				case TRIANGLE:
					ofTriangle(ofPoint(-radius / 2, -radius / 2), ofPoint(0, radius / 2), ofPoint(radius / 2, -radius / 2)); 
					break;
			}
		ofPopStyle(); 
		ofPopMatrix(); 
	}

	void tweenCompleteHandler(float * args)
	{
		cout << "remove me ! " << endl; 
		Tweenzor::add(&radius, maxRadius, maxRadius * 2, duration, 0.0f, EASE_LINEAR); 
		Tweenzor::addCompleteListener(Tweenzor::getTween(&radius), this, &Shape::tweenComplete2Handler); 
	}

	void tweenComplete2Handler(float * args)
	{
		cout << "remove me ! " << endl;
		bRemove = true;
	}

	ShapeType getRandomShapeType()
	{
		int index = floor( ofRandom(0, 4)) ; 
		switch (index)
		{
		case 0:
			return SQUARE;

		case 1:
			return CIRCLE;

		case 2:
			return DIAMOND ;

		case 3 :
			return TRIANGLE; 
		}
	}

	ShapeType getShapeTypeAtIndex(int index)
	{
		switch (index)
		{
		case 0:
			return SQUARE;

		case 1:
			return CIRCLE;

		case 2:
			return DIAMOND;

		case 3:
			return TRIANGLE;
		}

		return CIRCLE; 
	}
};

class CircleExpandScene : public BaseScene
{


public :
	CircleExpandScene() {}
	CircleExpandScene( int a_index, string a_name ):BaseScene( a_index, a_name ) {}

    void setup();
    void setupGui(float a_x=0, float a_y=0);
	void newBeatHandler(); 
//    void guiEvent(ofxUIEventArgs &e);
    
    void update();
    void draw();
	void drawDebug(); 
    
    void activate();
    void deactivate();
    
    bool transitionIn( float delay , float transitionTime );
    bool transitionOut( float delay , float transitionTime ) ;
    

	vector < Shape * > shapes; 
	ofxButton manualCreateShape;
	void manualCreateShapeListener(); 

	ofxToggle bRandomShape;
	ofxToggle bSquareShape; 
	ofxToggle bDiamondShape; 
	ofxToggle bTriangleShape; 
	ofxToggle bCircleShape; 
    
	ofFbo fbo; 
};
