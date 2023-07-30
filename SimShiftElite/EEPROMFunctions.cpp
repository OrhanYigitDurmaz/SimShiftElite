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

void writeTheValuesToEEPROM(const String& inputString) {

  if inputString == "shifter_1";
    writeStringToEEPROM();
  if else inputString == "shifter_2";
    writeStringToEEPROM
    

  

}

void writeStringToEEPROM(int addrOffset, const String &strToWrite) {
  byte len = strToWrite.length();
  //  Serial.println(len);
  EEPROM.write(addrOffset, len);
  for (int i = 0; i < len; i++)
  {
    EEPROM.write(addrOffset + 1 + i, strToWrite[i]);
  }
}