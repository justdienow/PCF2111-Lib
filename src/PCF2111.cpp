/**
 * \file PCF2111.cpp
 * \brief Implementation of a class for dealing with the PCF2111 LCD driver IC.
 * \author Justdienow
 * \copyright BSD license, check the License page on the blog for more information. All this text must be
 *  included in any redistribution.
 */

#include "PCF2111.h"

PCF2111::PCF2111(byte DLENpin, byte CLBpin, byte DATApin) {
  for (byte i = 0; i < LCD_BACKPLANE; i++) {
    for (byte j = 0; j < DATA_COUNT; j++) {
      _displayData[i][j] = 0;
    }
  }
  
  _DLENpin = DLENpin;
  _CLBpin = CLBpin;
  _DATApin = DATApin;

  pinMode(_DLENpin, OUTPUT);
  pinMode(_CLBpin, OUTPUT);
  pinMode(_DATApin, OUTPUT);

  digitalWrite(_DLENpin, LOW);
  digitalWrite(_CLBpin, LOW);
  digitalWrite(_DATApin, LOW);
}

void PCF2111::shiftBit(byte value) {
  digitalWrite(_CLBpin, HIGH);
  digitalWrite(_DATApin, value);
  digitalWrite(_CLBpin, LOW);
}

void PCF2111::shiftByte(byte value) {
  byte tmp = value;
  for(byte c=0; c<8; c++) {
    shiftBit(tmp & 1);
    tmp = tmp >> 1;
  }
}

byte PCF2111::writeDisplay(byte digit, byte value) {
  byte status = -1; // This is used to denote that either digit or value is out of bounds.

  // Check to see if values passed are within the bounds of our arrays.
  if((digit >= 0 && digit <= 7) && (value >= 0 && value <= 15)) {
    status = 0;

    // Grab the digit index so we can use it as the offset.
    byte digitIndex = LCDdigit[digit][0];

    if(LCDdigit[digit][1] == 0) {  // LCD DIGIT N lo Byte
      _displayData[0][digitIndex] = (_displayData[0][digitIndex] & 0xF0) | numberMapLowByte[value][0];
      _displayData[1][digitIndex] = (_displayData[1][digitIndex] & 0xF0) | numberMapLowByte[value][1];
    } else {                       // LCD DIGIT N hi Byte
      _displayData[0][digitIndex] = (_displayData[0][digitIndex] & 0x0F) | numberMapHighByte[value][0];
      _displayData[1][digitIndex] = (_displayData[1][digitIndex] & 0x0F) | numberMapHighByte[value][1];
    }

    // Outer is to iterate over backplanes 
    for (byte i = 0; i < LCD_BACKPLANE; i++) {
      digitalWrite(_DLENpin, HIGH);   // Enable the data input line so we can start writing to the chip.
      shiftBit(0);                    // Write a leading zero.
      // Inner is to iterate over data for each backplane
      for (byte j = 0; j < DATA_COUNT; j++) {
        shiftByte(_displayData[i][j]); // Write data to the chip shift register.
      }
      shiftBit(i);                    // Write the load bit for given backplane.
      digitalWrite(_DLENpin, LOW);    // Disable the data input line.
      shiftBit(0);                    // Write a trialing zero as the loading pulse to latch the data from the shift register.
    }
  }
  
  return status;
}

byte** PCF2111::getDisplayData() {
  byte** copyData = new byte*[LCD_BACKPLANE];
  for (byte i = 0; i < LCD_BACKPLANE; i++) {
    copyData[i] = new byte[DATA_COUNT];
    for (byte j = 0; j < DATA_COUNT; j++) {
      copyData[i][j] = _displayData[i][j];
    }
  }
  return copyData;
}