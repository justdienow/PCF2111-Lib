/**
 * \file PCF2111.cpp
 * \brief Implementation of a class for dealing with the PCF2111 LCD driver IC.
 * \author Justdienow
 * \copyright BSD license, check the License page on the blog for more information. All this text must be
 *  included in any redistribution.
 */

#include "PCF2111.h"

void PCF2111::begin() {
    pinMode(_DLEN_pin, OUTPUT);
    pinMode(_CLB_pin, OUTPUT);
    pinMode(_DATA_pin, OUTPUT);

    digitalWrite(_DLEN_pin, LOW);
    digitalWrite(_CLB_pin, LOW);
    digitalWrite(_DATA_pin, LOW);

    activeBP = 0
}

void PCF2111::shiftBit(byte value) {
    digitalWrite(_CLB_pin, HIGH);
    digitalWrite(_DATA_pin, value);
    digitalWrite(_CLB_pin, LOW);
}

void PCF2111::shiftByte(byte value) {
    byte tmp = value;
    for(byte c=0; c<8; c++) {
        shiftBit(tmp & 1);
        tmp = tmp >> 1;
    }
}

void PCF2111::updateDisplay() {
    activeBP ^= 0x01;
    digitalWrite(_DLEN_pin, HIGH);
    shiftBit(0);                  // leading zero

    for(byte c=0; c < DATA_COUNT; c++) {
        shiftByte(displayData[activeBP][c]);
    }

    shiftBit(activeBP);           // load bit
    digitalWrite(_DLEN_pin, LOW);
    shiftBit(0);                  // load pulse
}