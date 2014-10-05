#include <inttypes.h>
#include <avr/io.h>
#include <avr/pgmspace.h>
#include <util/delay.h>

#include "lcd.hpp"


void Lcd::writeNibble(int data) {
    LCD_DATA |= data;
    E_ENABLE;
    _delay_ms(20);
    E_DISABLE;
    LCD_DATA &= ~(data);
}


void Lcd::writeData(int data) {
    writeNibble(data & 0xF0);  // старшый полубайт
    writeNibble(data << 4);    //младший полубайт
}
////////////////////////////////////////////////////////////////////////////////////////////////////


Lcd::Lcd() {
    DDRB = 0xFF;
    PORTB = 0x00;

    DDRA = 0xFF;
    LCD_DATA = 0x00;

    RS_DISABLE;
    _delay_ms(200);

    writeNibble(0x30);
    _delay_ms(50);

    writeNibble(0x30);
    _delay_ms(50);

    writeNibble(0x28);
    _delay_ms(20);

    writeData(0x08);   // полное выключение дисплея
    _delay_ms(20);

    writeData(0x01);   // очистка дисплея
    _delay_ms(20);

    writeData(0x06);   // сдвиг курсора вправо
    _delay_ms(20);

    writeData(0x0C);   // включение дисплея
    _delay_ms(20);

    RS_ENABLE;
}
////////////////////////////////////////////////////////////////////////////////////////////////////


void Lcd::setCursor(int line, int pos) {
    pos |= 0b10000000;

    if (line == 1) {
        pos += 0x40;
    }
    writeCmd(pos);
}


void Lcd::writeString(const char *str) {
    do {
        writeData(*str);
    }
    while(*++str);
}


void Lcd::writeCmd(int cmd) {
    RS_DISABLE;
    writeData(cmd);
    RS_ENABLE;
}
