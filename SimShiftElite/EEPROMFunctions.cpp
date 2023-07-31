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

void readDataFromEEPROM() {
  MyData retrievedData1;
  MyData retrievedData2;

  // Read data from address 0
  EEPROM.get(0, retrievedData1);

  // Read data from address 1
  EEPROM.get(sizeof(MyData), retrievedData2);