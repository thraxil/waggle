#ifndef _MOTOR
#define _MOTOR
#include "ofMain.h"

enum State {MOTOR_OFF, MOTOR_HALF, MOTOR_FULL};

class Motor {
 public:
		void setup(int _idx);
		Motor();
 private:
		int idx;
		State state;
};

#endif
