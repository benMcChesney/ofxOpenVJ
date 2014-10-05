//
//  ColorOutlineScene.cpp
//  KinectPerformanceV01
//
//  Created by Nick Hardeman on 11/6/12.
//
//

#include "ColorOutlineScene.h"

//--------------------------------------------------------------
ColorOutlineScene::ColorOutlineScene()
{
    lastAddTime = ofGetElapsedTimeMillis();
}

//--------------------------------------------------------------
ColorOutlineScene::~ColorOutlineScene() {
    
}

//--------------------------------------------------------------
void ColorOutlineScene::setup() {
    hue     = ofRandom(1);
    hueDir  = 1;
    bOdd    = true;
    millisDelay = 2500 ;
    contourSoundThreshold = 0.25 ; 
}

//--------------------------------------------------------------
void ColorOutlineScene::setupGui(float a_x, float a_y) {
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
    gui->addSlider( "NUM MESHES" , 2.0 , 350.0f , numTooManyOffset , width, height) ;
    gui->addSlider( "SPECIAL Z OFFSET" , -1000 , 1000 , specialZOffset , width , height ) ;
    gui->addSlider( "NOISE Z MULTIPLIER" , -1000 , 1000 , noiseZMultiplier , width , height ) ; 

    gui->addSlider ( "RESAMPLE LINE AMOUNT"  , 2 , 460 , resampleLineAmount , width , height ) ;
    
    gui->addSlider("X OFFSET", -4000.0f , 4000.0f , &offset.x ) ;
    gui->addSlider("Y OFFSET", -4000.0f , 4000.0f , &offset.y ) ;
    gui->addSlider("Z OFFSET", -4000.0f , 4000.0f , &offset.z ) ;

    //resampleLineAmount
    ofAddListener( gui->newGUIEvent, this, &ColorOutlineScene::guiEvent );
    
}

//--------------------------------------------------------------
void ColorOutlineScene::guiEvent(ofxUIEventArgs &e) {
    string name = e.widget->getName();
	int kind = e.widget->getKind();
    
    BaseScene::guiEvent( e ) ; 
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

    if ( name ==  "RESAMPLE LINE AMOUNT" )  resampleLineAmount = ((ofxUISlider *) e.widget)->getScaledValue() ;
}


//--------------------------------------------------------------
void ColorOutlineScene::addContour()
{
    
    ofRectangle srcRect( 0,0, depthCameraManager->contourFinder.getWidth(), depthCameraManager->contourFinder.getHeight() );
    ofRectangle destRect( 0,0, getWidth(), getHeight() );
    ofRectangle newBounds = ofFitRectProportionallyInsideRect( srcRect, destRect );
    
    float offx = (getWidth() - newBounds.width) *.5;
    offx -= getWidth()/2;
    float offy = (getHeight() - newBounds.height) * .5f;
    offy -= getHeight()/2;
    
    vector<ofPolyline> newLines = ((KinectManager*)depthCameraManager)->getScaledContourPolyline( offx, offy, newBounds.width, newBounds.height );
    ofColor color(  0 , ofRandom(10, 100), ofRandom(30, 55) );
    //ofColor color(255, 10, 50);
    color.setHue( hue*255.f );
    
    if ( newLines.size() > 0 )
    {
        for(int i = 0; i < newLines.size(); i++ )
        {
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
            //ofPolyline mesh = path.getTessellation();
            
            lines.push_back( path );
            offsets.push_back( ofVec3f() ) ;
            ofxParticle2D particle;
            particle.color = color;
            particle.radius = 0.5f ;// + low  * 0.35f; // store the scale in here //
            particles.push_back( particle );
            
            colors.push_back( ofColor::fromHsb( hue * 254.0f , 200 + ofNoise( ofGetElapsedTimef() ) * 55.0f , 255 ) ) ;
            
            bOdd = !bOdd;
        }
    }
    
    lastAddTime = ofGetElapsedTimeMillis();

}

