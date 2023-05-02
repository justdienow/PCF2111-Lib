/**
 * \file PCF2111.h
 * \brief Implementation of a class for dealing with the PCF2111 LCD driver IC.
 * \author Justdienow
 * \copyright BSD license, check the License page on the blog for more information. All this text must be
 *  included in any redistribution.
 */

#ifndef PCF2111_H_
#define PCF2111_H_

//Arduino toolchain header, version dependent
#if defined(ARDUINO) && ARDUINO >= 100
	#include "Arduino.h"
#else
	#include "WProgram.h"
#endif

#define DATA_COUNT 4
#define LCD_BACKPLANE 2

class PCF2111 {
public:
    /**
     * \brief Constructor. Use begin() to complete the initialization of the chip.
     * @param \c DLENpin Data input line enable (CBUS) pin.
     * @param \c CLBpin Clock burst input (CBUS) pin.
     * @param \c DATApin Data input line (CBUS) pin for writing data.
     */
    PCF2111(byte DLENpin, byte CLBpin, byte DATApin);

    void shiftBit(byte value);

    void shiftByte(byte value);

    void updateDisplay(byte bp);

    byte** getDisplayData();
private:
    byte _displayData[LCD_BACKPLANE][DATA_COUNT];
    byte _activeBP;
    byte _DLENpin;
    byte _CLBpin;
    byte _DATApin;
};

#endif
