#include "Sequencer.h"

const int StepTime = 100;

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

Sequence buildLimitedSequence(unsigned full[4], unsigned half1[], unsigned half1N,
                              unsigned half2[], unsigned half2N) {
    Sequence s;
    for (unsigned i=0; i<4; i++) {
        s.steps.push_back({full[i], MotorState::FULL});
    }

    for (unsigned i=0; i<half1N; i++) {
        s.steps.push_back({half1[i], MotorState::HALF});
    }

    for (unsigned i=0; i<4; i++) {
        s.steps.push_back({full[i], MotorState::FULL});
    }

    for (unsigned i=0; i<half2N; i++) {
        s.steps.push_back({half2[i], MotorState::HALF});
    }

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

    unsigned N1steps[16] = {16, 10, 5, 1, // FULL ->
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

    Pattern p0;
    p0.sequences.push_back(N1_sequence);
    p0.sequences.push_back(N2_sequence);
    p0.sequences.push_back(N3_sequence);
    p0.sequences.push_back(N4_sequence);

    patterns[0] = p0;


    // NE
    unsigned NE1steps[16] = {20, 16, 11, 7, // FULL ->
                             3, 6, 10, 15, // HALF <-
                             20, 16, 11, 7, // FULL ->
                             12, 17, 21, 24}; // HALF <-
    auto NE1_sequence = buildStandardSequence(NE1steps);
    unsigned NE2steps[16] = {24, 21, 17, 12, // FULL ->
                             7, 11, 16, 20, // HALF <-
                             24, 21, 17, 12, // FULL ->
                             13, 18, 22, 25}; // HALF <-
    auto NE2_sequence = buildStandardSequence(NE2steps);

    Pattern p1;
    p1.sequences.push_back(NE1_sequence);
    p1.sequences.push_back(NE2_sequence);

    patterns[1] = p1;

    // E

    unsigned E1steps[16] = {9, 10, 11, 12, // FULL ->
                            7, 6, 5, 4, // HALF <-
                            9, 10, 11, 12, // FULL ->
                            18, 17, 16, 15}; // HALF <-
    auto E1_sequence = buildStandardSequence(E1steps);

    unsigned E2steps[16] = {15, 16, 17, 18, // FULL ->
                            12, 11, 10, 9, // HALF <-
                            15, 16, 17, 18, // FULL ->
                            23, 22, 21, 20}; // HALF <-
    auto E2_sequence = buildStandardSequence(E2steps);

    unsigned E3full[4] = {10, 11, 12, 13};
    unsigned E3half1[3] = {7, 6, 5};
    unsigned E3half2[4] = {19, 18, 17, 16};
    auto E3_sequence = buildLimitedSequence(E3full, E3half1, 3, E3half2, 4);

    unsigned E4full[4] = {16, 17, 18, 19};
    unsigned E4half1[4] = {13, 12, 11, 10};
    unsigned E4half2[3] = {23, 22, 21};
    auto E4_sequence = buildLimitedSequence(E4full, E4half1, 4, E4half2, 3);

    Pattern p2;
    p2.sequences.push_back(E1_sequence);
    p2.sequences.push_back(E2_sequence);
    p2.sequences.push_back(E3_sequence);
    p2.sequences.push_back(E4_sequence);

    patterns[2] = p2;

    // SE
    unsigned SE1steps[16] = {0, 5, 11, 18, // FULL ->
                             19, 12, 6, 1, // HALF <-
                             0, 5, 11, 18, // FULL ->
                             23, 17, 10, 4}; // HALF <-
    auto SE1_sequence = buildStandardSequence(SE1steps);
    unsigned SE2steps[16] = {4, 10, 17, 23, // FULL ->
                             18, 11, 5, 0, // HALF <-
                             4, 10, 17, 23, // FULL ->
                             27, 22, 16, 9}; // HALF <-
    auto SE2_sequence = buildStandardSequence(SE2steps);

    Pattern p3;
    p3.sequences.push_back(SE1_sequence);
    p3.sequences.push_back(SE2_sequence);

    patterns[3] = p3;

    // S
    unsigned S1steps[16] = {10, 16, 21, 25, // FULL ->
                            24, 20, 15, 9, // HALF <-
                            10, 16, 21, 25, // FULL ->
                            26, 22, 17, 11}; // HALF <-
    auto S1_sequence = buildStandardSequence(S1steps);

    unsigned S2steps[16] = {11, 17, 22, 26, // FULL ->
                            25, 21, 16, 10, // HALF <-
                            11, 17, 22, 26, // FULL ->
                            27, 23, 18, 12}; // HALF <-
    auto S2_sequence = buildStandardSequence(S2steps);

    unsigned S3steps[16] = {5, 10, 16, 21, // FULL ->
                            20, 15, 9, 4, // HALF <-
                            5, 10, 16, 21, // FULL ->
                            22, 17, 11, 6}; // HALF <-
    auto S3_sequence = buildStandardSequence(S3steps);

    unsigned S4steps[16] = {6, 11, 17, 22, // FULL ->
                            21, 16, 10, 5, // HALF <-
                            6, 11, 17, 22, // FULL ->
                            23, 18, 12, 7}; // HALF <-
    auto S4_sequence = buildStandardSequence(S4steps);

    Pattern p4;
    p4.sequences.push_back(S1_sequence);
    p4.sequences.push_back(S2_sequence);
    p4.sequences.push_back(S3_sequence);
    p4.sequences.push_back(S4_sequence);

    patterns[4] = p4;
    // SW
    unsigned SW1steps[16] = {3, 6, 10, 15, // FULL ->
                             14, 9, 5, 2, // HALF <-
                             3, 6, 10, 15, // FULL ->
                             20, 16, 11, 7}; // HALF <-
    auto SW1_sequence = buildStandardSequence(SW1steps);
    unsigned SW2steps[16] = {7, 11, 16, 20, // FULL ->
                             15, 10, 6, 3, // HALF <-
                             7, 11, 16, 20, // FULL ->
                             24, 21, 17, 12}; // HALF <-
    auto SW2_sequence = buildStandardSequence(SW2steps);

    Pattern p5;
    p5.sequences.push_back(SW1_sequence);
    p5.sequences.push_back(SW2_sequence);
    patterns[5] = p5;
    // W

    unsigned W1steps[16] = {12, 11, 10, 9, // FULL ->
                            4, 5, 6, 7, // HALF <-
                            12, 11, 10, 9, // FULL ->
                            15, 16, 17, 18}; // HALF <-
    auto W1_sequence = buildStandardSequence(W1steps);

    unsigned W2steps[16] = {18, 17, 16, 15, // FULL ->
                            9, 10, 11, 12, // HALF <-
                            18, 17, 16, 15,// FULL ->
                            20, 21, 22, 23}; // HALF <-
    auto W2_sequence = buildStandardSequence(W2steps);

    unsigned W3full[4] = {11, 10, 9, 8};
    unsigned W3half1[3] = {4, 5, 6};
    unsigned W3half2[4] = {14, 15, 16, 17};
    auto W3_sequence = buildLimitedSequence(W3full, W3half1, 3, W3half2, 4);

    unsigned W4full[4] = {17, 16, 15, 14};
    unsigned W4half1[4] = {8, 9, 10, 11};
    unsigned W4half2[3] = {20, 21, 22};
    auto W4_sequence = buildLimitedSequence(W4full, W4half1, 4, W4half2, 3);

    Pattern p6;
    p6.sequences.push_back(W1_sequence);
    p6.sequences.push_back(W2_sequence);
    p6.sequences.push_back(W3_sequence);
    p6.sequences.push_back(W4_sequence);

    patterns[6] = p6;

    // NW
    unsigned NW1steps[16] = {18, 11, 5, 0, // FULL ->
                             1, 6, 12, 19, // HALF <-
                             18, 11, 5, 0, // FULL ->
                             4, 10, 17, 23}; // HALF <-
    auto NW1_sequence = buildStandardSequence(NW1steps);
    unsigned NW2steps[16] = {23, 17, 10, 4, // FULL ->
                             0, 5, 11, 18, // HALF <-
                             23, 17, 10, 4, // FULL ->
                             9, 16, 22, 27}; // HALF <-
    auto NW2_sequence = buildStandardSequence(NW2steps);

    Pattern p7;
    p7.sequences.push_back(NW1_sequence);
    p7.sequences.push_back(NW2_sequence);
    patterns[7] = p7;
}

void Sequencer::update() {
    if (!isRunning) {
        return;
    }
    auto currentTime = ofGetElapsedTimeMillis();
    if (currentTime > nextStepTime) {
        nextStepTime += StepTime;
        auto idx = step % currentSequence.steps.size();
        auto s = currentSequence.steps.at(idx);
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
