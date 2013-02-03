//
//  KinectManager.cpp
//  Double_Kinect_Tests
//
//  Created by Nick Hardeman on 11/5/12.
//
//

#include "KinectManager.h"

//--------------------------------------------------------------
KinectManager::KinectManager() {
    farThreshold    = 70;
    nearThreshold   = 255;
    
    step            = 4;
    scale           = 1.f;
    
    inverseAxes.set(1,1,1);
    
    bPointsActive   = NULL;
    
    kinectFOV       = 70;
    maxTriDiff      = 100.f;
    bUseVideoColor  = false;
    bThreshWithOpenCV = false;
}

//--------------------------------------------------------------
void KinectManager::open() {
    
    mesh.clear();
    
    // enable depth->video image calibration
	kinect.setRegistration(true);
    
	kinect.init();
	//kinect.init(true); // shows infrared instead of RGB video image
	//kinect.init(false, false); // disable video image (faster fps)
	
	kinect.open();		// opens first available kinect
    
    width   = kinect.getWidth();
    height  = kinect.getHeight();
    
    
	grayImage.allocate(kinect.width, kinect.height);
	grayThreshNear.allocate(kinect.width, kinect.height);
	grayThreshFar.allocate(kinect.width, kinect.height);
    
    if(bPointsActive == NULL)
        bPointsActive = new bool[width*height];
    
    for(int x = 0; x < width; x++) {
        for(int y = 0; y < height; y++) {
            int i = x*height+y;
            bPointsActive[i] = false;
        }
    }
    
    setupMesh();
}

//--------------------------------------------------------------
void KinectManager::close() {
    kinect.close();
    if(bPointsActive != NULL) {
        delete [] bPointsActive;
        bPointsActive = NULL;
    }
}

//--------------------------------------------------------------
void KinectManager::loadSettings() {
    if(kinect.isConnected())
        gui->loadSettings("GUI/kinect_"+ofToString(kinect.getDeviceId(), 0)+".xml");
}

//--------------------------------------------------------------
void KinectManager::saveSettings() {
    if(kinect.isConnected())
        gui->saveSettings("GUI/kinect_"+ofToString(kinect.getDeviceId(), 0)+".xml");
}

//--------------------------------------------------------------
bool KinectManager::isConnected() {
    return kinect.isConnected();
}

//--------------------------------------------------------------
void KinectManager::update() {
    if(!kinect.isConnected()) return;
    kinect.update();
}

//--------------------------------------------------------------
void KinectManager::draw() {
    if(!kinect.isConnected()) return;
    
    ofSetColor(255);
    mesh.draw();
}

//--------------------------------------------------------------
void KinectManager::drawDebug() {
    ofNode node;
    node.setPosition(offsetVec);
    node.setOrientation( axesRotation );
    
    node.transformGL();
    
    ofSetColor(255, 0, 0);
    ofSphere(0,0,0, 10);
    
    float farZ = farThreshold * inverseAxes.z;
    ofSetColor(0, 0, 255);
    
    // http://www.lighthouse3d.com/tutorials/view-frustum-culling/view-frustums-shape/ //
    float hfar = 2.f * tan( (DEG_TO_RAD * kinectFOV) / 2.f) * (float)farThreshold;
    float wfar = hfar * (4.f/3.f);
    
    float hhfar = hfar*.5f;
    float hwfar = wfar*.5f;
    
    // Frustrum //
    ofLine(0,0,0, -hwfar, -hhfar, farZ);
    ofLine(0,0,0, hwfar, -hhfar, farZ);
    ofLine(0,0,0, hwfar, hhfar, farZ);
    ofLine(0,0,0, -hwfar, hhfar, farZ);
    
    // Far Plane //
    ofLine( -hwfar, -hhfar, farZ, hwfar, -hhfar, farZ );
    ofLine( hwfar, -hhfar, farZ, hwfar, hhfar, farZ );
    ofLine( -hwfar, hhfar, farZ, hwfar, hhfar, farZ );
    ofLine( -hwfar, -hhfar, farZ, -hwfar, hhfar, farZ );
    
    // X //
    ofLine( -hwfar, -hhfar, farZ, hwfar, hhfar, farZ );
    ofLine( hwfar, -hhfar, farZ, -hwfar, hhfar, farZ );
    
    node.restoreTransformGL();
    
}

