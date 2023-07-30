#include <Arduino.h>
#include <EEPROM.h>
#include "readSerial.h"
#include "EEPROMFunctions.h"

void readSerial() {
    if (Serial.available()) {

        String receivedData = Serial.readStringUntil('\n');

        if (receivedData == "loadFromEEPROM") {
            Serial.println("loadingFromEEPROM");
            //EEPROM LOADING LOGIC
            Serial.println("loadFromEEPROM DONE");
          
        } else if (receivedData == "writeToEEPROM") {
            Serial.println("writing");
            EEPROM.commit();
            Serial.println("wrote succesfully!");

        } else if (receivedData == "cleareeprom") {
            Serial.println("clearing");
            clearEEPROM();
            Serial.println("cleared succesfully!");

        } else if (receivedData.indexOf("rangeOffset:") != -1) {
            int number = receivedData.substring(receivedData.indexOf(':') + 1).toInt();
            Serial.print("Received number: ");
            Serial.println(number);

        } else if (receivedData == "shifter_1") {
            Serial.println("S1 CALIBRATED");

            //EEPROM.write()

        } else if (receivedData == "shifter_2") {
            Serial.println("S2 CALIBRATED");

        } else if (receivedData == "shifter_3") {
            Serial.println("S3 CALIBRATED");

        } else {
            Serial.println("WRONG_FORMAT");
        }
    }
}