#include "MotorManager.h"

const unsigned NMotors = 28;

const int rows[NMotors] = {0, 0, 0, 0,
                           1, 1, 1, 1,
                        2, 2, 2, 2, 2, 2,
                        3, 3, 3, 3, 3, 3,
                           4, 4, 4, 4,
                           5, 5, 5, 5};

const int cols[NMotors] = {1, 2, 3, 4,
                           1, 2, 3, 4,
                        0, 1, 2, 3, 4, 5,
                        0, 1, 2, 3, 4, 5,
                           1, 2, 3, 4,
                           1, 2, 3, 4};

MotorManager::MotorManager() {
}

void MotorManager::setup() {
    // layout row/column for each motor
    for (unsigned i=0; i<NMotors; i++) {
        Motor m;
        m.setup(i);
        motors.push_back(m);

        MotorTarget t;
        targets.push_back(t);
    }

    // populate color table
    colorMap[MotorState::HALF] = ofColor::orange;
    colorMap[MotorState::FULL] = ofColor::red;
    colorMap[MotorState::OFF] = ofColor::white;
#ifdef ENABLE_MOTORS
    ofLogNotice() << "enabling serialwriter";
    sWriter = new SerialWriter();
    sWriter->setup();
#endif
}

void MotorManager::update() {
#ifdef ENABLE_MOTORS
    sWriter->update();
#endif
}

void MotorManager::winAnimation() {
    // in here because the motor controller arduino
    // happens to be the one with the neopixels attached
#ifdef ENABLE_MOTORS
    sWriter->winAnimation();
#endif
}

void MotorManager::draw(ofVec2f topLeft, int mWidth) {
    for (unsigned int i=0; i < motors.size(); i++) {
        int row = rows[i];
        int col = cols[i];
        auto radius = float(mWidth) / 2;

        // fill color based on motor state
        ofSetColor(colorMap[motors.at(i).getState()]);
        ofFill();
        ofDrawCircle(topLeft.x + (mWidth * col) + radius,
                     topLeft.y + (mWidth * row) + radius,
                     radius);

        // then a black outline
        ofSetColor(ofColor::black);
        ofNoFill();
        ofDrawCircle(topLeft.x + (mWidth * col) + radius,
                     topLeft.y + (mWidth * row) + radius,
                     radius);

        // also save the clickable target box
        targets.at(i).x = topLeft.x + (mWidth * col);
        targets.at(i).y = topLeft.y + (mWidth * row);
        targets.at(i).width = mWidth;
    }

}

void MotorManager::mouseReleased(int x, int y, int button){
    for (unsigned int i=0; i<targets.size(); i++) {
        auto t = targets.at(i);
        if ((x >= t.x && x < (t.x + t.width)) &&
            (y >= t.y && y < (t.y + t.width))) {
            MotorState s = motors.at(i).interact();
            setMotorState(i, s);
        }
    }
}

void MotorManager::allOff() {
    for (auto & motor : motors) {
        motor.setState(MotorState::OFF);
    }
#ifdef ENABLE_MOTORS
    for (int i=0; i < motors.size(); i++) {
        sWriter->setMotor(i, MotorState::OFF);
    }
#endif
}

void MotorManager::setMotorState(int idx, MotorState ms) {
    motors.at(idx).setState(ms);
#ifdef ENABLE_MOTORS
    sWriter->setMotor(idx, ms);
#endif
}
