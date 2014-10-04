#define F_CPU 800000UL

#include <stdio.h>
#include <avr/io.h>
#include <avr/pgmspace.h>
#include <util/delay.h>  // Хотим использовать функции задержек

#include "lcd/lcd.hpp"


const uint8_t BATTERY_75[] PROGMEM= {
    0b00001110,
    0b00011011,
    0b00010001,
    0b00011111,
    0b00011111,
    0b00011111,
    0b00011111,
    0b00011111
};


const uint8_t BATTERY_75_ID = 0x03;
const uint8_t TEST_STR[] PROGMEM ="avislab.com/blog\0";
const uint32_t SLEEP_TIME = 2000;

int main() {
    uint8_t buffer[16];
    int i = 1;
    Lcd lcd;

    lcd.defineChar(BATTERY_75, BATTERY_75_ID);
    lcd.cursorOff();
    lcd.clr();
    lcd.gotoXY(15, 0);
    lcd.sendChar(BATTERY_75_ID);
    lcd.gotoXY(0, 0);
    lcd.cursorRight(1);
    lcd.sendChar('S');

    sprintf((char*)buffer, "ample #%d", i);

    lcd.string(buffer, 8);
    lcd.copyStringToLcd(TEST_STR, 0, 1);

    DDRB = 0b00000001;
    PORTB ^= _BV(PB0);
    _delay_ms(SLEEP_TIME << 1);
    PORTB ^= _BV(PB0);

    while(1)
    {}
}