//--------------------------------------------------------------
bool KinectManager::isFrameNew() {
    return kinect.isFrameNew();
}

//--------------------------------------------------------------
float* KinectManager::getDistancePixels() {
    return kinect.getDistancePixels();
}

//--------------------------------------------------------------
ofVec3f KinectManager::getWorldCoordAt( int x, int y ) {
    ofVec3f cur;
    setWorldCoord(x, y, cur);
    return cur;
}

//--------------------------------------------------------------
void KinectManager::setWorldCoord( int x, int y, ofVec3f& inVec ) {
    inVec = kinect.getWorldCoordinateAt(x, y);
    
    ofVec3f up(0,1,0);
    
    inVec.x *= inverseAxes.x;
    inVec.x *= scale;
    inVec.y *= inverseAxes.y;
    inVec.y *= scale;
    inVec.z *= inverseAxes.z;
    inVec.z *= scale;
    
    inVec.rotate(axesRotation.y, up);
}

//--------------------------------------------------------------
void KinectManager::setupMesh() {
    //cout << "KinectMesh :: setupMesh : step = " << step << endl;
    
    //bool bAddNormals = renderMode != OF_PRIMITIVE_POINTS ? true : false;
    
    ofColor borderColor(255, 0, 0);
    ofColor color(255, 255, 255);
    for(int y = 0; y < height; y++) {
        for(int x = 0; x < width; x++) {
            mesh.addVertex(ofVec3f(x,y,0));
            //mesh.addNormal(ofVec3f(x,y,-1)); // add and remove normals later //
            //if(x < step || x > width - step || y < step || y > height - step*3)
            //    mesh.addColor(borderColor);
            //else
            mesh.addColor(color);
            
            mesh.addTexCoord( ofVec2f( (float)x/(float)width, (float)y/(float)height) );
        }
    }
}

//--------------------------------------------------------------
void KinectManager::calculateMesh( ofVec3f mesh_offset ) {
    
    int w = 640;
    int h = 480;
    
    
    float minx, maxx;
    float miny, maxy;
    float minz, maxz;
    
    ofVec3f up(0,1,0);
    
    ofVec3f cur;
    ofColor color(255,255,255);
    // set the vertexes //
	for(int y = 0; y < h; y += step) {
		for(int x = 0; x < w; x += step) {
            int i = y * w + x;
            
            cur = kinect.getWorldCoordinateAt(x, y);
            
            bPointsActive[i] = false;
            if(cur.z >= nearThreshold && cur.z <= farThreshold)
                bPointsActive[i] = true;
            //if(!isnan(cur.x)) if(cur.x < minx) minx = cur.x;
            //if(!isnan(cur.x)) if(cur.x > maxx) maxx = cur.x;
            
            //if(!isnan(cur.y)) if(cur.y < miny) miny = cur.y;
            //if(!isnan(cur.y)) if(cur.y > maxy) maxy = cur.y;
            
            //if(!isnan(cur.z)) if(cur.z < minz) minz = cur.z;
            //if(!isnan(cur.z)) if(cur.z > maxz) maxz = cur.z;
            
            // flip the image //
            cur.x *= inverseAxes.x;
            cur.x *= scale;
            cur.y *= inverseAxes.y;
            cur.y *= scale;
            cur.z *= inverseAxes.z;
            cur.z *= scale;
            
            cur.rotate(axesRotation.y, up);
            cur += mesh_offset;
            mesh.setVertex(i, cur);
            
            if(bUseVideoColor) {
                color = kinect.getColorAt(x, y);
                mesh.setColor(i, color);
            }
            
		}
	}
}

