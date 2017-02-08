#include "Sequencer.h"

Sequencer::Sequencer() {
}

// normal 4 full, 4 half, 4 full, 4 weak sequence
Sequence buildStandardSequence(unsigned steps[16]) {
    Sequence s;    
    s.steps.push_back({steps[0], MotorState::FULL});
    s.steps.push_back({steps[1], MotorState::FULL});
    s.steps.push_back({steps[2], MotorState::FULL});
    s.steps.push_back({steps[3], MotorState::FULL});

    s.steps.push_back({steps[4], MotorState::HALF});
    s.steps.push_back({steps[5], MotorState::HALF});
    s.steps.push_back({steps[6], MotorState::HALF});
    s.steps.push_back({steps[7], MotorState::HALF});

    s.steps.push_back({steps[8], MotorState::FULL});
    s.steps.push_back({steps[9], MotorState::FULL});
    s.steps.push_back({steps[10], MotorState::FULL});
    s.steps.push_back({steps[11], MotorState::FULL});

    s.steps.push_back({steps[12], MotorState::HALF});
    s.steps.push_back({steps[13], MotorState::HALF});
    s.steps.push_back({steps[14], MotorState::HALF});
    s.steps.push_back({steps[15], MotorState::HALF});
    return s;
}

void Sequencer::setup(MotorManager * m) {
    motors = m;
    isRunning = false;

    // define the patterns. remember, motors:
    //             -  0  1  2  3  -
    //             -  4  5  6  7  -
    //             8  9 10 11 12 13
    //            14 15 16 17 18 19
    //             - 20 21 22 23  -
    //             - 24 25 26 27  -

    // ------ North ------

n    unsigned N1steps[16] = {16, 10, 5, 1, // FULL ->
                            0, 4, 9, 15, // HALF <-
                            16, 10, 5, 1, // FULL ->
                            2, 6, 11, 17}; // HALF <-
    auto N1_sequence = buildStandardSequence(N1steps);

    unsigned N2steps[16] = {17, 11, 6, 2, // FULL ->
                            1, 5, 10, 16, // HALF <-
                            17, 11, 6, 2, // FULL ->
                            3, 7, 12, 18}; // HALF <-
    auto N2_sequence = buildStandardSequence(N2steps);

    unsigned N3steps[16] = {21, 16, 10, 5, // FULL ->
                            4, 9, 15, 20, // HALF <-
                            21, 16, 10, 5, // FULL ->
                            6, 11, 17, 22}; // HALF <-
    auto N3_sequence = buildStandardSequence(N3steps);
    
    unsigned N4steps[16] = {22, 17, 11, 6, // FULL ->
                            5, 10, 16, 21, // HALF <-
                            22, 17, 11, 6, // FULL ->
                            7, 12, 18, 23}; // HALF <-
    auto N4_sequence = buildStandardSequence(N4steps);
    
    Pattern p1;
    p1.sequences.push_back(N1_sequence);
    p1.sequences.push_back(N2_sequence);
    p1.sequences.push_back(N3_sequence);
    p1.sequences.push_back(N4_sequence);

    patterns[0] = p1;


    // NE
    // E
    // SE
    // S
    // SW
    // W
    // NW
}

void Sequencer::update() {
    if (!isRunning) {
        return;
    }
    auto currentTime = ofGetElapsedTimeMillis();
    if (currentTime > nextStepTime) {
        nextStepTime += 1000;
        auto idx = step % currentSequence.steps.size();
        ofLogNotice() << idx;
        auto s = currentSequence.steps.at(idx);
        ofLogNotice() << s.motor;
        motors->allOff();
        motors->setMotorState(s.motor, s.state);
        step++;
    }
}

void Sequencer::start(int goal) {
    // select a sequence for the goal
    auto size = patterns.at(goal).sequences.size();
    currentSequence = patterns.at(goal).sequences.at(std::rand() % size);

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
