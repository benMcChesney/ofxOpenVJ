//
//  BoxOffsetScene.cpp
//  KinectPerformanceV01
//
//  Created by Nick Hardeman on 11/7/12.
//
//

#include "BoxOffsetScene.h"

//--------------------------------------------------------------
BoxOffsetScene::BoxOffsetScene() {
    
}

//--------------------------------------------------------------
BoxOffsetScene::~BoxOffsetScene() {
    
}

//--------------------------------------------------------------
void BoxOffsetScene::setup() {
    mode = 4;
    numBeatHits = 0;
    angle = 0;
    maxBeatHits = 40;
}

//--------------------------------------------------------------
void BoxOffsetScene::setupGui(float a_x, float a_y) {
    // creates new gui and adds the name to it //
    BaseScene::setupGui(a_x, a_y);
    
    gui->addSlider("MaxBeatHits", 1, 100, &maxBeatHits, 300, 16 );
    
    ofAddListener( gui->newGUIEvent, this, &BoxOffsetScene::guiEvent );
}

//--------------------------------------------------------------
void BoxOffsetScene::guiEvent(ofxUIEventArgs &e) {
    
}

//--------------------------------------------------------------
void BoxOffsetScene::activate() {
    numBeatHits = 0;
}

//--------------------------------------------------------------
void BoxOffsetScene::deactivate() {
    // turn off the gui //
    BaseScene::deactivate();
}

//--------------------------------------------------------------
void BoxOffsetScene::update() {
    kinectMan->update();
    
    if(kinectMan->isFrameNew()) {
        kinectMan->calculateCVOperations();
        
        ofRectangle srcRect( 0,0, kinectMan->contourFinder.getWidth(), kinectMan->contourFinder.getHeight() );
        ofRectangle destRect( 0,0, getWidth(), getHeight() );
        ofRectangle newBounds = ofFitRectProportionallyInsideRect( srcRect, destRect );
        
        float offx = (getWidth() - newBounds.width) * .25;
        float offy = (getHeight() - newBounds.height) * .75;
        
        vector<ofRectangle> brects = kinectMan->getScaledContourBoundingBoxes( offx, offy, newBounds.width, newBounds.height );
        if(brects.size() > 0) {
            targetRect = brects[0];
        }
    }
    
    // (x * (1 - a_pct)) + (a_x * a_pct);
    float xenoPct = .075f;
    float xenoVal = blobRect.width;
    float tval = targetRect.width;
    blobRect.width = (xenoVal * (1.f - xenoPct)) + (tval * xenoPct);
    
    xenoVal = blobRect.height;
    tval = targetRect.height;
    blobRect.height = (xenoVal * (1.f - xenoPct)) + (tval * xenoPct);
    
    xenoVal = blobRect.x;
    tval = targetRect.x;
    blobRect.x = (xenoVal * (1.f - xenoPct)) + (tval * xenoPct);
    
    xenoVal = blobRect.y;
    tval = targetRect.y;
    blobRect.y = (xenoVal * (1.f - xenoPct)) + (tval * xenoPct);
    
    energy *= .98;
    
    angle += energy;
}

//--------------------------------------------------------------
void BoxOffsetScene::draw() {
    
    
    bool bEven = numBeatHits % 2 == 0;
    
    if(mode == 0) {
        ofSetColor( energy * 255 );
        ofRect( blobRect.x, 0, blobRect.width, blobRect.y );
        
        ofLine(0, blobRect.getCenter().y, getWidth(), blobRect.getCenter().y);
    }
    if(mode == 1) {
        ofSetColor( energy * 255 );
        ofRect( 0, 0, blobRect.x, getHeight() );
        ofRect( blobRect.x + blobRect.width, 0, getWidth() - blobRect.x, getHeight() );
    }
    if(mode == 2) {
        
        ofSetColor(  bEven ? (energy*255) : 0 );
        ofRect( 0, 0, blobRect.x, getHeight() );
        
        ofSetColor( bEven ? 0 : (energy*255) );
        ofRect( blobRect.x + blobRect.width, 0, getWidth() - blobRect.x, getHeight() );
    }
    if(mode == 3) {
        ofSetColor( energy * 255 );
        ofRect( 0, 0, getWidth(), (float)getHeight()* energy );
        ofSetColor(0);
        ofRect( blobRect.x, 0, blobRect.width, getHeight() );
    }
    if(mode == 4) {
        ofSetColor( 255 );
        ofRect( blobRect.x,
               (sin( angle * .25 ) * (getHeight()*.5)) + (getHeight()*.5),
               blobRect.width,
               //blobRect.height
               cos( angle * .25 ) * blobRect.height + 10
            );
    }
    if(mode == 5) {
        ofSetColor( bEven ? 255 : 0 );
        ofRect(0, 0, getWidth(), getHeight() );
        
        ofSetColor( bEven ? 0 : (energy*255) );
        ofVec2f diff = (ofVec2f(blobRect.x, blobRect.y) - ofVec2f(0, getHeight()) );
        diff.normalize();
        diff *= getWidth();
        diff += (ofVec2f(blobRect.x, blobRect.y) );
        
        glBegin(GL_TRIANGLES); {
            glVertex2f(0, 0);
            glVertex2f(diff.x, diff.y);
            glVertex2f(0, getHeight());
        } glEnd();
        
        diff = (ofVec2f(blobRect.x+blobRect.width, blobRect.y) - ofVec2f(getWidth(), getHeight()) );
        diff.normalize();
        diff *= getWidth();
        diff += (ofVec2f(blobRect.x+blobRect.width, blobRect.y) );
        
        glBegin(GL_TRIANGLES); {
            glVertex2f( getWidth(), getHeight() );
            glVertex2f( diff.x, diff.y);
            glVertex2f( getWidth(), 0 );
        } glEnd();
        
        float hw = getWidth() *.5;
        
        ofSetColor( bEven ? 255 : 0 );
        ofSetLineWidth( (1-energy) * 46 + 1);
        ofLine( 0, 0, blobRect.getCenter().x, blobRect.getCenter().y );
        ofLine( getWidth(), 0, blobRect.getCenter().x, blobRect.getCenter().y );
        ofSetLineWidth(1);
        
    }
    
    ofSetColor(255, 0, 0);
    ofNoFill();
    ofRect( blobRect );
    ofFill();
    
}

//--------------------------------------------------------------
void BoxOffsetScene::drawDebug() {
    
}









