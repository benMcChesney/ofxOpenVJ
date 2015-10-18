//
//  Utils.h
//
//  Created by Nick Hardeman on 9/25/12.
//
//

#pragma once
#include "ofMain.h"

/*
class DraggablePoint : public ofRectangle
{
public:
    DraggablePoint() {setup();}
    
    void setup(bool bCentered=true) {
        _bDragging      = false;
        _bCentered      = bCentered;
        _bMouseOver     = false;
        _offset.set(0, 0);
        width = height = 14;
    }
    bool isDragging() {return _bDragging;};
    bool isMouseOver() {return _bMouseOver;}
    
    void setPosition( float a_x, float a_y ) {
        x = _bCentered ? ( a_x - width*.5f) : a_x;
        y = _bCentered ? ( a_y - height*.5f) : a_y;
    }
    void setPosition( ofVec2f pos ) {
        setPosition( pos.x, pos.y );
    }
    
    ofVec2f getPosition() {
        return ofVec2f( _bCentered?x+width*.5f:x, _bCentered?y+height*.5f:y);
    }
    ofVec2f getCornerPosition() {
        return ofVec2f( x, y);
    }
    
    bool isPointInside( float a_x, float a_y ) {
        if(a_x >= x) {if(a_x <= x + width) {if(a_y >= y){if(a_y <= y+ height){return true;}}}}; return false;
    }
    
    void mouseMoved( float a_x, float a_y ) {
        if(isPointInside(a_x, a_y))
            _bMouseOver=true;
        else
            _bMouseOver=false;
    }
    void mousePressed( float a_x, float a_y ) {
        if(isPointInside(a_x, a_y)) {
            _bDragging=true;
            _offset = getPosition()-ofVec2f(a_x, a_y);
        }else
            _bDragging=false;
    }
    void mouseReleased() {
        _bDragging = false;
    }
    void mouseDragged( float a_x, float a_y ) {
        if(_bDragging) {
            setPosition(ofVec2f(a_x, a_y)+_offset);
        }
    }
    
protected:
    bool _bMouseOver;
    bool _bDragging;
    bool _bCentered;
    ofVec2f _offset;
};

static bool isPointInsideRect(float a_x, float a_y, ofRectangle rect ) {
    if(a_x >= rect.x) {if(a_x <= rect.x + rect.width) {if(a_y >= rect.y){if(a_y <= rect.y + rect.height){return true;}}}};return false;
}

static void ofDrawGridInRect( ofVec2f TL, ofVec2f TR, ofVec2f BR, ofVec2f BL, int numColums, int numRows ) {
    ofVec2f topEdge     = TR - TL;
    ofVec2f botEdge     = BR - BL;
    ofVec2f leftEdge    = BL - TL;
    ofVec2f rightEdge   = BR - TR;
    
    float topLength     = topEdge.length();
    float botLength     = botEdge.length();
    float leftLength    = leftEdge.length();
    float rightLength   = rightEdge.length();
    
    topEdge.normalize();
    botEdge.normalize();
    leftEdge.normalize();
    rightEdge.normalize();
    
    
    float xPct = 0.f;
    float yPct = 0.f;
    glBegin(GL_LINES);
    
    for(int ix = 0; ix <= numColums; ix++) {
        xPct = (float)ix/(float)numColums;
        
        ofVec2f newTopEdge = (topEdge * (xPct * topLength)) + TL;
        glVertex2f( newTopEdge.x, newTopEdge.y);
        
        newTopEdge = (botEdge * (xPct * botLength)) + BL;
        glVertex2f( newTopEdge.x, newTopEdge.y);
        
    }
    
    for(int iy = 0; iy <= numRows; iy++) {
        yPct = (float)iy/(float)numRows;
        
        ofVec2f newEdge = (leftEdge * (yPct * leftLength)) + TL;
        glVertex2f( newEdge.x, newEdge.y);
        
        newEdge = (rightEdge * (yPct * rightLength)) + TR;
        glVertex2f( newEdge.x, newEdge.y);
        
    }
    glEnd();
};


static void ofQuadraticBezierVertex(float cpx, float cpy, float x, float y, float prevX, float prevY) {
    float cp1x = prevX + 2.0/3.0*(cpx - prevX);
    float cp1y = prevY + 2.0/3.0*(cpy - prevY);
    float cp2x = cp1x + (x - prevX)/3.0;
    float cp2y = cp1y + (y - prevY)/3.0;
    
    // finally call cubic Bezier curve function
    ofBezierVertex(cp1x, cp1y, cp2x, cp2y, x, y);
};

static vector<ofPoint> ofGetQuadraticBezierVerticies(float cpx, float cpy, float x, float y, float prevX, float prevY) {
    float cp1x = prevX + 2.0/3.0*(cpx - prevX);
    float cp1y = prevY + 2.0/3.0*(cpy - prevY);
    float cp2x = cp1x + (x - prevX)/3.0;
    float cp2y = cp1y + (y - prevY)/3.0;
    
    vector<ofPoint> pts;
    pts.push_back( ofPoint(cp1x, cp1y) );
    pts.push_back( ofPoint(cp2x, cp2y) );
    pts.push_back( ofPoint(x, y) );
    
    return pts;
};

static void ofRoundedRect(float x, float y, float w, float h, float r, float lineWidth=1, bool bOutline=false) {
    
    ofBeginShape();
    
    ofVertex(x+r, y);
    ofVertex(x+w-r, y);
    ofQuadraticBezierVertex(x+w, y, x+w, y+r, x+w-r, y);
    ofVertex(x+w, y+h-r);
    ofQuadraticBezierVertex(x+w, y+h, x+w-r, y+h, x+w, y+h-r);
    ofVertex(x+r, y+h);
    ofQuadraticBezierVertex(x, y+h, x, y+h-r, x+r, y+h);
    ofVertex(x, y+r);
    ofQuadraticBezierVertex(x, y, x+r, y, x, y+r);
    
    if(bOutline) {
        
        x += lineWidth;
        y += lineWidth;
        w -= (lineWidth*2);
        h -= (lineWidth*2);
        
        r *= (w-(lineWidth*2))/w;
        
        ofNextContour(true);
        ofVertex(x+r, y);
        ofVertex(x+w-r, y);
        ofQuadraticBezierVertex(x+w, y, x+w, y+r, x+w-r, y);
        ofVertex(x+w, y+h-r);
        ofQuadraticBezierVertex(x+w, y+h, x+w-r, y+h, x+w, y+h-r);
        ofVertex(x+r, y+h);
        ofQuadraticBezierVertex(x, y+h, x, y+h-r, x+r, y+h);
        ofVertex(x, y+r);
        ofQuadraticBezierVertex(x, y, x+r, y, x, y+r);
    }
    
    
    ofEndShape(true);
}

static ofPath ofGetRoundRectPath( float x, float y, float w, float h, float r ) {
    ofPath shape;
    shape.clear();
    
    shape.lineTo(x+r, y); // ofVertex
    shape.lineTo(x+w-r, y); // ofVertex
    vector<ofPoint> pts = ofGetQuadraticBezierVerticies(x+w, y, x+w, y+r, x+w-r, y);
    shape.bezierTo(pts[0].x, pts[0].y, pts[1].x, pts[1].y, pts[2].x, pts[2].y);
    shape.lineTo(x+w, y+h-r);
    pts = ofGetQuadraticBezierVerticies(x+w, y+h, x+w-r, y+h, x+w, y+h-r);
    shape.bezierTo(pts[0].x, pts[0].y, pts[1].x, pts[1].y, pts[2].x, pts[2].y);
    shape.lineTo(x+r, y+h);
    pts = ofGetQuadraticBezierVerticies( x, y+h, x, y+h-r, x+r, y+h );
    shape.bezierTo(pts[0].x, pts[0].y, pts[1].x, pts[1].y, pts[2].x, pts[2].y);
    shape.lineTo(x, y+r);
    pts = ofGetQuadraticBezierVerticies( x, y, x+r, y, x, y+r );
    shape.bezierTo(pts[0].x, pts[0].y, pts[1].x, pts[1].y, pts[2].x, pts[2].y);
    
    shape.close();
    
    return shape;
}

static ofRectangle ofFitRectProportionallyInsideRect( ofRectangle src, ofRectangle dest, bool bCenter=false ) {
    float scale = MIN( dest.width/src.width, dest.height/src.height );
    ofRectangle rect;
    rect.width = scale * src.width;
    rect.height = scale * src.height;
    
    rect.x = dest.x;
    rect.y = dest.y;
    
    if(bCenter) {
        rect.x = dest.x + (dest.width/2 - rect.width/2);
        rect.y = dest.y + (dest.height/2 - rect.height/2);
    }
    return rect;
}
*/
class ofxOpenVJUtils
{

	ofxOpenVJUtils() { }

public:
	static ofxOpenVJUtils* Instance()
	{
		static ofxOpenVJUtils inst;
		return &inst;
	}

	int getFrameAtNormalized(float normalized, int maxFrames)
	{
		int index = floor(ofMap(normalized, 0.0f, 1.0f, 0, maxFrames, true));
		return index;
	}
};






















