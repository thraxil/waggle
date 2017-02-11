#include "SerialReader.h"

SerialReader::SerialReader() {

}

void SerialReader::setup(GoalManager * _goals) {
    goals = _goals;
    serial = new ofSerial();
    serial->listDevices();
    if(!serial->setup("/dev/ttyACM0", 9600)) {
        ofLogNotice() << "unable to init serial device";
    }
}

void SerialReader::update() {
    int goal;
    bool on;
    if (serial->available()) {
        // get some data here
        unsigned char bytesReturned[7];
        memset(bytesReturned, 0, sizeof(bytesReturned));
        serial->readBytes(bytesReturned, 6);
        ofLogNotice() << bytesReturned;
        // the messages from the pollen look like
        // 0:ON or 0:OFF or 3:ON etc.
        // ie, GOAL:STATE
        // we take advantage of the fact that there are < 10 goals,
        // so the 0th char gives us an index
        // and we can just use the 3rd char, 'N' or 'F' to
        // figure out the state
        goal = bytesReturned[0] - '0';
        ofLogNotice() << goal;
        on = (bytesReturned[3] == 'N');
        ofLogNotice() << on;
        if (on) {
            goals->select(goal);
        }

    } else {
//         ofLogNotice() << "serial not available";
    }
    serial->flush();
}
