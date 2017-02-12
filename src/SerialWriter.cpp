#include "SerialWriter.h"

SerialWriter::SerialWriter() {

}

void SerialWriter::setup() {
    serial = new ofSerial();
    serial->listDevices();
    if(!serial->setup("/dev/ttyACM0", 9600)) {
        ofLogNotice() << "unable to init serial device";
    }
}

void SerialWriter::update() {
}

void SerialWriter::setMotor(int m, MotorState ms) {
    unsigned char b = 0;
    b = MOTOR_MASK & m;
    if (ms == MotorState::FULL) {
        b |= PROTO_ON;
    } else if (ms == MotorState::HALF) {
        b |= PROTO_HALF;
    } else {
        b |= PROTO_OFF;
    }
    ofLogNotice() << "writing " << b;
    if(serial->isInitialized()){
        ofLogNotice() << "writing serial data";
        serial->writeByte(b);
    } else {
        ofLogNotice() << "no serial available";
    }
}
