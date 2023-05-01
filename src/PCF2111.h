/**
 * \file PCF2111.h
 * \brief Implementation of a class for dealing with the PCF2111 LCD driver IC.
 * \author Justdienow
 * \copyright BSD license, check the License page on the blog for more information. All this text must be
 *  included in any redistribution.
 */

#ifndef _PCF2111_h
#define _PCF2111_h

#if ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

#define DATA_COUNT 4
#define LCD_BACKPLANE 2

class PCF2111 {
private:
    byte displayData[LCD_BACKPLANE][DATA_COUNT];
    byte activeBP;
    uint8_t _DLEN_pin;
    uint8_t _CLB_pin;
    uint8_t _DATA_pin;
public:
    /**
     * \brief Constructor. Use begin() to complete the initialization of the chip.
     * @param \c DLENpin Data input line enable (CBUS) pin.
     * @param \c CLBpin Clock burst input (CBUS) pin.
     * @param \c DATApin Data input line (CBUS) pin for writing data.
     */
    PCF2111(uint8_t DLENpin, uint8_t CLBpin, uint8_t DATApin) : _DLEN_pin(DLENpin), _CLB_pin(CLBpin), _DATA_pin(DATApin) {};

    /**
     *  \brief Init the PCF2111. It inits the control bus.
     */
    void begin();

    void shiftBit(byte value);

    void shiftByte(byte value);

    void updateDisplay();
};

#endif
