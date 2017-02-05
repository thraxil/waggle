#include "Motor.h"

#define MOTOR_OFF 0
#define MOTOR_HALF 1
#define MOTOR_FULL 2

Motor::Motor() {
}

void Motor::setup(int _idx) {
    idx = _idx;
    state = MOTOR_OFF;
}
