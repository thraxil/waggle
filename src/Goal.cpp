#include "Goal.h"
Goal::Goal() {
}

void Goal::setup(int _idx) {
    idx = _idx;
    isTarget = false;
}

void Goal::select() {
    isTarget = true;
}

void Goal::unselect() {
    isTarget = false;
}

bool Goal::getIsTarget() {
    return isTarget;
}
