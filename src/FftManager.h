//
//  FftManager.h
//  emptyExample
//
//  Created by Ben McChesney on 11/6/12.
//
//

#ifndef emptyExample_FftManager_h
#define emptyExample_FftManager_h

#include "ofxFft.h"
#include "ofxOsc.h"
#include "FftTrigger.h"
#include "ofxUI.h"
#include "MSABPMTapper.h"

#define MIC 0
#define NOISE 1
#define SINE 2

#define HOST "localhost"
#define PORT 12345

enum Trigger_Mode_t {TM_NONE=0, TM_SETTING, TM_MOVING, TM_NAMING};


class FftManager
{
    public : 
        void setup ( bool bListen = false ) ;
        void update ( ) ;
        void draw ( ) ;
        
        void loadSettings();
        void saveSettings();
        void drawTriggers();
        void checkTriggers();
        float lerpAmount ; 

        // ofxFft related
        void plot(float* array, int length, float yScale, int xScale, float yOffset);
    
        void audioReceived(float* input, int bufferSize, int nChannels);

	
        void keyPressed  ( ofKeyEventArgs &args );
        void mouseDragged( ofMouseEventArgs &args );
        void mousePressed( ofMouseEventArgs &args );
        void mouseReleased( ofMouseEventArgs &args );
   
        int bufferSize;
        ofxFft* fft;
        float* audioInput;
        float* fftOutput;
        float* eqFunction;
        float* eqOutput;
        float* ifftOutput;

        // ofxFft related app values
        int mode;
        bool useEQ;
            
        vector <FftTrigger> triggers;
        
        //trigger stuff for drawing.
        ofPoint oldMouse;
        bool settingTrigger;
        Trigger_Mode_t triggerMode;
        int selTrigger;
        
        //ofxUI
        ofxUICanvas *gui;
        void guiEvent(ofxUIEventArgs &e);
        void setupOfxUI( ) ;
        
        bool bClearXml ;
        bool bGuiEnabled ;
        
        float amplitudeScale ; 
		float amplitudeFriction ; 
        float triggerDelay ;
        
        void createNewTrigger ( float x , float y ) ;
        
        // OSC related
        ofxOscSender sender;
        void handleOSC();
        void sendSpectrum();
        void sendTriggers();
        bool sendFullSpectrum;
    
        float mouseX , mouseY ;
    
        bool bEditable ;
    
        ofxOscReceiver receiver ;
        void setupOSCReceiver( int port = 12345 ) ;
        void parseOSC() ;
        bool bListenToOsc ;
    
        
        float lowRange ;
        float midRange ;
        float highRange ;
    
        
};


#endif
