#ifndef _GOALMANAGER
#define _GOALMANAGER

#include "ofMain.h"
#include "Goal.h"
#include "Sequencer.h"

struct GoalTarget {
		int x, y;
		float radius;
};

class GoalManager {
public:
    void setup(int, Sequencer *);
    void update();
    void draw(ofVec2f center, float radius);
		void mouseReleased(int x, int y, int button);
		void clearAll();

		GoalManager();
 private:
		vector <Goal> goals;
		vector <GoalTarget> targets;
		Sequencer * sequencer;
};
#endif
