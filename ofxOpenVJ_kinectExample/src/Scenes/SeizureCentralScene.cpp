//
//  SeizureCentralScene.cpp
//  KinectPerformanceV01
//
//  Created by Nick Hardeman on 11/6/12.
//
//

#include "SeizureCentralScene.h"

//--------------------------------------------------------------
SeizureCentralScene::SeizureCentralScene()
{
    lastAddTime = ofGetElapsedTimeMillis();
}

//--------------------------------------------------------------
SeizureCentralScene::~SeizureCentralScene() {
    
}

//--------------------------------------------------------------
void SeizureCentralScene::setup() {
    hue     = ofRandom(1);
    hueDir  = 1;
    bOdd    = true;
    millisDelay = 2500 ;
    contourSoundThreshold = 0.25 ; 
}

//--------------------------------------------------------------
void SeizureCentralScene::setupGui(float a_x, float a_y) {
    // creates new gui and adds the name to it //
    BaseScene::setupGui(a_x, a_y);
    
    float dim = 30;
	float xInit = OFX_UI_GLOBAL_WIDGET_SPACING;
    float length = 320-xInit;

    
    int width = 300 ;
    int height = 18 ;

    gui->addSlider( "CONTOUR DELAY" , 15 , 2500 , millisDelay , width, height) ;
    gui->addSlider( "HUE INCREMENT" , 0.0 , 0.5 , hueIncrement , width, height) ;
    gui->addSlider( "HUE NOISE OFFSET" , 0.0 , 1.0 , hueNoiseOffset , width, height) ;
    gui->addSlider( "Z FORCE" , -200.0 , 200.0 , zForce , width, height) ;
    gui->addSlider( "RADIUS" , 0.0 , 1800.0 , radius , width, height) ;

    gui->addSlider( "RADIUS TIME" ,  0.0 , 6.0f , radius , width, height) ;
    gui->addSlider( "SPIRAL FACTOR" , 0.0 , 0.6f , spiralFactor , width, height) ;
    gui->addSlider( "NUM MESHES" , 1.0 , 350.0f , numTooManyOffset , width, height) ;
    gui->addSlider( "SPECIAL Z OFFSET" , -1000 , 1000 , specialZOffset , width , height ) ;
    gui->addSlider( "NOISE Z MULTIPLIER" , -1000 , 1000 , noiseZMultiplier , width , height ) ; 

    gui->addSlider ( "RESAMPLE LINE AMOUNT"  , 2 , 60 , resampleLineAmount , width , height ) ; 
    //resampleLineAmount
    ofAddListener( gui->newGUIEvent, this, &SeizureCentralScene::guiEvent );
    
}

//--------------------------------------------------------------
void SeizureCentralScene::guiEvent(ofxUIEventArgs &e) {
    string name = e.widget->getName();
	int kind = e.widget->getKind();
    
    if(name == "CONTOUR DELAY"  )
	{
		ofxUISlider *slider = (ofxUISlider *) e.widget;
        millisDelay = slider->getScaledValue() ;
	}
    
    if(name == "CONTOUR SOUND THRESHOLD" )
	{
		ofxUISlider *slider = (ofxUISlider *) e.widget;
        contourSoundThreshold = slider->getScaledValue() ;
	}
    
    if(name == "HUE INCREMENT" ) hueIncrement = ((ofxUISlider *) e.widget)->getScaledValue() ;
    if(name == "HUE NOISE OFFSET" ) hueNoiseOffset = ((ofxUISlider *) e.widget)->getScaledValue() ;

    if(name == "Z FORCE" ) zForce = ((ofxUISlider *) e.widget)->getScaledValue() ;
    if(name == "RADIUS" ) radius = ((ofxUISlider *) e.widget)->getScaledValue() ;
    if(name == "RADIUS TIME" ) radiusTime = ((ofxUISlider *) e.widget)->getScaledValue() ;
    if(name == "SPIRAL FACTOR" ) spiralFactor = ((ofxUISlider *) e.widget)->getScaledValue() ;
    if(name == "NUM MESHES" ) numTooManyOffset = ((ofxUISlider *) e.widget)->getScaledValue() ;

    if ( name == "SPECIAL Z OFFSET" )  specialZOffset = ((ofxUISlider *) e.widget)->getScaledValue() ;
    if ( name == "NOISE Z MULTIPLIER"  )  noiseZMultiplier = ((ofxUISlider *) e.widget)->getScaledValue() ;
    
    //    gui->addSlider ( "RESAMPLE LINE AMOUNT"  , 2 , 60 , resampleLineAmount , width , height ) ;
    if ( name ==  "RESAMPLE LINE AMOUNT" )  resampleLineAmount = ((ofxUISlider *) e.widget)->getScaledValue() ;
}

