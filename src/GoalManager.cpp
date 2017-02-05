#include "GoalManager.h"

GoalManager::GoalManager() {
}

void GoalManager::setup(int ngoals) {
    for (int i=0; i < ngoals; i++) {
        Goal g;
        g.setup(i);
        goals.push_back(g);
    }
}

void GoalManager::update() {
}

void GoalManager::draw(ofVec2f center, float radius) {
    auto step = 360.0 / goals.size();
    ofSetColor(ofColor::black);
    ofFill();
    for (int i=0; i<goals.size(); i++) {
        auto angle = ofDegToRad(i * step);
        auto x = center.x + (cos(angle) * radius);
        auto y = center.y + (sin(angle) * radius);
        ofDrawCircle(x, y, 20);
    }
}
