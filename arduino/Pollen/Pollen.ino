#define N_SENSORS 1
#define BLINK_INTERVAL 400

int ldrP0 = A0;
int ldrP1 = A1;
int ldrP2 = A2;
int ldrP3 = A3;
int ldrP4 = A4;
int ldrP5 = A5;
int ldrP6 = A8;
int ldrP7 = A9;

int ledP0 = 12;
int ledP1 = 3;
int ledP2 = 4;
int ledP3 = 5;
int ledP4 = 6;
int ledP5 = 7;
int ledP6 = 8;
int ledP7 = 9;

int ldrs[8] = {ldrP0,ldrP1, ldrP2, ldrP3, ldrP4, ldrP5,ldrP6, ldrP7};
int leds[8] = {ledP0, ledP1, ledP2, ledP3, ledP4, ledP5, ledP6, ledP7};

int mins[8] = {1024, 1024, 1024, 1024, 1024, 1024, 1024, 1024};
int maxes[8] = {0, 0, 0, 0, 0, 0, 0, 0};
int thresholds[8] = {512, 512, 512, 512, 512, 512, 512, 512};

// blinking or not
int ledStates[8] = {0, 0, 0, 0, 0, 0, 0, 0};
int ledCounter[8] = {0, 0, 0, 0, 0, 0, 0, 0};

int bump = 0;

void setup() {
    Serial.begin(9600);
    for (int i=0; i < N_SENSORS; i++) {
        pinMode(leds[i], OUTPUT);
    }
}

//function to read LEDS
int readSensor(int num){
    int val = analogRead(num);
    return val;
}

void blinkLEDs() {
    for (int k=0; k<N_SENSORS; k++) {
        ledCounter[k]++;
        if (ledStates[k] == 1) {
            if (ledCounter[k] < BLINK_INTERVAL) {
                digitalWrite(leds[k], LOW);
                delay(1);
            }
            if (ledCounter[k] > BLINK_INTERVAL && ledCounter[k] < (BLINK_INTERVAL * 2)) {
                digitalWrite(leds[k], HIGH);
                delay(1);
            }
        } else {
            digitalWrite(leds[k], LOW);
        }
        if (ledCounter[k] > (BLINK_INTERVAL * 2)) {
            ledCounter[k] = 0;
        }
    }
}


void loop() {
		// anything on serial?
		int incomingByte;
		if (Serial.available() > 0) {
				// nothing to do with it yet, but here we are...
				incomingByte = Serial.read();
				Serial.print("USB received: ");
				Serial.println(incomingByte, DEC);
		}
		
    // read sensor data and react
    for(int i=0; i < N_SENSORS; i++){
        int sensorVal =readSensor(ldrs[i]);

        // track min/max seen values and generate a threshold from those
        if (sensorVal > maxes[i]) {
            maxes[i] = sensorVal;
            thresholds[i] = (maxes[i] + mins[i]) / 2;
        }
        if (sensorVal < mins[i]) {
            mins[i] = sensorVal;
            thresholds[i] = (maxes[i] + mins[i]) / 2;
        }

				//        Serial.print(i);
				//        Serial.print(":");
				//        Serial.print(sensorVal);
				//        Serial.println("");

        if(sensorVal <= thresholds[i]){
						if (ledStates[i] == 0) {
								ledStates[i] = 1;
								Serial.print(i);
								Serial.println(":ON");
						}
        } else {
						if (ledStates[i] == 1) {
								ledStates[i] = 0;
								Serial.print(i);
								Serial.println(":OFF");
						}
        }
    }
    bump++;
    if (bump % 1000 == 0) {
        // every once in a while, lower the max
        // so it automatically adjusts to light level
        // changes in the room
        for (int j=0; j < N_SENSORS; j++) {
            maxes[j] = maxes[j] - 1;
            thresholds[j] = (maxes[j] + mins[j]) / 2;
        }
    }

    blinkLEDs();
}