//--------------------------------------------------------------
void SeizureCentralScene::activate() {
    
}

//--------------------------------------------------------------
void SeizureCentralScene::deactivate() {
    // turn off the gui //
    BaseScene::deactivate();
}

//--------------------------------------------------------------
void SeizureCentralScene::addContour() {
    ofRectangle srcRect( 0,0, kinectMan->contourFinder.getWidth(), kinectMan->contourFinder.getHeight() );
    ofRectangle destRect( 0,0, getWidth(), getHeight() );
    ofRectangle newBounds = ofFitRectProportionallyInsideRect( srcRect, destRect );
    
    float offx = (getWidth() - newBounds.width) *.5;
    offx -= getWidth()/2;
    float offy = (getHeight() - newBounds.height) * .5f;
    offy -= getHeight()/2;
    
    vector<ofPolyline> newLines = kinectMan->getScaledContourPolyline( offx, offy, newBounds.width, newBounds.height );
    ofColor color( ofRandom(0, 255), ofRandom(10, 100), ofRandom(30, 55) );
    //ofColor color(255, 10, 50);
    color.setHue( hue*255.f );
    
    //if(bOdd) color.set(255);
    //else color.set(0);
    
    for(int i = 0; i < newLines.size(); i++ ) {
        ofPolyline resampled = newLines[i].getResampledByCount(resampleLineAmount);
        
        ofPath path;
        for( int j = 0; j < resampled.getVertices().size(); j++) {
            if(j == 0) {
                path.newSubPath();
                path.moveTo( resampled.getVertices()[j] );
            } else {
                path.lineTo( resampled.getVertices()[j] );
            }
        }
        
        path.close();
        path.simplify() ;
        path.setUseShapeColor(false);
        
        path.tessellate();
        ofMesh mesh = path.getTessellation();
        
        //lines.push_back(path);
        lines.push_back( mesh );
        offsets.push_back( ofVec3f() ) ;
        ofxParticle2D particle;
        particle.color = color;
        particle.radius = 0.5f ; + low  * 0.35f; // store the scale in here //
        particles.push_back( particle );
        
        /*
        float hue = sin ( ofGetElapsedTimef() * hueIncrement )  * 128.0f + 128.0f ;
        float hueNoise = ofSignedNoise( ofGetElapsedTimef()  ) * hueNoiseOffset ;
        hue += hueNoise ;
        if ( hue > 255 )
            hue -= 255 ; 
         */
        /*
        (( ofGetElapsedTimef() * hueIncrement )  + ofSignedNoise( ofGetElapsedTimef() ) * hueNoiseOffset ) ;
        while ( hue > 255 )
        {
            hue -= 255.0f ;
        }*/
        
        colors.push_back( ofColor::fromHsb( hue * 254.0f , 200 + ofNoise( ofGetElapsedTimef() ) * 55.0f , 255 ) ) ;
        //vector<ofColor> colors;
        
        bOdd = !bOdd;
    }
    
    lastAddTime = ofGetElapsedTimeMillis();

}

