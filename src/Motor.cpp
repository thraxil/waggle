#include "Motor.h"

Motor::Motor() {
}

void Motor::setup(int _idx) {
    idx = _idx;
    state = MOTOR_OFF;
}
