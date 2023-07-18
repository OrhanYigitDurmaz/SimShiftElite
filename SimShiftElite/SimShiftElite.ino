
//  STILL WORK IN PROGRESS! USE IT ON YOUR OWN!!! Also use arduino-pico core from earlphilhowerr

//TODO:
// 1: Clean up messy code and add a better logic
// 2: Write the API docs for the serial commands
// 3: Make the GUI (if someone wants to help, im here: orhanyigitv2durmaz [at] gmail [dot] com ,  github.com/OrhanYigitDurmaz/SimShiftElite-GUI) )
// 4: 

#include <Arduino.h>
#include <EEPROM.h>
#include <Joystick.h>

const int adcPin1 = 26; // ADC pin 1
const int adcPin2 = 27; // ADC pin 2
const int gearHigh = 2; // Digital input pin number

// Create a joystick object
Joystick_ Joystick;

// Define the button ranges
const int numButtons = 8;
int buttonRanges[numButtons][2];

// Define EEPROM addresses for storing button ranges and range offset
const int EEPROMAddress = 0;
const int EEPROMRangeOffsetAddress = EEPROMAddress + sizeof(buttonRanges);

// Define default button ranges
const int defaultButtonRanges[numButtons][2] = {
  {100, 100},   // Button 1
  {100, 200},   // Button 2       The logic works like this: if a input pins is high(hence the name, if a physical button is pressed), 
  {100, 300},   // Button 3       the program adds +8 to every button number. So if you are in gear 1 while not pressing the button,
  {100, 400},   // Button 4       when you press that button you would be in gear 9
  {800, 100},   // Button 5       TODO: THIS IS NOT GOOD. We shouldve been using the MaxButton attribute for this. this way it will be dynamic.  
  {800, 200},   // Button 6
  {800, 300},   // Button 7
  {800, 400},   // Button 8
};

int maxButtonAllowed = numButtons; // Maximum button allowed, default to all buttons
int rangeOffset = 50; // Range offset, default to 50

void setup() {
  Serial.begin(9600);
  analogReadResolution(12); // Set ADC resolution to 12 bits

  // Initialize the joystick library
  Joystick.begin();

  // Wait for serial connection
  while (!Serial) {
    delay(10);
  }

  // Check if button ranges are stored in EEPROM
  bool loadFromEEPROM = false;
  if (EEPROM.read(EEPROMAddress) == 'R' && EEPROM.read(EEPROMAddress + 1) == 'A' &&
      EEPROM.read(EEPROMAddress + 2) == 'N' && EEPROM.read(EEPROMAddress + 3) == 'G') {
    // Read button ranges from EEPROM
    for (int i = 0; i < numButtons; i++) {
      int eepromAddr = EEPROMAddress + 4 + i * 4;
      for (int j = 0; j < 2; j++) {
        byte highByte = EEPROM.read(eepromAddr + j * 2);
        byte lowByte = EEPROM.read(eepromAddr + j * 2 + 1);
        buttonRanges[i][j] = (highByte << 8) | lowByte;
      }
    }
    rangeOffset = EEPROM.read(EEPROMRangeOffsetAddress);
    loadFromEEPROM = true;
  }

  // If button ranges were not loaded from EEPROM, use default ranges
  if (!loadFromEEPROM) {
    memcpy(buttonRanges, defaultButtonRanges, sizeof(buttonRanges));
  }

  // Validate button ranges
  for (int i = 0; i < numButtons; i++) {
    if (buttonRanges[i][0] < 0 || buttonRanges[i][0] >= 4096 ||
        buttonRanges[i][1] < 0 || buttonRanges[i][1] >= 4096) {
      Serial.println("CALIBRATION_FAILED");
      memcpy(buttonRanges, defaultButtonRanges, sizeof(buttonRanges));
      break;
    }
  }

  // Store button ranges and range offset in EEPROM if not loaded from EEPROM
  if (!loadFromEEPROM) {
    EEPROM.write(EEPROMAddress, 'R');
    EEPROM.write(EEPROMAddress + 1, 'A');
    EEPROM.write(EEPROMAddress + 2, 'N');
    EEPROM.write(EEPROMAddress + 3, 'G');
    for (int i = 0; i < numButtons; i++) {
      int eepromAddr = EEPROMAddress + 4 + i * 4;
      for (int j = 0; j < 2; j++) {
        byte highByte = buttonRanges[i][j] >> 8;
        byte lowByte = buttonRanges[i][j] & 0xFF;
        EEPROM.write(eepromAddr + j * 2, highByte);
        EEPROM.write(eepromAddr + j * 2 + 1, lowByte);
      }
    }
    EEPROM.write(EEPROMRangeOffsetAddress, rangeOffset);
  }

  // Print configured button ranges
  Serial.println("Configured Button Ranges:");
  for (int i = 0; i < numButtons; i++) {
    Serial.print("Button ");
    Serial.print(i + 1);
    Serial.print(": X: ");
    Serial.print(buttonRanges[i][0]);
    Serial.print(", Y: ");
    Serial.println(buttonRanges[i][1]);
  }

  // If loaded from EEPROM, print the loaded button ranges and range offset
  if (loadFromEEPROM) {
    Serial.println("Loaded Button Ranges:");
    for (int i = 0; i < numButtons; i++) {
      Serial.print("Button ");
      Serial.print(i + 1);
      Serial.print(": X: ");
      Serial.print(buttonRanges[i][0]);
      Serial.print(", Y: ");
      Serial.println(buttonRanges[i][1]);
    }
    Serial.print("Range Offset: ");
    Serial.println(rangeOffset);
  }

  // Check if max button allowed or range offset is set via serial
  if (Serial.available() > 0) {
    String input = Serial.readStringUntil('\n');
    if (input.startsWith("MAXBUTTON")) {
      int maxButton = input.substring(10).toInt();
      if (maxButton >= 1 && maxButton <= numButtons) {
        maxButtonAllowed = maxButton;
        Serial.print("Max Button Allowed: ");
        Serial.println(maxButtonAllowed);
      } else {
        Serial.println("Invalid Max Button Allowed value");
      }
    } else if (input.startsWith("RANGE_OFFSET")) {
      int offset = input.substring(12).toInt();
      if (offset >= 0 && offset <= 500) {
        rangeOffset = offset;
        Serial.print("Range Offset: ");
        Serial.println(rangeOffset);
      } else {
        Serial.println("Invalid Range Offset value");
      }
    }
  }
}

void loop() {
  int value1 = analogRead(adcPin1);
  int value2 = analogRead(adcPin2);

  Serial.print("ADC 1: ");
  Serial.print(value1);
  Serial.print("\tADC 2: ");
  Serial.println(value2);

  // Check button ranges
  for (int i = 0; i < maxButtonAllowed; i++) {
    int adc1Min = buttonRanges[i][0] - rangeOffset;
    int adc1Max = buttonRanges[i][0] + rangeOffset;
    int adc2Min = buttonRanges[i][1] - rangeOffset;
    int adc2Max = buttonRanges[i][1] + rangeOffset;

    if (value1 > adc1Min && value1 < adc1Max && value2 > adc2Min && value2 < adc2Max) {
      // Simulate button press
      int buttonNum = i + 1;
      if (digitalRead(gearHigh) == HIGH) {
        buttonNum += 8;
      }
      Joystick.pressButton(buttonNum);
    } else {
      // Release button
      Joystick.releaseButton(i + 1);
    }
  }

  // Send joystick data
  Joystick.sendState();

  delay(100); // Adjust delay as needed
}