//--------------------------------------------------------------
void KinectManager::calculatePoints( ofVec3f a_meshOffset  ) {
	int w = kinect.width;
    int h = kinect.height;
    
    if(mesh.getMode() != OF_PRIMITIVE_POINTS) mesh.setMode(OF_PRIMITIVE_POINTS);
    if(mesh.getNumNormals() > 0 ) mesh.clearNormals(); // no normals on points //
    
    mesh.clearIndices();
    
    calculateMesh( a_meshOffset );
    
    // set the vertexes //
	for(int y = 0; y < h; y += step) {
		for(int x = 0; x < w; x += step) {
            int i = y * w + x;
            
            if(bPointsActive[i]) {
                mesh.addIndex(i);
            }
		}
	}
}

//--------------------------------------------------------------
void KinectManager::calculateTriangleMesh( ofVec3f mesh_offset, bool bCalcNormals ) {
	int w = 640;
    int h = 480;
    
    float* z = kinect.getDistancePixels();
    
    mesh.clearIndices();
    if(mesh.getMode() != OF_PRIMITIVE_TRIANGLES) mesh.setMode(OF_PRIMITIVE_TRIANGLES);
    if( mesh.getNumNormals() != mesh.getNumVertices() ) {
        mesh.getNormals().assign(mesh.getNumVertices(), ofVec3f() );
    }
    
    ofVec3f cur;
    ofColor color(100,100,100);
    
    calculateMesh( mesh_offset );
    
    // calculate the normals //
    ofVec3f normal;
    ofVec3f triU, triV;
    
    for(int y = 0; y < h; y += step) {
		for(int x = 0; x < w; x += step) {
            int i = y * w + x;
            if(x < w - step && y < h - step) {
                unsigned int nwi = i;
                unsigned int nei = nwi + step;
                unsigned int swi = nwi + (step * w);
                unsigned int sei = swi + step;
                
                float nw = z[nwi];
                float ne = z[nei];
                float sw = z[swi];
                float se = z[sei];
                
                float nw_ne_diff = nw - ne;
                float nw_sw_diff = nw - sw;
                float ne_sw_diff = ne - sw;
                
                float sw_se_diff = sw - se;
                float ne_se_diff = ne - se;
                
                if(nw_ne_diff < 0) nw_ne_diff *= -1;
                if(nw_sw_diff < 0) nw_sw_diff *= -1;
                if(ne_sw_diff < 0) ne_sw_diff *= -1;
                if(sw_se_diff < 0) sw_se_diff *= -1;
                if(ne_se_diff < 0) ne_se_diff *= -1;
                
                if(bPointsActive[nwi] > 200 && bPointsActive[nei] > 200 && bPointsActive[swi] > 200) {
                    //if(nw != 0 && ne != 0 && sw != 0) {
                    if( nw_ne_diff < maxTriDiff && nw_sw_diff < maxTriDiff && ne_sw_diff < maxTriDiff) {
                        mesh.addIndex(nwi);
                        mesh.addIndex(nei);
                        mesh.addIndex(swi);
                        
                        // calculate the normals //
                        // average for the 6 faces //
                        // http://www.gamedev.net/topic/78633-glnormal-with-triangle-strip-possible-/ //
                        
                        //triU = mesh.getVertex(nei) - mesh.getVertex(nwi);
                        //triV = mesh.getVertex(swi) - mesh.getVertex(nwi);
                        
                        triU = mesh.getVertex(swi) - mesh.getVertex(nwi);
                        triV = mesh.getVertex(nei) - mesh.getVertex(nwi);
                        
                        normal = triU.cross(triV);
                        normal.normalize();
                        
                        mesh.setNormal(sei, (normal + mesh.getNormal(sei)));
                        mesh.setNormal(nei, (normal + mesh.getNormal(nei)));
                        mesh.setNormal(nwi, normal + mesh.getNormal(nwi));
                        
                    }
                    //}
                }
                
                if(bPointsActive[nei] > 200 && bPointsActive[sei] > 200 && bPointsActive[swi] > 200) {
                    //if(ne != 0 && se != 0 && sw != 0) {
                    if( sw_se_diff < maxTriDiff && ne_se_diff < maxTriDiff && ne_sw_diff < maxTriDiff) {
                        mesh.addIndex(nei);
                        mesh.addIndex(sei);
                        mesh.addIndex(swi);
                        
                        // calculate the normals //
                        //triU = mesh.getVertex(sei) - mesh.getVertex(nei);
                        //triV = mesh.getVertex(swi) - mesh.getVertex(nei);
                        
                        triU = mesh.getVertex(swi) - mesh.getVertex(nei);
                        triV = mesh.getVertex(sei) - mesh.getVertex(nei);
                        
                        normal = triU.cross(triV);
                        normal.normalize();
                        
                        mesh.setNormal(sei, normal);
                        mesh.setNormal(swi, (normal + mesh.getNormal(swi)) );
                        mesh.setNormal(nei, (normal + mesh.getNormal(nei)) );
                        
                    }
                }
            }
        }
    }
    
    for(int j = 0; j < mesh.getNumIndices(); j++) {
        int i = mesh.getIndex(j);
        mesh.setNormal(i, mesh.getNormal(i).normalize());
    }
    
}

