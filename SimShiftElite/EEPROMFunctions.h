#ifndef EEPROMFUNCTIONS_H
#define EEPROMFUNCTIONS_H

#include <Arduino.h>
#include <EEPROM.h>
#include "readSerial.h"

void startEEPROMfunc();
void stopEEPROMfunc();
void saveToEEPROMfunc();
void clearEEPROMfunc();
void writeToEEPROM(const adcValues data[], size_t numElements);
void readFromEEPROM(adcValues data[], size_t numElements);

#endif // EEPROMFUNCTIONS_H