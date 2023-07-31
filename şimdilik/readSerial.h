#ifndef READSERIAL_H
#define READSERIAL_H

#include <Arduino.h>
#include <EEPROM.h>

struct adcValues {
  int value1;
  int value2;
};

// Declare the adcValues array as external
extern adcValues data[8];
extern int rangeOffset;

void calibrateShifter(int shifterIndex);
void readSerial();
void handleRangeOffset(const String& receivedData);

#endif // READSERIAL_H