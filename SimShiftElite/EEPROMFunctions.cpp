#include <Arduino.h>
#include <EEPROM.h>

int address = 0;

void startEEPROM() {
  EEPROM.begin(512);
}

void stopEEPROM() {
  EEPROM.end(); 
}

void saveToEEPROM() {
  EEPROM.commit();
}

void clearEEPROM() {
  int EEPROMSize = EEPROM.length();

  for (int i = 0; i < EEPROMSize; i++) {
    EEPROM.write(i, 0);
  }
}


void loadFromEEPROM() {

  //EEPROM.get falan

}