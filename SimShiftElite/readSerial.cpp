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
            data[1].value1 = analogRead(A0);
            data[1].value2 = analogRead(A1);
            Serial.println("S1 CALIBRATED");

        } else if (receivedData == "shifter_2") {
            data[2].value1 = analogRead(A0);
            data[2].value2 = analogRead(A1);
            Serial.println("S2 CALIBRATED");

        } else if (receivedData == "shifter_3") {
            data[3].value1 = analogRead(A0);
            data[3].value2 = analogRead(A1);
            Serial.println("S3 CALIBRATED");

        } else if (receivedData == "shifter_4") {
            data[4].value1 = analogRead(A0);
            data[4].value2 = analogRead(A1);
            Serial.println("S4 CALIBRATED");

        } else if (receivedData == "shifter_5") {
            data[5].value1 = analogRead(A0);
            data[5].value2 = analogRead(A1);
            Serial.println("S5 CALIBRATED");

        } else if (receivedData == "shifter_6") {
            data[6].value1 = analogRead(A0);
            data[6].value2 = analogRead(A1);
            Serial.println("S6 CALIBRATED");
        
        } else if (receivedData == "shifter_7") {
            data[7].value1 = analogRead(A0);
            data[7].value2 = analogRead(A1);
            Serial.println("S7 CALIBRATED");

        } else if (receivedData == "shifter_8") {
            data[8].value1 = analogRead(A0);
            data[8].value2 = analogRead(A1);
            Serial.println("S8 CALIBRATED");

        } else {
            Serial.println("WRONG_FORMAT");
        }
    }
}