//--------------------------------------------------------------
void ColorOutlineScene::update()
{
    
    BaseScene::update( ) ;
    
    depthCameraManager->update();
    
    hue += ( hueIncrement * hueDir + ofNoise( ofGetElapsedTimef() ) * hueNoiseOffset ) ;
    
    if(hue <= 0) {
        hueDir = 1; hue += 1 ;
    }
    if(hue >= 1) {
        hueDir = -1; hue -= 1;
    }

    
    depthCameraManager->calculateCVOperations();
    
    if( ( ofGetElapsedTimeMillis() - lastAddTime  ) > millisDelay )
    {
        addContour();
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
        p.radius += .03f + .6 ;
        
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
        offsets[ i ].x = 320 ; //320 + sin ( fi  + t ) * r - r/2 ;//+ ( r / 2 ) ;
        offsets[ i ].y = 240 ; //240 + cos ( fi  + t ) * r - r/2 ; //- ( r / 2 ) ;
        offsets[ i ].z += ( zForce ) ; //* (0.1 + ofNoise( ofGetElapsedTimef() * noiseZMultiplier ))) ;
    }
    
    if ( offsets.size() > 2 )
    {
        ofVec3f first = offsets[ ( offsets.size() - 1) ] ;
        for ( int i = 0 ; i < lines.size() ; i++ )
        {
            //offsets[i].x -= first.x ;
            //offsets[i].y -= first.y ;
        }
    }
                           
}

void ColorOutlineScene::drawDebug( )
{
    BaseScene::drawDebug() ;
    
    stringstream ss ;
    ss << "# lines " << lines.size() << endl ;
    ss << "# offsets " << offsets.size() << endl ;
    ss << "# particles " << particles.size() << endl ;
    ss << "# colors " << colors.size() << endl ;
    
    if ( lines.size() > 0 )
    {
        ss << "particle  " << particles[0].x << " , " << ss << particles[0].y << " | radius : " << particles[0].radius << endl ;
        ss << "Offset " << offsets[0].x << " , " << ss << offsets[0].y << " , " << offsets[0].z << endl ;
        ss << "Lines# points  " << lines[0].getTessellation().getVertices().size() << endl ;
        
        lines[0].draw( 0 , 0 ) ;
    }
    ofDrawBitmapString( ss.str() , 600 , 60 );
}

//--------------------------------------------------------------
void ColorOutlineScene::draw()
{
    cameraManager->begin() ;
    
    ofPushMatrix()  ;
       // ofTranslate( -ofGetWidth() / 2 , -ofGetHeight() / 2 , specialZOffset ) ;
        float pct = 1.f;
        
        ofSetLineWidth(2);
        
        
        float t = ofGetElapsedTimef() ; 
        for(int i = 0; i < (int)lines.size(); i++)
        {
            float fi = (float) i ; 
            ofPushMatrix() ;
            
            ofTranslate( offsets[ i ] ) ;
            //pct = ((float)i/(float)lines.size());
            //pct = ofMap(i, 0, lines.size(), .8, 1);
            
            ofxParticle2D& p = particles[i];
            //glTranslatef(getWidth()/2, getHeight()/2, 0);
            //glScalef(p.radius, p.radius, p.radius);
        
            ofSetColor( colors[ i ] );
            lines[i].draw( );
        
            ofPopMatrix() ;
        }
    
    ofPopMatrix() ;
    ofSetLineWidth(1);
    cameraManager->end( ) ;
  
}



bool ColorOutlineScene::transitionIn( float delay , float transitionTime )
{
    if ( BaseScene::transitionIn( delay , transitionTime ) == false )
        return false ;
    else
    {
        alpha = 0.0f;
        Tweenzor::add( &alpha , alpha , 1.0f , delay , transitionTime ) ;
    }
    
    return true ;
}

bool ColorOutlineScene::transitionOut( float delay , float transitionTime )
{
    if ( BaseScene::transitionOut( delay , transitionTime ) == false )
        return false ;
    else
    {
        Tweenzor::add( &alpha , alpha , 0.0f , delay , transitionTime ) ;
    }
    return true ;
}