//--------------------------------------------------------------
void KinectManager::calculateTriangleStripMesh( ofVec3f mesh_offset, bool bCalcNormals ) {
    
	int w = kinect.width;
    int h = kinect.height;
    
    float* z = kinect.getDistancePixels();
    
    ofVec3f cur;
    ofColor color(255,255,255);
    
    if(mesh.getMode() != OF_PRIMITIVE_TRIANGLE_STRIP) mesh.setMode(OF_PRIMITIVE_TRIANGLE_STRIP);
    if( mesh.getNumNormals() != mesh.getNumVertices() ) {
        mesh.getNormals().assign(mesh.getNumVertices(), ofVec3f() );
    }
    
    mesh.clearIndices();
    
    calculateMesh( mesh_offset );
    
    ofVec3f normal;
    ofVec3f triU, triV;
    
    int dir = 1;
    
	for(int y = 0; y < h-step; y += step) {
        if(y > 0) dir *= -1;
        
		for(int x = 0; x < w; x += step) {
            
            int nx = x;
            int ny = y;
            if(dir == -1) {
                nx = (w-step) - x;
            }
            
            int i = y * w + nx;
            unsigned int nwi = i;
			unsigned int nei = nwi + step;
			unsigned int swi = nwi + (step * w);
			//unsigned int sei = swi + step;
            
            float nw = z[nwi];
            //float ne = z[nei];
            float sw = z[swi];
            //float se = z[sei];
            
            
            if(x >= w - step) {
                nei = w - step;
            }
            
            
            if(bPointsActive[nwi] > 200 && bPointsActive[swi] > 200) {
                
                triU = mesh.getVertex(nei) - mesh.getVertex(nwi);
                triV = mesh.getVertex(swi) - mesh.getVertex(nwi);
                
                normal = triU.cross(triV);
                normal.normalize();
                
                if(nw > 10 && sw > 10 ) {
                    
                    mesh.setNormal(nwi, normal+mesh.getNormal(nwi));
                    mesh.setNormal(swi, normal+mesh.getNormal(swi));
                    
                    mesh.addIndex(nwi);
                    mesh.addIndex(swi);
                    
                }
            }
            //if(x == w-1) {
            //mesh.addIndex(nwi);
            //mesh.addIndex(swi);
            //}
		}
	}
    
    for(int j = 0; j < mesh.getNumIndices(); j++) {
        int i = mesh.getIndex(j);
        mesh.setNormal(i, mesh.getNormal(i).normalize());
    }
    
}

