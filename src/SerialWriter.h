#ifndef _SERIALWRITER
#define _SERIALWRITER

#include "ofMain.h"
#include "Motor.h"

#define PROTO_ON 0x80
#define PROTO_HALF 0x40
#define PROTO_OFF 0x20
#define MOTOR_MASK 0x1f

class SerialWriter {
 public:
		SerialWriter();
		void setup();
		void update();
		void setMotor(int, MotorState);
		void winAnimation();

 private:
		ofSerial * serial;
};

#endif
