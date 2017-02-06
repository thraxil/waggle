#include "Motor.h"

Motor::Motor() {
}

void Motor::setup(int _idx) {
    idx = _idx;
    state = MotorState::OFF;
}

MotorState Motor::getState() {
    return state;
}

void Motor::interact() {
    switch(state) {
    case MotorState::OFF:
        state = MotorState::HALF;
        break;
    case MotorState::HALF:
        state = MotorState::FULL;
        break;
    case MotorState::FULL:
        state = MotorState::OFF;
        break;
    }
}
