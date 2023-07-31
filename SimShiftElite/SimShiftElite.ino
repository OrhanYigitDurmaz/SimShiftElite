
//  STILL WORK IN PROGRESS! USE IT ON YOUR OWN!!! Also use arduino-pico core from earlphilhowerr

//TODO:
// 1: Clean up messy code and add a better logic
// 2: Add Smoothed library for adc readings -- not needed, because we are adding rangeOffset
// 3: Add the main logic

#include <Arduino.h>
#include <EEPROM.h>
#include <Joystick.h>
#include "readSerial.h"
#include "EEPROMFunctions.h"

struct adcValues {
  int value1;
  int value2;
};

adcValues data[8] = {
  {4094, 4095},
  {2304, 2305},
  {1111, 2222},
  {3333, 4444},
  {5555, 6666},
  {7777, 8888},
  {9999, 1010},
  {1212, 1313}
};

void setup() {
  analogReadResolution(12);
  startEEPROM();
  Joystick.begin();
  Serial.begin(115200);
  
}

void loop() {
  readSerial();

  writeToEEPROM(data, sizeof(data) / sizeof(data[0]));

  // Reading data from EEPROM
  adcValues readData[8];
  readFromEEPROM(readData, sizeof(readData) / sizeof(readData[0]));

}