//--------------------------------------------------------------
ofVec3f KinectManager::getMeshCenter() {
    ofVec3f tcenter;
    for(int i = 0; i < mesh.getNumIndices(); i++) {
        tcenter += mesh.getVertex( mesh.getIndex(i) );
    }
    tcenter /= (float)mesh.getNumIndices();
    return tcenter;
}

//--------------------------------------------------------------
ofVec3f& KinectManager::getOffsetVector() {
    return offsetVec;
}

//--------------------------------------------------------------
void KinectManager::calculateCVOperations() {
    // make sure to only call this if isFrameNew() == true //
    
    //cout << "KinectManager :: calculateCVOperations : nearThreshCV = " << nearThreshCV << " farThreshCV = " << farThreshCV << endl;
    
    if(!kinect.isConnected()) return;
    
    
    
    // load grayscale depth image from the kinect source
    grayImage.setFromPixels(kinect.getDepthPixels(), kinect.width, kinect.height);
    
    if(inverseAxes.x == -1) {
        grayImage.mirror(false, true);
    }
    
    // we do two thresholds - one for the far plane and one for the near plane
    // we then do a cvAnd to get the pixels which are a union of the two thresholds
    if(bThreshWithOpenCV) {
        grayThreshNear = grayImage;
        grayThreshFar = grayImage;
        grayThreshNear.threshold(nearThreshCV, true);
        grayThreshFar.threshold(farThreshCV);
        cvAnd(grayThreshNear.getCvImage(), grayThreshFar.getCvImage(), grayImage.getCvImage(), NULL);
    } else {
        
        // or we do it ourselves - show people how they can work with the pixels
        unsigned char * pix = grayImage.getPixels();
        
        int numPixels = grayImage.getWidth() * grayImage.getHeight();
        for(int i = 0; i < numPixels; i++) {
            if(pix[i] < nearThreshCV && pix[i] > farThreshCV) {
                pix[i] = 255;
            } else {
                pix[i] = 0;
            }
        }
    }
    
    // update the cv images
    grayImage.flagImageChanged();
    
    // find contours which are between the size of 20 pixels and 1/3 the w*h pixels.
    // also, find holes is set to true so we will get interior contours as well....
//    findContours( ofxCvGrayscaleImage&  input,
//                 int minArea,
//                 int maxArea,
//                 int nConsidered,
//                 bool bFindHoles,
//                 bool bUseApproximation)
    
    
    contourFinder.findContours(grayImage, 30*30, (kinect.width*kinect.height)/2, 3, false);
}

//--------------------------------------------------------------
vector<ofPolyline> KinectManager::getScaledContourPolyline(float x, float y, float w, float h ) {
    
    float _width    = contourFinder.getWidth();
    float _height   = contourFinder.getHeight();
    
    float scalex    = 0.0f;
    float scaley    = 0.0f;
    
    if( _width != 0 ) { scalex = w/_width; } else { scalex = 1.0f; }
    if( _height != 0 ) { scaley = h/_height; } else { scaley = 1.0f; }
    
    vector<ofPolyline> lines;
    
	for( int i=0; i<(int)contourFinder.blobs.size(); i++ ) {
        ofPolyline line;
		for( int j=0; j<contourFinder.blobs[i].nPts; j++ ) {
			//ofVertex( blobs[i].pts[j].x, blobs[i].pts[j].y );
            line.addVertex(contourFinder.blobs[i].pts[j].x * scalex + x,
                           contourFinder.blobs[i].pts[j].y * scaley + y);
		}
        lines.push_back(line);
	}
    
    return lines;
}

