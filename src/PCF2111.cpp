/**
 * \file PCF2111.cpp
 * \brief Implementation of a class for dealing with the PCF2111 LCD driver IC.
 * \author Justdienow
 * \copyright TODO
 */

#include "PCF2111.h"

PCF2111::PCF2111(byte DLENpin, byte CLBpin, byte DATApin) {
    for (byte i = 0; i < LCD_BACKPLANE; i++) {
        for (byte j = 0; j < DATA_COUNT; j++) {
            _displayData[i][j] = 255;
        }
    }
    
    _activeBP = 0;
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

void PCF2111::updateDisplay(byte bp) {
    // _activeBP ^= 0x01;

    _activeBP = bp;

    digitalWrite(_DLENpin, HIGH);
    shiftBit(0);                  // leading zero

    for(byte i = 0; i < DATA_COUNT; i++) {
        shiftByte(_displayData[_activeBP][i]);
        Serial.print("In updateDisplay() LOOP - DD :: ");
        Serial.println(_displayData[_activeBP][i]);
    }

    shiftBit(_activeBP);           // load bit

    // for (byte i = 0; i < LCD_BACKPLANE; i++) {
    //     for (byte j = 0; j < DATA_COUNT; j++) {
    //         // _displayData[i][j] = 254;
    //         shiftByte(_displayData[i][j]);
    //         Serial.print("In updateDisplay() LOOP - DD :: ");
    //         Serial.println(_displayData[i][j]);
    //     }
    //     shiftBit(i); 
    // }

    digitalWrite(_DLENpin, LOW);
    shiftBit(0);                  // load pulse
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