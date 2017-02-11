#ifndef _SERIALREADER
#define _SERIALREADER

#include "ofMain.h"

class SerialReader {
 public:
		SerialReader();
		void setup();
		int update();

		ofSerial * serial;
};

#endif
