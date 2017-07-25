#ifndef _SERIALREADER
#define _SERIALREADER

#include "ofMain.h"

#ifdef TARGET_WIN32
#define READ_SERIAL_PORT "WINDOWS SERIAL PORT GOES HERE"
#else
#define READ_SERIAL_PORT "tty.usbmodem2384331"
#endif


class SerialReader {
 public:
		SerialReader();
		void setup();
		int update();

		ofSerial * serial;
};

#endif
