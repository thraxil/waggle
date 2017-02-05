#ifndef _GOALMANAGER
#define _GOALMANAGER

#include "ofMain.h"
#include "Goal.h"

class GoalManager {
public:
    void setup(int _ngoals);
    void update();
    void draw(ofVec2f center, float radius);

		GoalManager();
 private:
		vector <Goal> goals;
};
#endif
