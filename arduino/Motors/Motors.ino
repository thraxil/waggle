#define N_MOTORS 28
#define BLINK_INTERVAL 400

// motor states
#define OFF 0
#define ON 1
#define HALF 2

#define PROTO_ON 0x80
#define PROTO_HALF 0x40
#define PROTO_OFF 0x20
#define MOTOR_FLAG 0x1f

int latchPin = 1;
int clockPin = 2;
int dataPin = 3;

int motorStates[N_MOTORS];
int motorCounters[N_MOTORS];

void setup() {
    Serial.begin(9600);
    pinMode(latchPin, OUTPUT);
    pinMode(clockPin, OUTPUT);
    pinMode(dataPin, OUTPUT);

		for (int i=0; i < N_MOTORS; i++) {
				motorStates[i] = 0;
				motorCounters[i] = 0;
		}
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

/*************************

The protocol for motor control is extremely simple

A message is just one char
the lower 5 bits specify the motor
the upper three bits are flags for ON/HALF/FULL. only one of them can be set.

 ************************/

void checkSerial() {
		unsigned char incomingByte;
		int motor;
		if (Serial.available() > 0) {
				incomingByte = Serial.read();

				Serial.print("USB received: ");
				Serial.println(incomingByte, DEC);

				// mask off lower five bytes for the motor
				motor = incomingByte & MOTOR_FLAG;
				
				if (incomingByte & PROTO_ON) {
						motorStates[motor] = ON;
				} else if (incomingByte & PROTO_HALF) {
						motorStates[motor] = HALF;
				} else if (incomingByte & PROTO_OFF) {
						motorStates[motor] = OFF;
				} else {
						// one of those flags must be set
						Serial.print("received invalid byte");
				}
				// reset its blink counter
				motorCounters[motor] = 0;
		}
}		

void blinkMotors() {
		for (int i=0; i < N_MOTORS; i++) {
				motorCounters[i]++;
				if (motorStates[i] == ON) {
						// on is on
						motorOn(i);
				} else if (motorStates[i] == HALF) {
						// blink logic
						if (motorCounters[i] < BLINK_INTERVAL) {
								motorOn(i);
						} else if (motorCounters[i] >= BLINK_INTERVAL && motorCounters[i] < (2 * BLINK_INTERVAL)) {
								motorOff(i);
						}
				} else {
						// otherwise it's off
						motorOff(i);
				}
		}
}

void loop() {
		//		checkSerial();

		//		blinkMotors();
		// purely for debugging:
    for (int numberToDisplay = 0; numberToDisplay < 8; numberToDisplay++) {
				motorOn(numberToDisplay);
        delay(500);
				motorOff(numberToDisplay);
    }
}
