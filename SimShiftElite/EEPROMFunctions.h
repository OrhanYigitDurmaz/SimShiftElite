#ifndef EEPROMFUNCTIONS_H
#define EEPROMFUNCTIONS_H

#include <Arduino.h>
#include <EEPROM.h>

void startEEPROM();
void stopEEPROM();
void saveToEEPROM();
void clearEEPROM();
void loadFromEEPROM();


#endif