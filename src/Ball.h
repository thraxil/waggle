#ifndef _BALL
#define _BALL

#include "ofMain.h"

class Ball {
public:
    void setup(float _x, float _y, int _dim);
    void update();
    void draw();

    float x;
    float y;
    float speedX;
    float speedY;
    int dim;
    ofColor color;

    Ball();
private:
};
#endif
