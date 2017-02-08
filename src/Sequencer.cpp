#include "Sequencer.h"

Sequencer::Sequencer() {
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

    Sequence N1_sequence;
    N1_sequence.steps.push_back({16, MotorState::FULL});
    N1_sequence.steps.push_back({10, MotorState::FULL});
    N1_sequence.steps.push_back({5, MotorState::FULL});
    N1_sequence.steps.push_back({1, MotorState::FULL});

    N1_sequence.steps.push_back({0, MotorState::HALF});
    N1_sequence.steps.push_back({4, MotorState::HALF});
    N1_sequence.steps.push_back({9, MotorState::HALF});
    N1_sequence.steps.push_back({15, MotorState::HALF});

    N1_sequence.steps.push_back({16, MotorState::FULL});
    N1_sequence.steps.push_back({10, MotorState::FULL});
    N1_sequence.steps.push_back({5, MotorState::FULL});
    N1_sequence.steps.push_back({1, MotorState::FULL});

    N1_sequence.steps.push_back({2, MotorState::HALF});
    N1_sequence.steps.push_back({6, MotorState::HALF});
    N1_sequence.steps.push_back({11, MotorState::HALF});
    N1_sequence.steps.push_back({17, MotorState::HALF});

    Sequence N2_sequence;
    N2_sequence.steps.push_back({17, MotorState::FULL});
    N2_sequence.steps.push_back({11, MotorState::FULL});
    N2_sequence.steps.push_back({6, MotorState::FULL});
    N2_sequence.steps.push_back({2, MotorState::FULL});

    N2_sequence.steps.push_back({1, MotorState::HALF});
    N2_sequence.steps.push_back({5, MotorState::HALF});
    N2_sequence.steps.push_back({10, MotorState::HALF});
    N2_sequence.steps.push_back({16, MotorState::HALF});

    N2_sequence.steps.push_back({17, MotorState::FULL});
    N2_sequence.steps.push_back({11, MotorState::FULL});
    N2_sequence.steps.push_back({6, MotorState::FULL});
    N2_sequence.steps.push_back({2, MotorState::FULL});

    N2_sequence.steps.push_back({3, MotorState::HALF});
    N2_sequence.steps.push_back({7, MotorState::HALF});
    N2_sequence.steps.push_back({12, MotorState::HALF});
    N2_sequence.steps.push_back({18, MotorState::HALF});

    Sequence N3_sequence;
    N3_sequence.steps.push_back({21, MotorState::FULL});
    N3_sequence.steps.push_back({16, MotorState::FULL});
    N3_sequence.steps.push_back({10, MotorState::FULL});
    N3_sequence.steps.push_back({5, MotorState::FULL});

    N3_sequence.steps.push_back({4, MotorState::HALF});
    N3_sequence.steps.push_back({9, MotorState::HALF});
    N3_sequence.steps.push_back({15, MotorState::HALF});
    N3_sequence.steps.push_back({20, MotorState::HALF});

    N3_sequence.steps.push_back({21, MotorState::FULL});
    N3_sequence.steps.push_back({16, MotorState::FULL});
    N3_sequence.steps.push_back({10, MotorState::FULL});
    N3_sequence.steps.push_back({5, MotorState::FULL});

    N3_sequence.steps.push_back({6, MotorState::HALF});
    N3_sequence.steps.push_back({11, MotorState::HALF});
    N3_sequence.steps.push_back({17, MotorState::HALF});
    N3_sequence.steps.push_back({22, MotorState::HALF});

    Sequence N4_sequence;
    N4_sequence.steps.push_back({22, MotorState::FULL});
    N4_sequence.steps.push_back({17, MotorState::FULL});
    N4_sequence.steps.push_back({11, MotorState::FULL});
    N4_sequence.steps.push_back({6, MotorState::FULL});

    N4_sequence.steps.push_back({5, MotorState::HALF});
    N4_sequence.steps.push_back({10, MotorState::HALF});
    N4_sequence.steps.push_back({16, MotorState::HALF});
    N4_sequence.steps.push_back({21, MotorState::HALF});

    N4_sequence.steps.push_back({22, MotorState::FULL});
    N4_sequence.steps.push_back({17, MotorState::FULL});
    N4_sequence.steps.push_back({11, MotorState::FULL});
    N4_sequence.steps.push_back({6, MotorState::FULL});

    N4_sequence.steps.push_back({7, MotorState::HALF});
    N4_sequence.steps.push_back({12, MotorState::HALF});
    N4_sequence.steps.push_back({18, MotorState::HALF});
    N4_sequence.steps.push_back({23, MotorState::HALF});

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
        step++;
        nextStepTime += 1000;
        auto idx = step % currentSequence.steps.size();
        ofLogNotice() << idx;
        auto s = currentSequence.steps.at(idx);
        ofLogNotice() << s.motor;
        motors->allOff();
        motors->setMotorState(s.motor, s.state);
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
