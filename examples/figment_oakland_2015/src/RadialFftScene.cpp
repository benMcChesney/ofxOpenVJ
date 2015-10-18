//
//  TestScene.cpp
//  KinectPerformanceV01
//
//  Created by Ben McChesney on 11/6/12.
//
//

#include "RadialFftScene.h"

//--------------------------------------------------------------
RadialFftScene::RadialFftScene() {
    
}

//--------------------------------------------------------------
RadialFftScene::~RadialFftScene() {
    
}

//--------------------------------------------------------------
void RadialFftScene::setup() {
    
}

//--------------------------------------------------------------
void RadialFftScene::setupGui(float a_x, float a_y)
{
    // creates new gui and adds the name to it //
    BaseScene::setupGui(a_x, a_y);
   
	gui.add( maxRadius.setup( "MAX RADIUS" , 400.0f , 50.0f , 1200.0f ) );
	gui.add( minRadius.setup( "MIN RADIUS" , 200.0f , 25.0f , 1100.0f ) ) ;
	gui.add( smoothedAmount.setup( "SMOOTHING" , 3.0f , 0.0f, 25.0f )) ;
	gui.add(resampledAmount.setup("RESAMPLED AMOUNT", 32, 5, 300 )); 
	ofxFloatSlider ;
   // ofAddListener( gui->newGUIEvent, this, &EmptyScene::guiEvent );
    loadSettings() ; 
}

void RadialFftScene::newBeatHandler()
{
	cout << "RadialFftScene::newBeatHandler" << endl;
}

//--------------------------------------------------------------
void RadialFftScene::activate() {
    
	BaseScene::activate(); 
}

//--------------------------------------------------------------
void RadialFftScene::deactivate() {
    
    // turn off the gui //
    BaseScene::deactivate();
}

//--------------------------------------------------------------
void RadialFftScene::update() {
}

//--------------------------------------------------------------
void RadialFftScene::draw() 
{
	FftRadialShape s; 
	ofColor c = ofColor::fromHsb( ofGetFrameNum() %  255, 255, 255);
	ofSetColor(c); 
	ofPolyline p;
	
	float numBands = (float) FFT_SUBBANDS; 
	float perTheta = 360.0f / numBands; 

	ofPushMatrix(); 
	ofTranslate(ofGetWidth() / 2, ofGetHeight() / 2); 

	//ofCircle(0, 0, 5); 

	for (int i = 0; i < numBands; i++)
	{
		ofPushMatrix();
		ofPoint pt; 
		/* 
		r=sqrt(x*x+y*y)
a=atan(x/y)


x=r*cos(a);
y=r*sin(a);
*/
		
		
			float radius = ofMap(soundManager->beatTracker.getBand(i), 0.0f, 1.0f, minRadius, maxRadius, true); 
			float theta = perTheta * i; 

			float x = radius * cos( ofDegToRad( theta ) ); 
			float y = radius * sin( ofDegToRad( theta ) );

			p.addVertex( ofPoint ( x , y )  ); 

			theta = perTheta * ( i + 0.5 ) ;
			radius = minRadius; 
			x = radius * cos(ofDegToRad(theta));
			y = radius * sin(ofDegToRad(theta));

			p.addVertex(ofPoint(x, y));
			//ofRotateZ();	
				
			//ofRect(-4, maxRadius, 8, radius - minRadius );
		ofPopMatrix(); 
	}


	p.close();
	p = p.getResampledByCount(resampledAmount);
	p = p.getSmoothed(smoothedAmount); 
	
	ofPath path; 

	vector< ofPoint > verts = p.getVertices(); ; 
	for (int v = 0; v < verts.size(); v++)
	{
		path.lineTo(verts[v]); 
	}

	path.setColor(c); 
	path.setFilled(true); 
	path.draw(); 
	//p.draw();


	ofPopMatrix(); 




	
}

void RadialFftScene::drawDebug() {
	BaseScene::drawDebug(); 
}

bool RadialFftScene::transitionIn(float delay, float transitionTime)
{

	if (BaseScene::transitionIn(delay, transitionTime) == false)
		return false;
	else
	{
		cout << "simple scene transitionin ! " << endl;
		//Build the scene out
		//Tweenzor::add(&drawNumCubes, 0.0f, (float)numCubes, delay, transitionTime, EASE_OUT_QUAD);
	}

	return true;
}

bool RadialFftScene::transitionOut(float delay, float transitionTime)
{
	if (BaseScene::transitionOut(delay, transitionTime) == false)
		return false;
	else
	{
		//Tweenzor::add(&drawNumCubes, numCubes, 0.0f, delay, transitionTime, EASE_OUT_QUAD);
	}
	return true;
}
