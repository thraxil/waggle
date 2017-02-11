#ifndef _SERIALREADER
#define _SERIALREADER

#include "ofMain.h"
#include "GoalManager.h"

class SerialReader {
 public:
		SerialReader();
		void setup(GoalManager *);
		void update();

		ofSerial * serial;
		GoalManager *goals;
};

#endif
