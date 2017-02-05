#ifndef _MOTOR
#define _MOTOR
#include "ofMain.h"

class Motor {
 public:
		void setup(int _idx);
		Motor();
 private:
		int idx;
		int state;
};

#endif
