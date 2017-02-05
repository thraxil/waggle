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
    }
}

void MotorManager::update() {
}

void MotorManager::draw(ofVec2f center, int mWidth) {
    ofVec2f topLeft(center.x - (mWidth * 3), center.y - (mWidth * 3));
    for (int i=0; i < motors.size(); i++) {
        int row = rows[i];
        int col = cols[i];
        auto radius = float(mWidth) / 2;
        ofDrawCircle(topLeft.x + (mWidth * row) + radius,
                     topLeft.y + (mWidth * col) + radius,
                     radius);
    }

}
