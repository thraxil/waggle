#include "GoalManager.h"
#define GOAL_SCALE 0.05

GoalManager::GoalManager() {
}

void GoalManager::setup(int ngoals, Sequencer * _sequencer) {
    sequencer = _sequencer;
    for (int i=0; i < ngoals; i++) {
        Goal g;
        g.setup(i);
        goals.push_back(g);

        GoalTarget t;
        targets.push_back(t);
    }
}

void GoalManager::update() {
}

void GoalManager::draw(ofVec2f center, float radius) {
    auto step = 360.0 / goals.size();
    auto size = GOAL_SCALE * radius;


    for (unsigned int i=0; i<goals.size(); i++) {
        auto angle = ofDegToRad((i * step) - 90);
        auto x = center.x + (cos(angle) * radius);
        auto y = center.y + (sin(angle) * radius);
        auto goal = goals.at(i);
        if (goal.getIsSelected()) {
            ofFill();
            ofSetColor(ofColor::yellow);
            ofDrawCircle(x, y, size * 1.3);
            ofNoFill();
            ofSetColor(ofColor::black);
            ofDrawCircle(x, y, size * 1.3);
        }
        ofFill();
        if (goal.getIsTarget()) {
            ofSetColor(ofColor::orange);
        } else {
            ofSetColor(ofColor::white);
        }
        ofDrawCircle(x, y, size);
        // and an outline
        ofNoFill();
        ofSetColor(ofColor::black);
        ofDrawCircle(x, y, size);

        // save a target for clicking
        targets.at(i).x = x;
        targets.at(i).y = y;
        targets.at(i).radius = size;
    }
}

void GoalManager::mouseReleased(int x, int y, int button){
    for (unsigned int i=0; i<targets.size(); i++) {
        auto t = targets.at(i);
        auto distance = ofDist(x, y, t.x, t.y);
        if (distance < t.radius) {
            auto isTarget = goals.at(i).getIsTarget();
            clearAll();
            if (!isTarget) {
                goals.at(i).selectTarget();
                sequencer->start(i);
            } else {
                sequencer->stop();
            }
        }
    }
}

void GoalManager::clearAll() {
    for (auto & goal : goals) {
        goal.unselectTarget();
    }
}

void GoalManager::select(int g) {
    for (auto & goal : goals) {
        goal.unselect();
    }
    goals.at(g).select();
}
