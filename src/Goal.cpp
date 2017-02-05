#include "Goal.h"
Goal::Goal() {
}

void Goal::setup(int _idx) {
    idx = _idx;
    color.set(0, 0, ofRandom(255));
}

void Goal::update() {

}

void Goal::draw() {
    ofSetColor(color);
}
