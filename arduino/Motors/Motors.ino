#include <Adafruit_NeoPixel.h>
//http://forum.arduino.cc/index.php?topic=142753.0


#define SWSerial Serial
#define HWSerial Serial1
#define N_MOTORS 7
#define BLINK_INTERVAL 60
#define LEDSTRIP 12
#define NUMPIXELS 30

#define MOTOR_1 10
#define MOTOR_2 6
#define MOTOR_3 5
#define MOTOR_4 4
#define MOTOR_5 3
#define MOTOR_6 9
#define MOTOR_7 21

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

    HWSerial.begin(9600);
    SWSerial.begin(9600);
    pinMode(latchPin, OUTPUT);
    pinMode(clockPin, OUTPUT);
    pinMode(dataPin, OUTPUT);

    pinMode(MOTOR_25, OUTPUT);
    pinMode(MOTOR_26, OUTPUT);
    pinMode(MOTOR_27, OUTPUT);
    pinMode(MOTOR_1, OUTPUT);
    pinMode(MOTOR_2, OUTPUT);
    pinMode(MOTOR_3, OUTPUT);
    pinMode(MOTOR_4, OUTPUT);
    pinMode(MOTOR_5, OUTPUT);
    pinMode(MOTOR_6, OUTPUT);
    pinMode(MOTOR_7, OUTPUT);
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

    if (whichPin == 0 || whichPin == 1 || whichPin == 5 ||whichPin == 4) {
        digitalWrite(MOTOR_1, whichState);
        return;
    }
    if (whichPin == 2 || whichPin == 3 || whichPin == 7 || whichPin ==  6) {
        digitalWrite(MOTOR_2, whichState);
        return;
    }
    if (whichPin == 9 || whichPin == 8 || whichPin == 15 || whichPin == 14) {
        digitalWrite(MOTOR_3, whichState);
        return;
    }
      if (whichPin == 11 || whichPin == 10 || whichPin == 17 || whichPin == 16) {
        digitalWrite(MOTOR_4, whichState);
        return;
    }
    if (whichPin == 13 || whichPin == 12 || whichPin == 19 || whichPin == 18) {
        digitalWrite(MOTOR_5, whichState);
        return;
    }
    if (whichPin == 21 || whichPin == 20 || whichPin == 24 || whichPin == 25) {
        digitalWrite(MOTOR_6, whichState);
        return;
    }
    if (whichPin == 23 ||whichPin == 22|| whichPin == 27 || whichPin == 26 ) {
        digitalWrite(MOTOR_7, whichState);
        return;
    }

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

void checkSerial(HardwareSerial *this_port) {
    unsigned char incomingByte;
    int motor;
    if (this_port->available() > 0) {
        incomingByte = this_port->read();

        this_port->print("USB received: ");
        this_port->println(incomingByte, DEC);

				// first, check for a win
				if (incomingByte == 0xFF) {
						winAnimation();
						return;
				}

        // mask off lower five bits for the motor
        motor = incomingByte & MOTOR_FLAG;

        this_port->print("MOTOR: ");
        this_port->println(motor);
        if (incomingByte & PROTO_ON) { //we are looking for 0x80
            this_port->println("ON");
            motorStates[motor] = ON;
        } else if (incomingByte & PROTO_HALF) {
            this_port->println("HALF");
            motorStates[motor] = HALF;
        } else if (incomingByte & PROTO_OFF) {
            this_port->println("OFF");
            motorStates[motor] = OFF;
        } else {
            // one of those flags must be set
            this_port->print("received invalid byte");
        }
        // reset its blink counter
        motorCounters[motor] = 0;
    }
}
//function overload
void checkSerial(usb_serial_class *this_port) {
    unsigned char incomingByte;
    int motor;
    if (this_port->available() > 0) {
        incomingByte = this_port->read();

        this_port->print("USB received: ");
        this_port->println(incomingByte, DEC);

				// first, check for a win
				if (incomingByte == 0xFF) {
						winAnimation();
						return;
				}

        // mask off lower five bits for the motor
        motor = incomingByte & MOTOR_FLAG;

        this_port->print("MOTOR: ");
        this_port->println(motor);
        if (incomingByte & PROTO_ON) { //we are looking for 0x80
            this_port->println("ON");
            motorStates[motor] = ON;
        } else if (incomingByte & PROTO_HALF) {
            this_port->println("HALF");
            motorStates[motor] = HALF;
        } else if (incomingByte & PROTO_OFF) {
            this_port->println("OFF");
            motorStates[motor] = OFF;
        } else {
            // one of those flags must be set
            this_port->print("received invalid byte");
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

		checkSerial(&HWSerial);
    checkSerial(&SWSerial);
    digitalWrite(1, HIGH);
    //digitalWrite(1,HIGH);
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
bool inRange(int val, int minimum, int maximum)
{
  return ((minimum <= val) && (val <= maximum));
}
