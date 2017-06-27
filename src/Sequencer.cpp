#include "Sequencer.h"

Sequencer::Sequencer() {
}

// normal 4 full, 4 half, 4 full, 4 weak sequence
Sequence buildStandardSequence(unsigned steps[16]) {
    Sequence s;
    s.steps.push_back({steps[0], MotorState::FULL});
    s.steps.push_back({steps[1], MotorState::FULL});
    s.steps.push_back({steps[2], MotorState::FULL});
   

    s.steps.push_back({steps[3], MotorState::HALF});
    s.steps.push_back({steps[4], MotorState::HALF});


    s.steps.push_back({steps[5], MotorState::FULL});
    s.steps.push_back({steps[6], MotorState::FULL});
    s.steps.push_back({steps[7], MotorState::FULL});


    s.steps.push_back({steps[8], MotorState::HALF});
    s.steps.push_back({steps[9], MotorState::HALF});

    return s;
}

//Sequence buildLimitedSequence(unsigned full[4], unsigned half1[], unsigned half1N,
//                              unsigned half2[], unsigned half2N) {
//    Sequence s;
//    for (unsigned i=0; i<4; i++) {
//        s.steps.push_back({full[i], MotorState::FULL});
//    }
//
//    for (unsigned i=0; i<half1N; i++) {
//        s.steps.push_back({half1[i], MotorState::HALF});
//    }
//
//    for (unsigned i=0; i<4; i++) {
//        s.steps.push_back({full[i], MotorState::FULL});
//    }
//
//    for (unsigned i=0; i<half2N; i++) {
//        s.steps.push_back({half2[i], MotorState::HALF});
//    }
//
//    return s;
//}

void Sequencer::setup(MotorManager * m) {
    motors = m;
    isRunning = false;
    isPaused = false;
    StepTime = 100;

    // define the patterns. remember, motors:
//    0 1
//   2 3 4
//    5 6
    // ------ North ------

    unsigned N1steps[10] = {2, 3, 4, // FULL ->
                            1,0, // HALF <-
                            2,3,4,// FULL ->
                            6,5}; // HALF <-
    auto N1_sequence = buildStandardSequence(N1steps);

    unsigned N2steps[10] = {5,3,1, // FULL ->
                            0,2, // HALF <-
                            5,3,1, // FULL ->
                            4,6}; // HALF <-
    auto N2_sequence = buildStandardSequence(N2steps);

    unsigned N3steps[10] = {6,3,0, // FULL ->
                            2,5, // HALF <-
                            6,3,0, // FULL ->
                            1,4}; // HALF <-
    auto N3_sequence = buildStandardSequence(N3steps);

    unsigned N4steps[10] = {4,3,2, // FULL ->
                            5,6, // HALF <-
                            4,3,2, // FULL ->
                            0,1}; // HALF <-
    auto N4_sequence = buildStandardSequence(N4steps);

    unsigned N5steps[10] = {1,3,5,// FULL ->
                            6,4, // HALF <-
                            1,3,5, // FULL ->
                            2,0}; // HALF <-
    auto N5_sequence = buildStandardSequence(N5steps);
   
    unsigned N6steps[10] = {0,3,6, // FULL ->
                            4,1, // HALF <-
                            0,3,6, // FULL ->
                            5,2}; // HALF <-
    auto N6_sequence = buildStandardSequence(N6steps);
    
 

    patterns[0] = N1_sequence;
    patterns[5] = N2_sequence;
    patterns[4] = N3_sequence;
    patterns[3] = N4_sequence;
    patterns[2] = N5_sequence;
    patterns[1] = N6_sequence;

   

    
    lastMotor = 0;
}

void Sequencer::update() {
    if (!isRunning || isPaused) {
        return;
    }
    auto currentTime = ofGetElapsedTimeMillis();
    if (currentTime > nextStepTime) {
        nextStepTime = currentTime + StepTime;
        auto idx = step % currentSequence.steps.size();
        auto s = currentSequence.steps.at(idx);
     //   cout << idx << endl;
        motors->setMotorState(lastMotor, MotorState::OFF);
        motors->setMotorState(s.motor, s.state);
        lastMotor = s.motor;
        step++;
    }
}

void Sequencer::start(int goal) {
    
    cout << goal << " is the goal number from the sequencer " << endl;
    // select a sequence for the goal
    currentSequence = patterns.at(goal);

    isRunning = true;
    startTime = ofGetElapsedTimeMillis();
    // kick it off directly
    nextStepTime = startTime;
    step = 0;
}

void Sequencer::stop() {
    isRunning = false;
    motors->allOff();
}

void Sequencer::togglePause() {
    isPaused = !isPaused;
}

void Sequencer::speedUp() {
    StepTime *= .9;
    ofLogNotice() << StepTime;
}

void Sequencer::speedDown() {
    StepTime *= 1.1;
    ofLogNotice() << StepTime;
}