//--------------------------------------------------------------
void SeizureCentralScene::update() {
    kinectMan->update();
    
    //if ( low > contourSoundThreshold )
    //hue += (.3f * hueDir);
    
    hue += ( hueIncrement * hueDir + ofNoise( ofGetElapsedTimef() ) * hueNoiseOffset ) ;
    
    if(hue <= 0) {
        hueDir = 1; hue += 1 ;
    }
    if(hue >= 1) {
        hueDir = -1; hue -= 1;
    }
    
    //cout << "hue: " << hue << " dir = " << hueDir << endl;
    
    if(kinectMan->isFrameNew()) {
        kinectMan->calculateCVOperations();
        
        if( ( ofGetElapsedTimeMillis() - lastAddTime  ) > millisDelay ) {
            addContour();
            //cout << "lines.size() = " << lines.size() << " particles.size() = " << particles.size() << endl;
        }
    }
    
    int numTooMany = lines.size()-numTooManyOffset ;
    
    if(numTooMany > 0 ) {
        lines.erase( lines.begin(), lines.begin()+numTooMany );
        particles.erase( particles.begin(), particles.begin()+numTooMany);
        offsets.erase( offsets.begin() , offsets.begin() + numTooMany ) ;
        colors.erase( colors.begin() , colors.begin() + numTooMany ) ; 
    }
    
    for(int i = 0; i < particles.size(); i++) {
        ofxParticle2D& p = particles[i];
        p.radius += .03f + low * .6 ;
        
    }
    
    for(int i = 0; i < particles.size(); i++) {
        if(particles[i].radius > getHeight() / 3) {
            particles.erase( particles.begin() + i );
            break;
        }
    }
    
    float t = ofGetElapsedTimef() * radiusTime ;
    float r = radius + sin ( ofGetElapsedTimef() ) * (radius * .1) ;
    //offsets[ (offsets.size() - 1 ) ] ;
    for ( int i = 0 ; i < lines.size() ; i++ )
    {
        float fi = (float) i * spiralFactor ;
        offsets[ i ].x = 320 + sin ( fi  + t ) * r - r/2 ;//+ ( r / 2 ) ;
        offsets[ i ].y = 240 + cos ( fi  + t ) * r - r/2 ; //- ( r / 2 ) ;
        offsets[ i ].z += ( zForce * (0.1 + ofNoise( ofGetElapsedTimef() * noiseZMultiplier ))) ;
    }
    
    ofVec3f first = offsets[ ( offsets.size() - 1) ] ;
    for ( int i = 0 ; i < lines.size() ; i++ )
    {
        offsets[i].x -= first.x ;
        offsets[i].y -= first.y ;
    }

    
    /*
    offsets[ i ].x = 320 + sin ( fi  + t ) * r  ;//+ ( r / 2 ) ;
    offsets[ i ].y = 240 + cos ( fi  + t ) * r ; //- ( r / 2 ) ;
    offsets[ i ].z += ( zForce * (0.1 + ofNoise( ofGetElapsedTimef() * noiseZMultiplier ))) ;
     */
    
                           
}

//--------------------------------------------------------------
void SeizureCentralScene::draw() {
    

    if(particles.size()>0) {
        ofColor color = particles[0].color;
        //color.setBrightness(.8f * 255);
        //ofSetColor( color );
//        ofRect(0, 0, getWidth(), getHeight() );
    }
    
    
    cameraMan->begin() ;
//    kinectMan->post.begin( cameraMan->cam )  ;
    
    ofTranslate( -ofGetWidth() / 2 , -ofGetHeight() / 2 , specialZOffset ) ;
    float pct = 1.f;
    
    ofSetLineWidth(2);
    
    
    float t = ofGetElapsedTimef() ; 
    for(int i = 0; i < (int)lines.size(); i++) {
        float fi = (float) i ; 
        ofPushMatrix() ;
        
        ofTranslate( offsets[ i ] ) ;
        //pct = ((float)i/(float)lines.size());
        pct = ofMap(i, 0, lines.size(), .8, 1);
        
        ofxParticle2D& p = particles[i];
        //ofSetColor( p.color );
        
        glPushMatrix(); {
            glTranslatef(getWidth()/2, getHeight()/2, 0);
            glScalef(p.radius, p.radius, p.radius);
            
            //ofColor color = p.color;
            //color.setBrightness(pct * 255);
            ofSetColor( colors[ i ] );
            lines[i].draw();
            
        } glPopMatrix();
        ofPopMatrix() ; 
    }
    ofSetLineWidth(1);
    cameraMan->end( ) ;
   // kinectMan->post.end() ;
}

//--------------------------------------------------------------
void SeizureCentralScene::drawDebug() {
    
}






