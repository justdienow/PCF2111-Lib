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

  byte writeDisplay(byte digit, byte value);

  byte** getDisplayData();
private:
  byte _displayData[LCD_BACKPLANE][DATA_COUNT];
  byte _DLENpin;
  byte _CLBpin;
  byte _DATApin;

  /*
  * 8 LCD Digits positions - For "Watt Hour Display"
  * From 0 to 7 inclusively - left to right
  */ 
  byte LCDdigit [8][2] = {
    {0, 0}, // LCD DIGIT 0 lo Byte - OFFSET 0  to 3
    {3, 1}, // LCD DIGIT 1 hi Byte - OFFSET 28 to 31
    {0, 1}, // LCD DIGIT 2 hi Byte - OFFSET 4  to 7
    {3, 0}, // LCD DIGIT 3 lo Byte - OFFSET 24 to 27
    {1, 0}, // LCD DIGIT 4 lo Byte - OFFSET 8  to 11
    {2, 1}, // LCD DIGIT 5 hi Byte - OFFSET 20 to 23
    {1, 1}, // LCD DIGIT 6 hi Byte - OFFSET 12 to 15
    {2, 0}  // LCD DIGIT 7 lo Byte - OFFSET 16 to 19
  };

  /*
  * Upper byte for mapping LCD glyphs 0 to 15('F')
  * bits = 0000****b (16 to 240)
  */
  byte numberMapHighByte [16][2] = {
    {0xD0, 0x70}, // 0
    {0x80, 0x20}, // 1
    {0xF0, 0x10}, // 2
    {0xE0, 0x30}, // 3
    {0xA0, 0x60}, // 4
    {0x60, 0x70}, // 5
    {0x70, 0x70}, // 6
    {0xC0, 0x20}, // 7
    {0xF0, 0x70}, // 8
    {0xE0, 0x70}, // 9
    {0xF0, 0x60}, // A 10
    {0x30, 0x70}, // b 11
    {0x50, 0x50}, // C 12
    {0xB0, 0x30}, // d 13
    {0x70, 0x50}, // E 14
    {0x70, 0x40}  // F 15
  };

  /*
  * Lower byte for mapping LCD glyphs 0 to 15('F')
  * bits = ****0000b (0 to 15)
  */
  byte numberMapLowByte [16][2] = {
    {0x0D, 0x07}, // 0
    {0x08, 0x02}, // 1
    {0x0F, 0x01}, // 2
    {0x0E, 0x03}, // 3
    {0x0A, 0x06}, // 4
    {0x06, 0x07}, // 5
    {0x07, 0x07}, // 6
    {0x0C, 0x02}, // 7
    {0x0F, 0x07}, // 8
    {0x0E, 0x07}, // 9
    {0x0F, 0x06}, // A 10
    {0x03, 0x07}, // b 11
    {0x05, 0x05}, // C 12
    {0x0B, 0x03}, // d 13
    {0x07, 0x05}, // E 14
    {0x07, 0x04}  // F 15
  };
};

#endif