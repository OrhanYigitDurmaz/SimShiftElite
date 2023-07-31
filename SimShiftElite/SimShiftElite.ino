
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

adcValues data[8] = {
  {10, 11}, // Initialize with 0, but you can set your own calibration values
  {100, 110},
  {1000, 1100},
  {2000, 2100},
  {0, 0},
  {0, 0},
  {0, 0},
  {0, 0}
};

void setup() {
  analogReadResolution(12);
  startEEPROMfunc();
  Joystick.begin();
  Serial.begin(115200);
  
}

void loop() {
  readSerial();
  println()
}