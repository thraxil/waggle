#include "ofApp.h"

#define BOUNDARY_CIRCLE_SCALE 0.9
#define MOTOR_GRID_SCALE 0.6
#define NGOALS 8

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetBackgroundAuto(false);
    ofBackground(0);
    ofSetFrameRate(60);
    ofSetCircleResolution(50);
    ofEnableAntiAliasing();

    motors.setup();
    sequencer.setup(&motors);
    goals.setup(NGOALS, &sequencer);

    goalSelected = -1; // which one the player has chosen
    goalTargeted = -1; // the "correct" one
}

//--------------------------------------------------------------
void ofApp::update(){
    goalTargeted = goals.getTargetGoal();
    sequencer.update();
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofBackground(ofColor::white);

    // some useful info about the screen
    auto width = ofGetWidth();
    auto height = ofGetHeight();
    auto bound = std::min(width, height);

    ofVec2f center(width / 2, height / 2);
    auto radius = (bound / 2) * BOUNDARY_CIRCLE_SCALE;

    // draw a big ol circle
    drawBoundaryCircle(center, radius);

    // draw the goals
    goals.draw(center, radius);

    // draw the motor grid
    auto dim = MOTOR_GRID_SCALE * bound;
    int rows = 6;
    int cols = 6;
    int mWidth = dim / rows;
    ofVec2f topLeft(center.x - (mWidth * 3), center.y - (mWidth * 3));
    drawGrid(rows, cols, center, topLeft, dim, mWidth);

    // finally, the motors
    motors.draw(topLeft, mWidth);
}

void ofApp::drawBoundaryCircle(ofVec2f center, float radius) {
    ofSetColor(220, 220, 220);
    ofDrawCircle(center.x, center.y, radius);
}

void ofApp::drawGrid(int rows, int cols, ofVec2f center, ofVec2f topLeft, float dim, int mWidth) {
    ofSetColor(ofColor::white);
    ofSetRectMode(OF_RECTMODE_CENTER);
    ofDrawRectangle(center.x, center.y, dim, dim);
    ofSetColor(ofColor::black);
    ofNoFill();
    ofSetRectMode(OF_RECTMODE_CORNER);

    for (int i=0; i < rows; i++) {
        for (int j=0; j < cols; j++) {
            ofDrawRectangle(topLeft.x + (mWidth * i),
                            topLeft.y + (mWidth * j),
                            mWidth, mWidth);
        }
    }
}


//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    // this won't work once we have more than 10 goals,
    // but for now...
    if (key >= '0' && key <= '7') {
        // simulate a goal selection
        goalSelected = key - '0';
        goals.select(goalSelected);
        if (goalTargeted > -1) {
            // there's a target goal, so we're "playing"
            if (goalTargeted == goalSelected) {
                // CORRECT!
                win();
            } else {
                // BZZT! Wrong!
                lose();
            }
        } else {
            // no goal was targeted, so just treat this as
            // debugging
        }
    }
}

void ofApp::win() {
    ofLogNotice() << "correct goal selected! you've got pollen!";
    // show animation
    // play sound
    newGame();
}

void ofApp::lose() {
    ofLogNotice() << "wrong goal! no pollen for you!";
    // show animation
    // pay sound
    newGame();
}

void ofApp::newGame() {
    ofLogNotice() << "starting new game";
    // pick a random goal
    auto g = std::rand() % NGOALS;
    goals.selectTarget(g);
    goals.unselectAll();
    sequencer.start(g);
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
    motors.mouseReleased(x, y, button);
    goals.mouseReleased(x, y, button);
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
