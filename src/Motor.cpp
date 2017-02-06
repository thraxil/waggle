#include "Motor.h"

Motor::Motor() {
}

void Motor::setup(int _idx) {
    idx = _idx;
    state = MotorState::OFF;

    // set up state transition table
    stateTransitions[MotorState::OFF] = MotorState::HALF;
    stateTransitions[MotorState::HALF] = MotorState::FULL;
    stateTransitions[MotorState::FULL] = MotorState::OFF;
}

MotorState Motor::getState() {
    return state;
}

void Motor::interact() {
    state = stateTransitions[state];
}
