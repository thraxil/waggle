#ifndef _SERIALREADER
#define _SERIALREADER

#include "ofMain.h"

class SerialReader {
 public:
		SerialReader();
		void setup();
		void update();

		ofSerial * serial;
};

#endif
