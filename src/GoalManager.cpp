#include "GoalManager.h"
#define GOAL_SCALE 0.05

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
    auto size = GOAL_SCALE * radius;
    ofSetColor(ofColor::black);
    ofFill();
    for (unsigned int i=0; i<goals.size(); i++) {
        auto angle = ofDegToRad(i * step);
        auto x = center.x + (cos(angle) * radius);
        auto y = center.y + (sin(angle) * radius);
        ofDrawCircle(x, y, size);
    }
    screenCenter = center;
    goalsRadius = radius;
    goalSize = size;
}

void GoalManager::mouseReleased(int x, int y, int button){
    ofLogNotice() << "goalanager handling mouse click";
    auto step = 360.0 / goals.size();
    for (unsigned int i=0; i<goals.size(); i++) {
        auto angle = ofDegToRad(i * step);
        auto goalX = screenCenter.x + (cos(angle) * goalsRadius);
        auto goalY = screenCenter.y + (sin(angle) * goalsRadius);
        auto distance = ofDist(x, y, goalX, goalY);
        if (distance < goalSize) {
            ofLogNotice() << "goal " << i << " clicked";
        }
    }
}
