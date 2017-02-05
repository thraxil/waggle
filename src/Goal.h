#ifndef _GOAL
#define _GOAL

#include "ofMain.h"

class Goal {
public:
    void setup(int _idx);
    void update();
    void draw();

    int idx;
    ofColor color;

    Goal();
private:
};
#endif
