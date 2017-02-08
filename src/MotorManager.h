#ifndef _MOTORMANAGER
#define _MOTORMANAGER

#include "ofMain.h"
#include "Motor.h"

struct MotorTarget {
		int x, y;
		float width;
};

class MotorManager {
public:
    void setup();
    void update();
    void draw(ofVec2f topLeft, int mWidth);
		void mouseReleased(int x, int y, int button);
		void setMotorState(int, MotorState);

		MotorManager();
 private:
		vector <Motor> motors;
		vector <MotorTarget> targets;
    std::map<MotorState,ofColor> colorMap;
};
#endif
