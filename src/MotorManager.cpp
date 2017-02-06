#include "MotorManager.h"
#define NMOTORS 28

const int rows[NMOTORS] = {0, 0, 0, 0,
                           1, 1, 1, 1,
                        2, 2, 2, 2, 2, 2,
                        3, 3, 3, 3, 3, 3,
                           4, 4, 4, 4,
                           5, 5, 5, 5};

const int cols[NMOTORS] = {1, 2, 3, 4,
                           1, 2, 3, 4,
                        0, 1, 2, 3, 4, 5,
                        0, 1, 2, 3, 4, 5,
                           1, 2, 3, 4,
                           1, 2, 3, 4};

MotorManager::MotorManager() {
}

void MotorManager::setup() {
    // layout row/column for each motor
    for (int i=0; i<NMOTORS; i++) {
        Motor m;
        m.setup(i);
        motors.push_back(m);

        MotorTarget t;
        targets.push_back(t);
    }
}

void MotorManager::update() {
}

void MotorManager::draw(ofVec2f topLeft, int mWidth) {
    for (unsigned int i=0; i < motors.size(); i++) {
        int row = rows[i];
        int col = cols[i];
        auto radius = float(mWidth) / 2;
        ofDrawCircle(topLeft.x + (mWidth * row) + radius,
                     topLeft.y + (mWidth * col) + radius,
                     radius);
        targets.at(i).x = topLeft.x + (mWidth * row);
        targets.at(i).y = topLeft.y + (mWidth * col);
        targets.at(i).width = mWidth;
    }

}

void MotorManager::mouseReleased(int x, int y, int button){
    ofLogNotice() << "motormanager handling mouse click";
    for (unsigned int i=0; i<targets.size(); i++) {
        auto t = targets.at(i);
        if ((x >= t.x && x < (t.x + t.width)) &&
            (y >= t.y && y < (t.y + t.width))) {
            ofLogNotice() << "motor " << i << " clicked";
        }
    }
}
