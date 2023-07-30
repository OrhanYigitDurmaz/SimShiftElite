
//  STILL WORK IN PROGRESS! USE IT ON YOUR OWN!!! Also use arduino-pico core from earlphilhowerr

//TODO:
// 1: Clean up messy code and add a better logic
// 2: Add Smoothed library for adc readings
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

void setup() {
  analogReadResolution(12);
  startEEPROM();
  Joystick.begin();
  Serial.begin(115200);
  
}

void loop() {
  Serial.println(analogRead(A0));
  Serial.println(analogRead(A1));
  readSerial();
}