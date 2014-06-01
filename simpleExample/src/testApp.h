#pragma once

#include "ofMain.h"
#include "ofxOpenVJ.h"
#include "Tweenzor.h"
#include "SceneList.h"


class testApp : public ofBaseApp{

  public:
	void setup();
    void exit();

	void update();
	void draw();
    
	void keyPressed  (int key);
	void keyReleased(int key);
	void mouseMoved(int x, int y );
	void mouseDragged(int x, int y, int button);
	void mousePressed(int x, int y, int button);
	void mouseReleased(int x, int y, int button);
	void windowResized(int w, int h);
	void dragEvent(ofDragInfo dragInfo);
	void gotMessage(ofMessage msg);
    
    void audioReceived(float* input, int bufferSize, int nChannels) ;
    
    ofxOpenVJSet set ; 
};
