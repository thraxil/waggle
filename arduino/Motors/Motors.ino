// Pin connected to ST_CP of 74HC595
int latchPin = 8;
// Pin connected to SH_CP of 74HC595
int clockPin = 12;
// Pin connected to DS of 74HC595
int dataPin = 11;



void setup() {
    pinMode(latchPin, OUTPUT);
    pinMode(clockPin, OUTPUT);
    pinMode(dataPin, OUTPUT);
}


void registerWrite(int whichPin, int whichState) {
		// the bits you want to send
		byte bitsToSend = 0;

		// turn off the output so the pins don't light up during the shift
		digitalWrite(latchPin, LOW);

		// turn on the next highest bit in bitsToSend:
		bitWrite(bitsToSend, whichPin, whichState);

		// shift the bits out:
		shiftOut(dataPin, clockPin, MSBFIRST, bitsToSend);

    // ship it
		digitalWrite(latchPin, HIGH);
}

void motorOn(int motor) {
		registerWrite(motor, HIGH);
}

void motorOff(int motor) {
		registerWrite(motor, LOW);
}


void loop() {
    // count from 0 to 255 and display the number
    // on the LEDs
    for (int numberToDisplay = 0; numberToDisplay < 256; numberToDisplay++) {
				motorOn(numberToDisplay);
        delay(500);
				motorOff(numberToDisplay);
    }
}
