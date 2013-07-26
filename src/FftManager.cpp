//
//  FftManager.cpp
//  emptyExample
//
//  Created by Ben McChesney on 11/6/12.
//
//

#include "FftManager.h"


void FftManager::setup ( bool bListen )
{
    lerpAmount = 0.5 ; 
    bEditable = false ; 
    bufferSize = 512;
    
    bListenToOsc = bListen ; 
	/*
    //If we are listening from the OSC app we don't need any of this
    if ( bListenToOsc == false )
    {
        fft = ofxFft::create(bufferSize, OF_FFT_WINDOW_BARTLETT);
        // To use with FFTW, try:
        // fft = ofxFft::create(bufferSize, OF_FFT_WINDOW_BARTLETT, OF_FFT_FFTW);
        
        audioInput = new float[bufferSize];
        fftOutput = new float[fft->getBinSize()];
        eqFunction = new float[fft->getBinSize()];
        eqOutput = new float[fft->getBinSize()];
        //ifftOutput = new float[bufferSize];
        
        // 0 output channels,
        // 1 input channel
        // 44100 samples per second
        // [bins] samples per buffer
        // 4 num buffers (latency)
        
        
        // this describes a linear low pass filter
        for(int i = 0; i < fft->getBinSize(); i++)
            eqFunction[i] = (float) (fft->getBinSize() - i) / (float) fft->getBinSize();
        
        mode = MIC;
        
        // OSC setup
        // open an outgoing connection to HOST:PORT
        sender.setup( HOST, PORT );
    }
    */
    lowRange = 0.0f ;
    midRange = 0.0f ;
    highRange = 0.0f ;
    
    loadSettings();
    
    ofSetFrameRate(30);
    
    triggerMode = TM_NONE;
    
    selTrigger = -1;
    
    bGuiEnabled = false ;
    amplitudeScale = 1.0f ;
    triggerDelay = 0.1f ;
    bListenToOsc = false ; 
    
    //if ( bListenToOsc == false )
    //     setupOfxUI( ) ;
    /*
    ofAddListener( ofEvents().mouseDragged, this, &FftManager::mouseDragged ) ;
    ofAddListener( ofEvents().mousePressed, this, &FftManager::mousePressed ) ;
    ofAddListener( ofEvents().mouseReleased, this, &FftManager::mouseReleased ) ;
    ofAddListener( ofEvents().keyPressed, this, &FftManager::keyPressed ) ;
    */
   

}

void FftManager::setupOSCReceiver( int port )
{
    receiver.setup( port ) ;
    bListenToOsc = true ;
}

void FftManager::parseOSC()
{
    if ( bListenToOsc == true )
    {
//        cout << "waiting for message! " << endl ;
        while ( receiver.hasWaitingMessages() )
        {
            
            ofxOscMessage m ;
            receiver.getNextMessage( &m ) ;
            
           //cout << "receiveer::address : " << m.getAddress() << endl ;
            
            /*
             lowRange = 0.0f ;
             mediumRange = 0.0f ;
             highRange = 0.0f ;
             */
            
            int isTriggered = m.getArgAsInt32(0) ;
            float friction = 0.85f ;
            
            if ( m.getAddress() == "/low" )
            {
                if ( isTriggered == 1 )
                    lowRange = ofLerp( lowRange , m.getArgAsFloat( 1 ) , lerpAmount ) ;
                else
                    lowRange *= friction ; 
                    
            }
            if ( m.getAddress() == "/mid" )
            {
                if ( isTriggered == 1 )
                    midRange = ofLerp( lowRange , m.getArgAsFloat( 1 ) , lerpAmount ) ;
                else
                    midRange *= friction ; 
                
            }
                
            if ( m.getAddress() == "/high" )
            {
                if ( isTriggered == 1  )
                    highRange = ofLerp( lowRange , m.getArgAsFloat( 1 ) , lerpAmount ) ;
                else
                    highRange *= friction ; 
            }
        }
    }
}

void FftManager::update ( )
{
    if ( bListenToOsc )
    {
        parseOSC( ) ;
    }
    else
    {
        handleOSC( ) ;
        for ( int t = 0 ; t < triggers.size() ; t++ )
        {
            triggers[t].update() ;
        }
    }

}


