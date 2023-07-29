
//  STILL WORK IN PROGRESS! USE IT ON YOUR OWN!!! Also use arduino-pico core from earlphilhowerr

//TODO:
// 1: Clean up messy code and add a better logic
// 2: Write the API docs for the serial commands
// 3: Make the GUI (if someone wants to help, im here: orhanyigitv2durmaz [at] gmail [dot] com ,  github.com/OrhanYigitDurmaz/SimShiftElite-GUI) )
// 4: Add Smoothed library for adc readings

#include <Arduino.h>
#include <EEPROM.h>
#include <Joystick.h>
#include "readSerial.h"

void setup() {
  Serial.begin(9600);
  analogReadResolution(12); // Set ADC resolution to 12 bits
}

void loop() {
  ReadSerial.loop
}