#ifndef _GOALMANAGER
#define _GOALMANAGER

#include "ofMain.h"
#include "Goal.h"

class GoalManager {
public:
    void setup(int _ngoals);
    void update();
    void draw(ofVec2f center, float radius);
		void mouseReleased(int x, int y, int button);

		GoalManager();
 private:
		vector <Goal> goals;
		ofVec2f screenCenter;
		float goalsRadius;
		float goalSize;
};
#endif
