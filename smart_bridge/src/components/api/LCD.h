#ifndef __LCD__
#define __LCD__

#include <LiquidCrystal_I2C.h>
#include <Wire.h>

class LCD {
public:
  /**
     * @brief Construct a new LCD object.
     * 
     * @param columns the column of the LCD display
     * @param rows number of row
     */
  LCD(int address, int columns, int rows);
  void write(const char* string, int start_col, int start_rows);
  void clear();
protected:
  LiquidCrystal_I2C lcd;
};

#endif