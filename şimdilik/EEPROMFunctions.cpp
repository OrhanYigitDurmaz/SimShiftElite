#include <Arduino.h>
#include <EEPROM.h>
#include "readSerial.h"

int address = 0;


void startEEPROMfunc() {
  EEPROM.begin(512);
}

void stopEEPROMfunc() {
  EEPROM.end(); 
}

void saveToEEPROMfunc() {
  EEPROM.commit();
}

void clearEEPROMfunc() {
  int EEPROMSize = EEPROM.length();
  for (int i = 0; i < EEPROMSize; i++) {
    EEPROM.write(i, 0);
  }
}


void writeToEEPROM(const adcValues data[], size_t numElements) {
  size_t address = 0;
  for (size_t i = 0; i < numElements; ++i) {
    EEPROM.put(address, data[i].value1);
    address += sizeof(int);
    EEPROM.put(address, data[i].value2);
    address += sizeof(int);
  }
}

void readFromEEPROM(adcValues data[], size_t numElements) {
  size_t address = 0;
  for (size_t i = 0; i < numElements; ++i) {
    EEPROM.get(address, data[i].value1);
    address += sizeof(int);
    EEPROM.get(address, data[i].value2);
    address += sizeof(int);
  }
}