#include "AnimatedIcon.h"
typedef vector<ofPoint> Segment;
vector<Segment> segments;

//--------------------------------------------------------------

void AnimatedIcon::setup(string _path, float _lineWidth , ofFloatColor c ){

	completion = 0;
	lineWidth = _lineWidth;

	color = c ; 
    clear() ; 

    filePath = _path ; 
	if ( ofFile::doesFileExist( _path ) == false ) 
	{
		ofLogError ( "AnimatedIcon::setup()" + _path + " does NOT exist ! ABORTING !!! " ) ; 
		return ;
	}

	svg.load(_path);
	if(svg.getNumPath() > 0)
	{
		for (int i = 0; i < svg.getNumPath(); ++i){
			ofPath path = svg.getPathAt(i);
			path.setPolyWindingMode(OF_POLY_WINDING_ODD);
			vector<ofPolyline> outline = path.getOutline();
			for (int j = 0; j < outline.size(); j++)
			{
				polylines.push_back(outline[j]);
			}
		}
	}
}

void AnimatedIcon::clear()
{
    segments.clear() ;
    polylines.clear() ;
    
    int numPaths = svg.getNumPath() ;
    for ( int i = 0 ; i < numPaths ; i++ )
        svg.getPathAt( i ).clear() ;

}
//--------------------------------------------------------------
void AnimatedIcon::draw(){
	completion = ofClamp(completion, 0,1);

	ofSetLineWidth ( lineWidth ) ;
	ofSetColor( color ) ; 
	if(completion == 0){
		return;
	} else if(completion == 1) {
		svg.draw();
	} else {
	for (int i = 0; i < polylines.size(); i++) {
			ofPolyline* polyline = &polylines[i];
			int limit = floor(polyline->getIndexAtPercent(completion));
			vector<ofPoint>vertices = polyline->getVertices();
				
			for (int i = 0; i < limit; ++i) {
				ofLine(vertices[i], vertices[i+1]);
			}
			ofLine(vertices[limit], polyline->getPointAtPercent(completion));
		}
	}
}


void AnimatedIcon::drawStroke( ) 
{
	completion = ofClamp(completion, 0,1);
	ofSetColor( color ) ; 
	ofSetLineWidth ( lineWidth ) ;
	ofPushStyle();
    ofNoFill() ;
	ofEnableSmoothing() ; 

	if(completion == 0){
		return;
	} else if(completion == 1){
		for (int i = 0; i < polylines.size(); i++) {
			polylines[i].draw();
		}
	} else {
		for (int i = 0; i < polylines.size(); i++) {
			ofPolyline* polyline = &polylines[i];
			int limit = floor(polyline->getIndexAtPercent(completion));
			vector<ofPoint>vertices = polyline->getVertices();
				
			for (int i = 0; i < limit; ++i) {
				ofLine(vertices[i], vertices[i+1]);
			}
			ofLine(vertices[limit], polyline->getPointAtPercent(completion));
		}
	}

	ofPopStyle(); 
}