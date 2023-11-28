#ifndef __LCD__
#define __LCD__

#include <LiquidCrystal_I2C.h>
#include <Wire.h>

class LCD {
public:
  /**
     * @brief Construct a new LCD object.
     * 
     * @param column the column of the LCD display
     * @param row number of row
     */
  LCD(int address, int columns, int rows);
  void write(const char* string, int start_col, int start_rows);
protected:
  LiquidCrystal_I2C lcd;
};

#endif