void FftManager::draw ( )
{
    drawTriggers();
	ofSetColor( 255 , 255 , 255 ) ;
	
    ofPushMatrix() ;
    ofTranslate(0, ofGetHeight()-16, 0 ) ;
    if(useEQ)
    {
        ofDrawBitmapString("EQd FFT Output", 2, 13);
       // plot(eqOutput, fft->getBinSize(), -512, 4, 0);
    }
    else
    {
        ofDrawBitmapString("FFT Output", 2, 13);
      //  plot(fftOutput, fft->getBinSize(), -512, 4, 0);
    }
	ofPopMatrix() ;
}


//--------------------------------------------------------------
void FftManager::loadSettings(){
	useEQ = false;
	sendFullSpectrum = true;
	
	ofxXmlSettings XML;
	
	if(XML.loadFile("fft_osc_settings.xml"))
	{
		if(XML.getValue("prefs:Send_Full_Spectrum", "true", 0)=="false")
			sendFullSpectrum = false;
		
		int numTriggers = XML.getNumTags("Trigger");
		
		for(int i=0;i<numTriggers;i++)
		{
			FftTrigger newTrigger;
            float lowBand = XML.getValue("Trigger:low_band", 0, i);
            float highBand = XML.getValue("Trigger:high_band", 10, i);
            newTrigger.setup( lowBand , highBand ) ;
			newTrigger.name = XML.getValue("Trigger:name", "error", i);
			newTrigger.height = XML.getValue("Trigger:height", 0.5f, i);
            newTrigger.maxFreq = XML.getValue("Trigger:maxFreq", 10.0f, i ) ;
            
			newTrigger.hit = false;
			newTrigger.sent = false;
			
			triggers.push_back(newTrigger);
		}
	}
	else {
		saveSettings();
	}
	
}

void FftManager::saveSettings()
{
	ofxXmlSettings XML;
	
	XML.addTag("prefs");
	if(sendFullSpectrum)
		XML.setValue("prefs:Send_Full_Spectrum", "true", 0);
	else {
		XML.setValue("prefs:Send_Full_Spectrum", "false", 0);
	}
	
	for(int t=0;t<triggers.size();t++)
	{
		XML.addTag("Trigger");
		XML.setValue("Trigger:name", triggers[t].name, t);
		XML.setValue("Trigger:low_band", triggers[t].lowBand, t);
		XML.setValue("Trigger:high_band", triggers[t].highBand, t);
		XML.setValue("Trigger:height", triggers[t].height, t);
        XML.setValue("Trigger:maxFreq", triggers[t].maxFreq, t);
       // XML.setValue("Trigger:minFreq", triggers[t].minFreq, t);
	}
	
	
	XML.saveFile("fft_osc_settings.xml");
}



void FftManager::drawTriggers()
{
	for(int t=0;t<triggers.size();t++)
	{
		triggers[t].draw ( ) ;
	}
	
	if(triggerMode == TM_SETTING)
	{
		if(oldMouse.x>mouseX)
			ofSetColor(180,100,100);
		else
			ofSetColor(0,180,0);
		ofLine(oldMouse.x, mouseY, mouseX, mouseY);
	}
}

/*
void FftManager::plot(float* array, int length, float yScale, int xScale, float yOffset) {
	ofNoFill();
	ofSetColor(80,80,80);
	ofRect(0, 0, length*xScale, yScale);
	ofSetColor(255,255,255);
	
	glPushMatrix();
	glTranslatef(0,yOffset,0);
	
	ofBeginShape();
	for (int i = 0; i < length; i++) {
		ofVertex(i*xScale, array[i] * yScale);
	}
	ofEndShape();
	
	glPopMatrix();
}

void FftManager::audioReceived(float* input, int bufferSize, int nChannels)
{
    
    if (mode == MIC)
        memcpy(audioInput, input, sizeof(float) * bufferSize);
    
    for ( int b = 0 ; b < bufferSize ; b++ )
        audioInput[b] *= amplitudeScale ;
    
    fft->setSignal(audioInput);
    memcpy(fftOutput, fft->getAmplitude(), sizeof(float) * fft->getBinSize());
    
    if(useEQ)
    {
        for(int i = 0; i < fft->getBinSize(); i++)
            eqOutput[i] = fftOutput[i] * eqFunction[i] * amplitudeScale ;
    }
    
    fft->setPolar(eqOutput, fft->getPhase());
    
    fft->clampSignal();
    
    checkTriggers();

}
*/

void FftManager::handleOSC()
{
    if ( bListenToOsc == false )
    {
        if(sendFullSpectrum)
            sendSpectrum();
        sendTriggers();
    }
}

