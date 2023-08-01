
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

adcValues data[9] = {
  {10, 10},
  {20, 20},
  {30, 30},
  {40, 40},
  {50, 50},
  {60, 60},
  {70, 70},
  {80, 80},
  {100, 100}    //first one is the rangeOffset. its here because it gets written to the eeprom
};

int rangeOffset = data[8].value1;

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
  byte eepromstatus = EEPROM.read(0);
  if (eepromstatus != 0) {
    EEPROM.get(0, data);
  } else {
  
  }
  Joystick.begin();
  Serial.begin(115200);
  rangeOffset = data[8].value1;
  
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
            EEPROM.put(0, data);
            EEPROM.commit();
            Serial.println("wrote succesfully!");

        } else if (receivedData == "clearEEPROM") {
            Serial.println("clearing");
            for (int i = 0; i < 512; i++) {
            EEPROM.write(i, 0);
            }
            EEPROM.commit();
            Serial.println("cleared succesfully!");

        } else if (receivedData == "clearDATA") {
            Serial.println("clearing");
            for (int i = 0; i < 9; i++) {
              data[i].value1 = 0;
              data[i].value2 = 0;
            }
            Serial.println("cleared succesfully!");

        } else if (receivedData.indexOf("rangeOffset:") != -1) {
            int newRangeOffset = receivedData.substring(receivedData.indexOf(':') + 1).toInt();
            rangeOffset = newRangeOffset;
            Serial.print("RangeOffset: ");
            Serial.println(rangeOffset);
            data[8].value1 = rangeOffset;

        } else if (receivedData == "print") {
            Serial.println(rangeOffset);

        } else if (receivedData == "shifter_1") {
            data[0].value1 = analogRead(A0);
            data[0].value2 = analogRead(A1);
            Serial.println("S1 CALIBRATED");

        } else if (receivedData == "shifter_2") {
            data[1].value1 = analogRead(A0);
            data[1].value2 = analogRead(A1);
            Serial.println("S2 CALIBRATED");

        } else if (receivedData == "shifter_3") {
            data[2].value1 = analogRead(A0);
            data[2].value2 = analogRead(A1);
            Serial.println("S3 CALIBRATED");

        } else if (receivedData == "shifter_4") {
            data[3].value1 = analogRead(A0);
            data[3].value2 = analogRead(A1);
            Serial.println("S4 CALIBRATED");

        } else if (receivedData == "shifter_5") {
            data[4].value1 = analogRead(A0);
            data[4].value2 = analogRead(A1);
            Serial.println("S5 CALIBRATED");

        } else if (receivedData == "shifter_6") {
            data[5].value1 = analogRead(A0);
            data[5].value2 = analogRead(A1);
            Serial.println("S6 CALIBRATED");
        
        } else if (receivedData == "shifter_7") {
            data[6].value1 = analogRead(A0);
            data[6].value2 = analogRead(A1);
            Serial.println("S7 CALIBRATED");

        } else if (receivedData == "shifter_8") {
            data[7].value1 = analogRead(A0);
            data[7].value2 = analogRead(A1);
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
  delay(1000);

  for (int i = 0; i < 8; i++) {
    if (isWithinRange(data[i], rangeOffset, potValue1, potValue2)) {
      Serial.print("Shifter ");
      Serial.print(i + 1);
      Serial.println(" is within the range.");
      Joystick.button(i + 1, true);
  } else {
      Joystick.button(i,false);
      continue;
  }

  }
  Serial.println(data[8].value1);
  delay(1000);
}

