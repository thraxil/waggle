#ifndef _SEQUENCER
#define _SEQUENCER

#include "ofMain.h"
#include "Motor.h"
#include "MotorManager.h"

struct Step {
    unsigned motor;
    MotorState state;
};

struct Sequence {
		vector <Step> steps;
};

struct Pattern {
		vector <Sequence> sequences;
};

class Sequencer {
 public:
    void setup(MotorManager *);
		void update();
		void start(int);
		void stop();
		
    Sequencer();
 private:
		bool isRunning;
		MotorManager * motors;
		float startTime;
		float nextStepTime;
		int goal;
		int step;
		Sequence currentSequence;
		std::map <int, Pattern> patterns;
};
#endif