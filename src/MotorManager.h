#ifndef _MOTORMANAGER
#define _MOTORMANAGER

#include "ofMain.h"
#include "Motor.h"

class MotorManager {
public:
    void setup();
    void update();
    void draw(ofVec2f topLeft, int mWidth);
		void mouseReleased(int x, int y, int button);		

		MotorManager();
 private:
		vector <Motor> motors;
};
#endif
