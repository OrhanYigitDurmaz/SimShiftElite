#ifndef tl
#define tl

#if (ARDUINO >=100)
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

class ReadSerial  {
  public:
    ReadSerial();

    void readSerial();

  private:
};
#endif