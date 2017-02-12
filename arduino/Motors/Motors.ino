#include <Adafruit_NeoPixel.h>

#define N_MOTORS 28
#define BLINK_INTERVAL 60
#define LEDSTRIP 12
#define NUMPIXELS 30

// motor states
#define OFF 0
#define ON 1
#define HALF 2

#define PROTO_ON 0x80
#define PROTO_HALF 0x40
#define PROTO_OFF 0x20
#define MOTOR_FLAG 0x1f

#define MOTOR_25 6
#define MOTOR_26 7
#define MOTOR_27 8

int latchPin = 2;
int clockPin = 3;
int dataPin = 4;

int motorStates[N_MOTORS];
int motorCounters[N_MOTORS];

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, LEDSTRIP, NEO_GRB + NEO_KHZ800);
int delayVal = 20;
int numLoops = 5;

void setup() {
    Serial.begin(9600);
    pinMode(latchPin, OUTPUT);
    pinMode(clockPin, OUTPUT);
    pinMode(dataPin, OUTPUT);

    pinMode(MOTOR_25, OUTPUT);
    pinMode(MOTOR_26, OUTPUT);
    pinMode(MOTOR_27, OUTPUT);

    for (int i=0; i < N_MOTORS; i++) {
        motorStates[i] = 0;
        motorCounters[i] = 0;
    }
		pixels.begin();
}

void winAnimation() {
		for (int i=0; i < numLoops; i++) {
				for (int j=0; j < NUMPIXELS; j++) {
						pixels.setPixelColor(j, pixels.Color(255, 255, 255));
						pixels.show();
						delay(delayVal);
				}
		}
}

// the bits you want to send
byte bitsToSend[3] = {0, 0, 0};


void registerWrite(int whichPin, int whichState) {
    // three are not on shift registers, just on individual
    // digital out pins
    if (whichPin == 25) {
        digitalWrite(MOTOR_25, whichState);
        return;
    }
    if (whichPin == 26) {
        digitalWrite(MOTOR_26, whichState);
        return;
    }
    if (whichPin == 27) {
        digitalWrite(MOTOR_27, whichState);
        return;
    }
    // shift registers for the rest...

		/* //    Serial.print(whichPin); */
    /* if (whichState) { */
    /*     Serial.print(" ON "); */
    /* } else { */
    /*     Serial.println(" OFF "); */
    /* } */

    // turn off the output so the pins don't light up during the shift
    digitalWrite(latchPin, LOW);

    // turn on the next highest bit in bitsToSend:
    if (whichPin < 8) {
        bitWrite(bitsToSend[0], whichPin, whichState);
    } else if (whichPin < 15) {
        bitWrite(bitsToSend[1], whichPin - 8, whichState);
    } else {
        bitWrite(bitsToSend[2], whichPin - 16, whichState);
    }

    // shift the bits out:
    shiftOut(dataPin, clockPin, MSBFIRST, bitsToSend[0]);
    if (bitsToSend[0] != 0) {
				//        Serial.println(" byte 0");
    }
    shiftOut(dataPin, clockPin, MSBFIRST, bitsToSend[1]);
    if (bitsToSend[1] != 0) {
				//        Serial.println(" byte 1");
    }
    shiftOut(dataPin, clockPin, MSBFIRST, bitsToSend[2]);
    if (bitsToSend[2] != 0) {
				//        Serial.println(" byte 2");
    }

    // ship it
    digitalWrite(latchPin, HIGH);
}

void motorOn(int motor) {
    //    Serial.print("switch on motor ");
    //    Serial.println(motor);
    registerWrite(motor, HIGH);
}

void motorOff(int motor) {
    //    Serial.print("switch off motor ");
    //    Serial.println(motor);
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

				// first, check for a win
				if (incomingByte == 0xFF) {
						winAnimation();
						return;
				}

        // mask off lower five bits for the motor
        motor = incomingByte & MOTOR_FLAG;

        Serial.print("MOTOR: ");
        Serial.println(motor);
        if (incomingByte & PROTO_ON) {
            Serial.println("ON");
            motorStates[motor] = ON;
        } else if (incomingByte & PROTO_HALF) {
            Serial.println("HALF");
            motorStates[motor] = HALF;
        } else if (incomingByte & PROTO_OFF) {
            Serial.println("OFF");
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
    //    for (int k=0; k < 3; k++) {
    //        bitsToSend[k] = 0;
    //    }

    for (int i=0; i < N_MOTORS; i++) {
        motorCounters[i]++;
        if (motorCounters[i] > (2 * BLINK_INTERVAL)) {
            motorCounters[i] = 0;
        }
        if (motorStates[i] == ON) {
            // on is on
            motorOn(i);
        } else if (motorStates[i] == HALF) {
            // blink logic
            if ((millis() % BLINK_INTERVAL) < (BLINK_INTERVAL / 2)) {
								motorOn(i);
						} else {
								motorOff(i);
						}
				} else {
						// otherwise it's off
						motorOff(i);
				}
		}
}

void loop() {
		checkSerial();

		blinkMotors();
		//		delay(1);
		//    delay(10);
		// purely for debugging:
		/* for (int numberToDisplay = 0; numberToDisplay < 28; numberToDisplay++) { */
		/*     motorOn(numberToDisplay); */
		/*     delay(250); */
		/*     motorOff(numberToDisplay); */
		/*    delay(250); */
		/* } */
}
