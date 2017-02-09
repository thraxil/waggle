#include "SerialReader.h"

SerialReader::SerialReader() {

}

void SerialReader::setup() {
    serial = new ofSerial();
    serial->listDevices();
    serial->setup(0, 57600);
}

void SerialReader::update() {
    // if (serial->available()) {
    //     // get some data here
    // } else {
    //     ofLogNotice() << "serial not available";
    // }
}