void FftManager::sendSpectrum()
{
	ofxOscMessage m;
	
	m.clear();
	m.setAddress( "/spectrum" );
//	for(int i=0;i<fft->getBinSize();i++)
//		m.addFloatArg(fftOutput[i]);
//	sender.sendMessage( m );
    
    
}


void FftManager::sendTriggers()
{
	
	for(int t=0;t<triggers.size();t++)
	{
        ofxOscMessage m;
        
        m.clear();
        
        m.setAddress( "/"+triggers[t].name );
        
        
		if(triggers[t].hit)
		{
			m.addIntArg(1);
            triggers[t].sent=true;
		}
        else
        {
            m.addIntArg( 0 ) ; 
        }
        
        m.addFloatArg( triggers[t].averageAmplitude ) ;
            
        sender.sendMessage( m );
	}
}

/*
void FftManager::checkTriggers()
{
	for(int t=0;t<triggers.size();t++)
	{
        triggers[t].averageAmplitude = 0.0f ;
        //if ( triggers[t].trigger() == true )
        //{
        float sumAmplitude = 0.0f ;
        int amplitudeCount = 0 ;
        //float bandRange = triggers[t].highBand - triggers[t].lowBand ;
        for(int b=0;b<fft->getBinSize();b++)
        {
            float amplitude ;
            float maxFreq = triggers[t].maxFreq ;
            float minFreq = triggers[t].minTriggerDelay ;
            
            if(b >= triggers[t].lowBand && b <= triggers[t].highBand)
            {
                
                if(useEQ)
                {
                    amplitude = eqOutput[b] ;
                    
                    if(eqOutput[b]>triggers[t].height)
                        triggers[t].trigger() ; //hit=true;
                }
                else {
                    amplitude = fftOutput[b] ;
                    //sumAmplitude+= fftOutput[b] ;
                    if(fftOutput[b]>triggers[t].height)
                        triggers[t].trigger() ; //xhit=true;
                }
                
                if ( amplitude >= triggers[t].minTriggerDelay )
                {
                    if ( amplitude > maxFreq )
                    {
                        amplitude = maxFreq ;
                    }
                    sumAmplitude += amplitude ;
                    amplitudeCount++ ;
                }
                
            }
            else {
                if(b > triggers[t].highBand )
                    break;
            }
        }
        
        if ( amplitudeCount > 0 )
        {
            sumAmplitude /= ((float) amplitudeCount ) ;
            sumAmplitude *= amplitudeScale ;
            if ( sumAmplitude > 1.0f )
                sumAmplitude = 1.0f ;
            triggers[t].averageAmplitude = sumAmplitude ;
        }
		//}
	}
}

//--------------------------------------------------------------
void FftManager::mouseDragged(ofMouseEventArgs &args ){
    
    if ( bEditable == false ) return ; 
    int x = args.x ;
    int y = args.y ;
    int button = args.button ;
    
	if(y>ofGetHeight()-528  && triggerMode == TM_MOVING && y<ofGetHeight()-16)
	{
		if(triggers[selTrigger].lowBand + x/4 >= 0 && (x/4)+triggers[selTrigger].highBand-triggers[selTrigger].lowBand <= 256)
		{
			triggers[selTrigger].highBand = (x/4)+triggers[selTrigger].highBand-triggers[selTrigger].lowBand;
			triggers[selTrigger].lowBand = x/4;
            triggers[selTrigger].updateBands( ) ;
			triggers[selTrigger].height = (float(y - ofGetHeight()+16)*-1)/512;
		}
		oldMouse.set(x,y);
	}
}

//--------------------------------------------------------------
void FftManager::mousePressed(ofMouseEventArgs &args ){
    
        if ( bEditable == false ) return ; 
    int x = args.x ;
    int y = args.y ;
    int button = args.button ;
    
    cout << "mousePressed(" <<x << " , " << y << " button : " << button << endl;
	if(y>ofGetHeight()-528 && triggerMode != TM_NAMING && y<ofGetHeight()-16)
	{
        cout << "correct coordinates!" << endl ; 
		if(triggerMode == TM_NONE)
		{
            cout << "correct trigger mode!" << endl; 
			//check to see if its touching any triggers here.
			for(int t=0;t<triggers.size();t++)
			{
                if ( triggers[t].hitTest( x , y ) == true )
                {
                    //lowBand
                    selTrigger = t;
					break;
                }
     
			}
			
			
			if(selTrigger != -1)
			{
				if(button==0)
				{
					oldMouse.set(x,y);
					triggerMode = TM_MOVING;
				}
				if ( button == 1 )
				{
                    if ( triggers.size() > 0 )
                        triggers.erase(triggers.begin()+selTrigger);
				}
                
			}
            if ( button == 2 )
            {
                cout << "left button !!! should be adjusting min/max amps" << endl ;
                //Left button
                for(int t=0 ; t<triggers.size() ; t++ )
                {
                    if ( triggers[t].hitTestX( mouseX ) == true )
                    {
                        
                        float _adjustedY = mouseY - 240 ;
                        float adjustedY = (512 - _adjustedY) / 512.0f ;
                        cout << "adjustedY " << _adjustedY << endl ;
                        int aboveOrBelow = triggers[t].aboveOrBelow( mouseY ) ;
                        if ( aboveOrBelow == 1 )
                        {
                            triggers[t].minTriggerDelay = adjustedY ;
                        }
                        if ( aboveOrBelow == -1 )
                        {
                            triggers[t].maxFreq = adjustedY ;
                        }
                        
                        //lowBand
                        selTrigger = t;
                        break;
                    }
                }
            }
		}
	}
}

//--------------------------------------------------------------
void FftManager::mouseReleased(ofMouseEventArgs &args )
{
    
    if ( bEditable == false ) return ;
    
    int x = args.x ;
    int y = args.y ;
    int button = args.button ;
    
	if(y>ofGetHeight()-528 && y<ofGetHeight()-16)
	{
		if(triggerMode==TM_SETTING && triggerMode != TM_NAMING && x > oldMouse.x)
		{
			FftTrigger newTrigger;
            float lowBand = oldMouse.x/4.0f ;
            float highBand = x/4.0f ;
            newTrigger.setup( lowBand ,highBand ) ;
			newTrigger.height = (float(y - ofGetHeight()+16)*-1)/512;
			newTrigger.name = "[enter name]";
			
			newTrigger.hit = false;
			newTrigger.sent = false;
			
			triggers.push_back(newTrigger);
			triggerMode = TM_NAMING;
		}
		if(triggerMode==TM_MOVING)
		{
			selTrigger=-1;
			triggerMode = TM_NONE;
		}
	}
}


//--------------------------------------------------------------
void FftManager::keyPressed(ofKeyEventArgs &args){
    int key = args.key ;
       
    
    if ( bEditable == false ) return ;

	if(triggerMode == TM_NAMING)
	{
		if(key==13)//return
		{
			if(triggers[triggers.size()-1].name == "[enter name]")
				triggers[triggers.size()-1].name = "untitled_"+ofToString((int)triggers.size());
			
			triggerMode = TM_NONE;
		}
		else if(key == 127)//delete
		{
			if(triggers[triggers.size()-1].name.size()>0)
				triggers[triggers.size()-1].name = triggers[triggers.size()-1].name.substr(0,triggers[triggers.size()-1].name.size()-1);
			
			if(triggers[triggers.size()-1].name.size()==0)
				triggers[triggers.size()-1].name = "[enter name]";
		}
		else if(key == 32)
		{
			triggers[triggers.size()-1].name+="_";
		}
		else
		{
			if(triggers[triggers.size()-1].name == "[enter name]")
				triggers[triggers.size()-1].name = "";
			
			triggers[triggers.size()-1].name+=char(key);
		}
	}
    else
    {
        //cout << "keyPressed : " << key << endl;
        switch ( key )
        {
            case 'g':
            case 'G':
                bGuiEnabled = !bGuiEnabled ;
                break ;
                
            case 356:
                for ( int t = 0 ; t < triggers.size() ; t++ )
                {
                    if ( triggers[t].hitTest( mouseX , mouseY ) == true )
                    {
                        if( triggers[t].highBand > 0 )
                            triggers[t].highBand -= 1 ;
                        break;
                    }
                }
                
                break ;
                
            case 358:
                for ( int t = 0 ; t < triggers.size() ; t++ )
                {
                    if ( triggers[t].hitTest( mouseX , mouseY ) == true )
                    {
                        if( triggers[t].highBand < fft->getBinSize() )
                            triggers[t].highBand += 1 ;
                        break;
                    }
                }
                break ;
                
            case ',':
            case '<':
                for ( int t = 0 ; t < triggers.size() ; t++ )
                {
                    if ( triggers[t].hitTest( mouseX , mouseY ) == true )
                    {
                        if( triggers[t].lowBand > 0 )
                            triggers[t].lowBand -= 1 ;
                        break;
                    }
                }
                
                break ;
                
            case '.':
            case '>':
                for ( int t = 0 ; t < triggers.size() ; t++ )
                {
                    if ( triggers[t].hitTest( mouseX , mouseY ) == true )
                    {
                        if( triggers[t].lowBand < fft->getBinSize() )
                            triggers[t].lowBand += 1 ;
                        break;
                    }
                }
                
                
                break ;
                
            case 's':
            case 'S':
                saveSettings() ;
                break ;
                
                //createNewTrigger
            case 'n' :
            case 'N' :
                createNewTrigger( mouseX , mouseY ) ;
                break ;
                
        }
        
        
    }
}
*/
void FftManager::createNewTrigger ( float x , float y )
{
    if(y>ofGetHeight()-528 && triggerMode != TM_NAMING && y<ofGetHeight()-16)
	{
        oldMouse.set(x,y);
        triggerMode = TM_SETTING;
    }
}


