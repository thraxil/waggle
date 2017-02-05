#ifndef _MOTORMANAGER
#define _MOTORMANAGER

#include "ofMain.h"
#include "Motor.h"

class MotorManager {
public:
    void setup();
    void update();
    void draw(ofVec2f center, int mWidth);

		MotorManager();
 private:
		vector <Motor> motors;
};
#endif