//--------------------------------------------------------------
vector<ofRectangle> KinectManager::getScaledContourBoundingBoxes(float x, float y, float w, float h ) {
    
    float _width    = contourFinder.getWidth();
    float _height   = contourFinder.getHeight();
    
    float scalex    = 0.0f;
    float scaley    = 0.0f;
    
    if( _width != 0 ) { scalex = w/_width; } else { scalex = 1.0f; }
    if( _height != 0 ) { scaley = h/_height; } else { scaley = 1.0f; }
    
    vector<ofRectangle> rects;
    
	for( int i=0; i<(int)contourFinder.blobs.size(); i++ ) {
        ofRectangle rect = contourFinder.blobs[i].boundingRect;
        rect.x = rect.x * scalex + x;
        rect.y = rect.y * scaley + y;
        rect.width = rect.width * scalex;
        rect.height = rect.height * scaley;
        rects.push_back( rect );
	}
    
    return rects;
}

//--------------------------------------------------------------
void KinectManager::guiEvent(ofxUIEventArgs &e) {
    string ename = e.widget->getName();
    
    if(e.widget->getName() == "KINECT_CAMERA_ANGLE") {
        ofxUISlider *slider = (ofxUISlider *) e.widget;
        cout << "kinect angle = " << slider->getScaledValue() << endl;
        kinect.setCameraTiltAngle( (int)round(slider->getScaledValue()) );
    }
    if (e.widget->getName() == "Mesh Offset X") {
        ofxUISlider *slider = (ofxUISlider *) e.widget;
        offsetVec.x = slider->getScaledValue();
    } else if (e.widget->getName() == "Mesh Offset Y") {
        ofxUISlider *slider = (ofxUISlider *) e.widget;
        offsetVec.y = slider->getScaledValue();
    } else if (e.widget->getName() == "Mesh Offset Z") {
        ofxUISlider *slider = (ofxUISlider *) e.widget;
        offsetVec.z = slider->getScaledValue();
    } else if (e.widget->getName() == "Kinect FOV" ) {
        ofxUISlider* slider = (ofxUISlider*) e.widget;
        kinectFOV = slider->getScaledValue();
    }
    
    if(e.widget->getName() == "ThreshSlider") {
        ofxUIRangeSlider* slider = (ofxUIRangeSlider*) e.widget;
        nearThreshold   = slider->getScaledValueLow();
        farThreshold    = slider->getScaledValueHigh();
    } else if (e.widget->getName() == "X AXIS" ) {
        ofxUILabelToggle* toggle = (ofxUILabelToggle*) e.widget;
        //cout << "invert x axis " << toggle->getValue() << endl;
        inverseAxes.x = toggle->getValue() == 1 ? -1 : 1;
    } else if (e.widget->getName() == "Y AXIS" ) {
        ofxUILabelToggle* toggle = (ofxUILabelToggle*) e.widget;
        //cout << "invert x axis " << toggle->getValue() << endl;
        inverseAxes.y = toggle->getValue() == 1 ? -1 : 1;
    } else if (e.widget->getName() == "Z AXIS" ) {
        ofxUILabelToggle* toggle = (ofxUILabelToggle*) e.widget;
        //cout << "invert x axis " << toggle->getValue() << endl;
        inverseAxes.z = toggle->getValue() == 1 ? -1 : 1;
    } else if (e.widget->getName() == "Mesh Step") {
        ofxUISlider* slider = (ofxUISlider*) e.widget;
        step = slider->getScaledValue();
    } else if (e.widget->getName() == "Y AXIS ROT" ) {
        ofxUIRotarySlider* slider = (ofxUIRotarySlider*) e.widget;
        axesRotation.y = slider->getScaledValue();
    } else if (e.widget->getName() == "BTHRESH_WITH_CV") {
        bThreshWithOpenCV = ((ofxUIToggle*)e.widget)->getValue();
    } else if (ename == "CV_ThreshSlider") {
        ofxUIRangeSlider* slider = (ofxUIRangeSlider*) e.widget;
        nearThreshCV    = 255-slider->getScaledValueLow();
        farThreshCV     = 255-slider->getScaledValueHigh();
    }

}

