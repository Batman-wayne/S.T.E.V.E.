#include <SoftwareSerial.h>
#include "Servo.h"
SoftwareSerial BTSerial(3, 2); // RX | TX
Servo escl;
Servo escr;
int throttle = '0';
int throttlecont = '0';
const byte numChars = 32;
char receivedChars[numChars];   // an array to store the received data

boolean newData = false;

int dataNumber = 0;             // new for this version

void setup() {
    Serial.begin(9600);
    escl.attach (9);
    escr.attach (10);
    Serial.print("Ready");
    BTSerial.begin(9600);
}

void loop() {
    recvWithEndMarker();
    showNewNumber();
}

void recvWithEndMarker() {
    static byte ndx = 0;
    char endMarker = '\n';
    char rc;
    
    if (BTSerial.available()) {
        rc = BTSerial.read();

        if (rc != endMarker) {
            receivedChars[ndx] = rc;
            ndx++;
            if (ndx >= numChars) {
                ndx = numChars - 1;
            }
        }
        else {
            receivedChars[ndx] = '\0'; // terminate the string
            ndx = 0;
            newData = true;
        }
    }
}

void showNewNumber() {
    if (newData == true) {
        dataNumber = 0;             // new for this version
        dataNumber = atoi(receivedChars);   // new for this version
        throttle = map(dataNumber, 0, 1023, 1000, 2000);
        throttlecont = constrain(throttle, 1000, 2000);
        Serial.println(throttlecont);
        escl.writeMicroseconds(throttlecont);\
        escr.writeMicroseconds(throttlecont);
        newData = false;
    }
}




