#pragma once

#include <inttypes.h>

#define LCD_RS   PB4
#define LCD_E    PB2
#define LCD_DATA PORTA

#define RS_ENABLE  PORTB |=  _BV(LCD_RS) // установить "1"
#define RS_DISABLE PORTB &= ~_BV(LCD_RS) // установить "0"

#define E_ENABLE  PORTB |=  _BV(LCD_E);
#define E_DISABLE PORTB &= ~_BV(LCD_E);


class Lcd {
    void writeNibble(int data);
    void writeData(int data);

public:
    Lcd();

    void setCursor(int line, int pos);
    void writeString(const char *str);
    void writeCmd(int cmd);
};