void FftManager::guiEvent(ofxUIEventArgs &e)
{
    string name = e.widget->getName();
	int kind = e.widget->getKind();
	
	if(name == "CLEAR XML")
	{
		ofxUIToggle *toggle = (ofxUIToggle *) e.widget;
		bClearXml = toggle->getValue();
        if ( bClearXml == true )
        {
            cout << "CLEARING XML!!" << endl ;
            ofxXmlSettings XML;
            XML.saveFile("settings.xml");
            triggers.clear() ;
        }
	}
    if ( name == "AMPLITUDE SCALE" )
    {
        ofxUISlider *slider = (ofxUISlider *) e.widget;
		amplitudeScale = slider->getScaledValue();
        //cout << "value: " << slider->getScaledValue() << endl;
    }
    
    if ( name == "TRIGGER DELAY" )
    {
        ofxUISlider *slider = (ofxUISlider *) e.widget;
		triggerDelay = slider->getScaledValue();
        for ( int t = 0 ; t < triggers.size() ; t++ )
        {
            triggers[t].minTriggerDelay = triggerDelay ;
        }
        cout << "changing minTrigger delay to " << triggerDelay << endl ;
        //cout << "value: " << slider->getScaledValue() << endl;
    }
    
    if ( name == "SEND FULL FFT" )
    {
        ofxUIToggle *toggle = (ofxUIToggle *) e.widget;
		sendFullSpectrum = toggle->getValue();
        //cout << "value: " << slider->getScaledValue() << endl;
    }
    
    if ( name == "USE EQ" )
    {
        ofxUIToggle *toggle = (ofxUIToggle *) e.widget;
		useEQ = toggle->getValue() ; 
    }
    
    if ( name == "LISTEN TO OSC" )
    {
        ofxUIToggle *toggle = (ofxUIToggle *) e.widget;
		bListenToOsc = toggle->getValue();
        //cout << "value: " << slider->getScaledValue() << endl;
    }
    
    if ( name == "EDIT TRIGGERS" )
    {
        ofxUIToggle *toggle = (ofxUIToggle *) e.widget;
		bEditable = toggle->getValue();
        //cout << "value: " << slider->getScaledValue() << endl;
    }
  
    gui->saveSettings("GUI/fft.xml") ;
}

