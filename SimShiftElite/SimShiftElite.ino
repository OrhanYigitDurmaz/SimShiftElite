
//  STILL WORK IN PROGRESS! USE IT ON YOUR OWN!!! Also use arduino-pico core from earlphilhowerr

//TODO:
// 1: Clean up messy code and add a better logic
// 2: Add Smoothed library for adc readings -- not needed, because we are adding rangeOffset
// 3: Add the main logic

#include <Arduino.h>
#include <EEPROM.h>
#include <Joystick.h>

struct adcValues {
  int value1;
  int value2;
};

adcValues data[8] = {
  {10, 11},
  {100, 110},
  {1000, 1100},
  {2000, 2100},
  {3000, 0},
  {3000, 60},
  {5000, 40},
  {6000, 20}
};

int rangeOffset = 100;

bool isWithinRange(adcValues values, int rangeOffset, int potValue1, int potValue2) {
  int lowerBound1 = values.value1 - rangeOffset;
  int upperBound1 = values.value1 + rangeOffset;
  int lowerBound2 = values.value2 - rangeOffset;
  int upperBound2 = values.value2 + rangeOffset;

  return ((potValue1 >= lowerBound1 && potValue1 <= upperBound1) &&
          (potValue2 >= lowerBound2 && potValue2 <= upperBound2));
}

void setup() {
  analogReadResolution(12);
  EEPROM.begin(512);
  EEPROM.get(0, data);
  Joystick.begin();
  Serial.begin(115200);
  int rangeOffset = 100;
  
}

void loop() {
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

        } else if (receivedData == "clearEEPROM") {
            Serial.println("clearing");
            int EEPROMSize = EEPROM.length();
            for (int i = 0; i < EEPROMSize; i++) {
            EEPROM.write(i, 0);
            }
            Serial.println("cleared succesfully!");

        } else if (receivedData.indexOf("rangeOffset:") != -1) {
            int rangeOffset = receivedData.substring(receivedData.indexOf(':') + 1).toInt();
            Serial.print("RangeOffset: ");
            Serial.println(rangeOffset);

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
  } Serial.flush();

  int potValue1 = analogRead(A0);
  int potValue2 = analogRead(A1);

  Serial.print(potValue1);
  Serial.print(", ");
  Serial.println(potValue2);
  delay(100);

  for (int i = 0; i < 8; i++) {
    if (isWithinRange(data[i], rangeOffset, potValue1, potValue2)) {
      Serial.print("Shifter ");
      Serial.print(i);
      Serial.println(" is within the range.");
  } else {
      continue;
  }

  }

  delay(100);
}