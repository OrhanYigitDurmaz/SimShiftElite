#include <Arduino.h>

void setup() {

Serial.begin(115200)

}

void readSerial() {

    if (Serial.avaliable()) {

        String receivedData = Serial.readStringUntil("\n")

        if (receivedData == "loadEEPROM") {
            //DO LOAD EEPROM
        } else if (receivedData == "")   

    }

}

void loop() {

    readSerial();

}
