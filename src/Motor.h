#ifndef _MOTOR
#define _MOTOR
#include "ofMain.h"

enum class MotorState : int { OFF, HALF, FULL};

class Motor {
 public:
		void setup(int _idx);
		Motor();
		MotorState getState();
		void interact();

 private:
		int idx;
		MotorState state;

};

#endif
