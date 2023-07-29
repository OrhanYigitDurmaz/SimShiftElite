#include <Arduino.h>
void setup() {

Serial.begin(115200);

}

void readSerial() {

    if (Serial.available()) {

        String receivedData = Serial.readStringUntil("\n")

        if (receivedData == "shifter_1") {
            
            Serial.println("S1 CALIBRATED");

        } else if (receivedData == "shifter_2") {

            Serial.println("S2 CALIBRATED");

        } else if (receivedData == "shifter_3") {

            Serial.println("S3 CALIBRATED");
            
        } 

    }

}

void loop() {

    readSerial();

}
