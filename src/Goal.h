#ifndef _GOAL
#define _GOAL

#include "ofMain.h"

class Goal {
public:
    int idx;

    void setup(int _idx);
		void select();
		void unselect();
		bool getIsTarget();

    Goal();
 private:
		bool isTarget;
};
#endif
