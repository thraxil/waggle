#include "ofApp.h"

#define BOUNDARY_CIRCLE_SCALE 0.9
#define MOTOR_GRID_SCALE 0.6

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetBackgroundAuto(false);
    ofBackground(0);
    ofSetFrameRate(60);
    ofSetCircleResolution(50);
    ofEnableAntiAliasing();
}

//--------------------------------------------------------------
void ofApp::update(){
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofBackground(ofColor::white);

    // some useful info about the screen
    auto width = ofGetWidth();
    auto height = ofGetHeight();
    auto bound = std::min(width, height);

    ofVec2f center(width / 2, height / 2);

    // draw a big ol circle
    ofSetColor(200, 200, 200);
    auto radius = (bound / 2) * BOUNDARY_CIRCLE_SCALE;
    ofDrawCircle(center.x, center.y, radius);

    // draw the goals

    // draw the motor grid
    ofSetColor(ofColor::white);
    ofSetRectMode(OF_RECTMODE_CENTER);
    auto dim = MOTOR_GRID_SCALE * bound;
    ofDrawRectangle(center.x, center.y, dim, dim);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){
    ofLogNotice() << "resized [" << w << ", " << h << "]";
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