void FftManager::setupOfxUI()
{
    cout << "settings up ofxUI!" << endl ;
    bClearXml = false ;
    
    float dim = 24;
	float xInit = OFX_UI_GLOBAL_WIDGET_SPACING;
    float length = 200 ;
	
    gui = new ofxUICanvas(0, 0, ofGetWidth() , 300 );
	
    gui->addToggle( "CLEAR XML" , bClearXml );
    gui->addToggle( "SEND FULL FFT" , sendFullSpectrum );
    gui->addToggle( "LISTEN TO OSC" , bListenToOsc );
    gui->addToggle( "USE EQ" , useEQ );
    gui->addToggle( "EDIT TRIGGERS" , bEditable );
    
    gui->addSlider("AMPLITUDE SCALE" , 0.0 , 10.0f , amplitudeScale, length , dim ) ; 
    gui->addSlider("TRIGGER DELAY" , 0.0, 0.50f , triggerDelay, length , dim ) ;
    //gui->addWidgetDown(new ofxUISlider(length-xInit,dim, 0.0,20.0f, amplitudeScale , "AMPLITUDE SCALE"));
    //gui->addWidgetRight(new ofxUISlider(length-xInit,dim, 0.0,1.20f, triggerDelay , "TRIGGER DELAY"));
    
    ofAddListener(gui->newGUIEvent,this,&FftManager::guiEvent);
    gui->loadSettings("GUI/fft.xml") ;
    
    //  gui->disable() ;
    
}




