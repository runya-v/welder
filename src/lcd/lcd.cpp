#include <inttypes.h>
#include <avr/io.h>
#include <avr/pgmspace.h>
#include <util/delay.h>

#include "lcd.hpp"


Lcd::Lcd() {
    _delay_ms(1);
    LDP &= ~(1 << LCD_D7 | 1 << LCD_D6 | 1 << LCD_D5 | 1 << LCD_D4);
    //LCP &= ~(1 << LCD_E | 1 << LCD_RW | 1 << LCD_RS);
    LCP &= ~(1 << LCD_E | 1 << LCD_RS);
    LDDR |= 1 << LCD_D7 | 1 << LCD_D6 | 1 << LCD_D5 | 1 << LCD_D4;
    //LCDR |= 1 << LCD_E | 1 << LCD_RW | 1 << LCD_RS;
    LCDR |= 1 << LCD_E | 1 << LCD_RS;

    //---------one------
    //4 bit mode
    LDP |= (1 << LCD_D5 | 1 << LCD_D4);
    LDP &= ~(1 << LCD_D7 | 1 << LCD_D6);
    LCP |= (1 << LCD_E);
    _delay_ms(1);
    LCP &= ~(1 << LCD_E);
    _delay_ms(1);

    //-----------two-----------
    LDP |= (1 << LCD_D5 | 1 << LCD_D4);
    LDP &= ~(1 << LCD_D7 | 1 << LCD_D6);
    LCP|= (1 << LCD_E);
    _delay_ms(1);
    LCP &= ~(1 << LCD_E);
    _delay_ms(1);

    //-------three-------------
    LDP |= (1 << LCD_D5);
    LDP &= ~(1 << LCD_D7 | 1 << LCD_D6 | 1 << LCD_D4);
    LCP|= (1 << LCD_E);
    _delay_ms(1);
    LCP &= ~(1 << LCD_E);
    _delay_ms(1);

    //--------4 bit--dual line---------------
    sendCommand(0b00101000);

    //-----increment address, cursor shift------
    sendCommand(0b00001110);
}


void Lcd::sendChar(uint8_t ch) {
    LDP &= ~((0b11110000) >> (4 - LCD_D4));
    LDP |= ((ch&0b11110000) >> (4 - LCD_D4));

    LCP |= 1 << LCD_RS;
    LCP |= 1 << LCD_E;
    _delay_ms(1);
    LCP &= ~(1 << LCD_E);
    LCP &= ~(1 << LCD_RS);
    _delay_ms(1);

    LDP &= ~((0b11110000) >> (4 - LCD_D4));
    LDP |= ((ch & 0b00001111) << (LCD_D4));

    LCP |= 1 << LCD_RS;
    LCP |= 1 << LCD_E;
    _delay_ms(1);
    LCP &= ~(1 << LCD_E);
    LCP &= ~(1 << LCD_RS);
    _delay_ms(1);
}


void Lcd::sendCommand(uint8_t cmd) {
    LDP &= ~((0b11110000) >> (4 - LCD_D4));
    LDP |= ((cmd&0b11110000) >> (4 - LCD_D4));

    LCP |= 1 << LCD_E;
    _delay_ms(1);
    LCP &= ~(1 << LCD_E);
    _delay_ms(1);

    LDP &= ~((0b11110000) >> (4 - LCD_D4));
    LDP |= ((cmd&0b00001111) << (LCD_D4));

    LCP |= 1 << LCD_E;
    _delay_ms(1);
    LCP &= ~(1 << LCD_E);
    _delay_ms(1);
}


void Lcd::clr() {
    sendCommand(1 << LCD_CLR);
}


void Lcd::home() {
    sendCommand(1 << LCD_HOME);
}


void Lcd::string(uint8_t *data, uint8_t num_bytes) {
    register uint8_t i;

    // check to make sure we have a good pointer
    if (data) {
        // print data
        for(i = 0; i < num_bytes; ++i) {
            sendChar(data[i]);
        }
    }
}


void Lcd::gotoXY(uint8_t x, uint8_t y) {
    register uint8_t dgram_addr;

    // remap lines into proper order
    switch(y) {
        case 0:  dgram_addr = LCD_LINE0_DDRAMADDR + x; break;
        case 1:  dgram_addr = LCD_LINE1_DDRAMADDR + x; break;
        case 2:  dgram_addr = LCD_LINE2_DDRAMADDR + x; break;
        case 3:  dgram_addr = LCD_LINE3_DDRAMADDR + x; break;
        default: dgram_addr = LCD_LINE0_DDRAMADDR + x;
    }
    // set data address
    sendCommand(1 << LCD_DDRAM | dgram_addr);
}


//Copies string from flash memory to Lcd:: at x y position
//const uint8_t welcomeln1[] PROGMEM="AVR Lcd:: DEMO\0";
//CopyStringtoLCD(welcomeln1, 3, 1);
void Lcd::copyStringToLcd(const uint8_t *flash_loc, uint8_t x, uint8_t y) {
    uint8_t i;
    gotoXY(x,y);

    for (i = 0; (uint8_t)pgm_read_byte(&flash_loc[i]); ++i) {
        sendChar((uint8_t)pgm_read_byte(&flash_loc[i]));
    }
}

//defines char symbol in CGRAM
//const uint8_t backslash[] PROGMEM = {
//0b00000000,//back slash
//0b00010000,
//0b00001000,
//0b00000100,
//0b00000010,
//0b00000001,
//0b00000000,
//0b00000000
//};
//
//LCDdefinechar(backslash,0);


void Lcd::defineChar(const uint8_t *pc, uint8_t char_code) {
    uint8_t a;
    uint8_t pcc;
    uint16_t i;

    a = (char_code << 3) | 0x40;

    for (i = 0; i < 8; ++i) {
        pcc = pgm_read_byte(&pc[i]);
        sendCommand(++a);
        sendChar(pcc);
    }
}


void Lcd::shiftLeft(uint8_t n) {
    uint8_t i;

    for (i = 0; i < n; ++i) {
        sendCommand(0x1E);
    }
}


void Lcd::shiftRight(uint8_t n) {
    uint8_t i;

    for (i = 0; i < n; ++i) {
        sendCommand(0x18);
    }
}


void Lcd::cursorOn() {
    sendCommand(0x0E);
}


void Lcd::cursorOnBlink() {
    sendCommand(0x0F);
}


void Lcd::cursorOff() {
    sendCommand(0x0C);
}


void Lcd::blank() {
    sendCommand(0x08);
}


void Lcd::visible() {
    sendCommand(0x0C);
}


void Lcd::cursorLeft(uint8_t n) {
    uint8_t i;

    for (i = 0; i < n; ++i) {
        sendCommand(0x10);
    }
}


void Lcd::cursorRight(uint8_t n) {
    uint8_t i;

    for (i = 0; i < n; ++i) {
        sendCommand(0x14);
    }
}