//--------------------------------------------------------------
void KinectManager::setupGui(float a_x, float a_y) {
    gui = new ofxUIScrollableCanvas( a_x, a_y, 320, ofGetHeight() + 300 - a_y );
    
    float GUI_WIDGET_WIDTH = 300;
    float GUI_SLIDER_HEIGHT = 16;
    
    gui->addWidgetDown(new ofxUILabel("Kinect Settings", OFX_UI_FONT_LARGE));
    gui->addSpacer(GUI_WIDGET_WIDTH, 2);
    
    gui->addSlider("KINECT_CAMERA_ANGLE", -30.0, 30.0, 0.0, GUI_WIDGET_WIDTH, GUI_SLIDER_HEIGHT);
    
    //ofTexture* rgbTex = ((ofTexture*) &kinect.getTextureReference());
    //gui->addWidgetDown( new ofxUIBaseDraws(128, 96, rgbTex, "RGB Texture") );
    ofTexture* depthTex = (ofTexture*) &kinect.getDepthTextureReference();
    gui->addWidgetDown( new ofxUIBaseDraws(128, 96, depthTex, "Depth Texture") );
    
    //ofTexture* cvTex = ((ofTexture*)&grayImage.getTextureReference());
//    ofxCvGrayscaleImage* ((ofxCvGrayscaleImage*) &grayImage);
    gui->addWidgetRight( new ofxUIBaseDraws(128, 96, ((ofxCvGrayscaleImage*) &grayImage), "Open CV Texture") );
    
    gui->addWidgetDown( new ofxUIToggle("BTHRESH_WITH_CV", false, 16, 16) );
    gui->addRangeSlider("CV_ThreshSlider", 0.0, 255, 0, 255, GUI_WIDGET_WIDTH, GUI_SLIDER_HEIGHT);
    
    gui->addRangeSlider("ThreshSlider", 0.0, 7500.0, 50.0, 1000.0, GUI_WIDGET_WIDTH, GUI_SLIDER_HEIGHT);
    
    gui->addSlider("Kinect FOV", 1, 179, 70, GUI_WIDGET_WIDTH, GUI_SLIDER_HEIGHT);
    
    gui->addSpacer( GUI_WIDGET_WIDTH, 1);
    gui->addSlider("Mesh Offset X", -3000.f, 3000.f, 0.0, GUI_WIDGET_WIDTH, GUI_SLIDER_HEIGHT);
    gui->addSlider("Mesh Offset Y", -3000.f, 3000.f, 0.0, GUI_WIDGET_WIDTH, GUI_SLIDER_HEIGHT);
    gui->addSlider("Mesh Offset Z", -3000.f, 3000.f, 0.0, GUI_WIDGET_WIDTH, GUI_SLIDER_HEIGHT);
    gui->addSlider("Mesh Step", 1, 20, 4, GUI_WIDGET_WIDTH, GUI_SLIDER_HEIGHT);
    
    gui->addSpacer( GUI_WIDGET_WIDTH, 1);
    gui->addWidgetDown(new ofxUILabel("INVERT AXES", OFX_UI_FONT_MEDIUM));
    gui->addWidgetDown( new ofxUILabelToggle("X AXIS", false, 90, 30, 0, 0) );
    gui->addWidgetRight( new ofxUILabelToggle("Y AXIS", false, 90, 30, 0, 0) );
    gui->addWidgetRight( new ofxUILabelToggle("Z AXIS", false, 90, 30, 0, 0) );
    
    gui->addWidgetDown(new ofxUIRotarySlider(64, -180.f, 180.f, 0.f, "Y AXIS ROT"));
    
    gui->addSpacer( GUI_WIDGET_WIDTH, 1);
    
    gui->setScrollArea(a_x, a_y, 320, ofGetHeight() - 10 - a_y);
    
    ofAddListener( gui->newGUIEvent, this, &KinectManager::guiEvent );
}









