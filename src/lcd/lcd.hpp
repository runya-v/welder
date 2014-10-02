#pragma once

#include <inttypes.h>

#define LCD_RS  1     //define MCU pin connected to LCD RS
#define LCD_RW  0     //define MCU pin connected to LCD R/W
#define LCD_E   2     //define MCU pin connected to LCD E
#define LCD_D4  4     //define MCU pin connected to LCD D3
#define LCD_D5  5     //define MCU pin connected to LCD D4
#define LCD_D6  6     //define MCU pin connected to LCD D5
#define LCD_D7  7     //define MCU pin connected to LCD D6
#define LDP     PORTD //define MCU port connected to LCD data pins
#define LCP     PORTB //define MCU port connected to LCD control pins
#define LDDR    DDRD  //define MCU direction register for port connected to LCD data pins
#define LCDR    DDRB  //define MCU direction register for port connected to LCD control pins

#define LCD_CLR             0 //DB0: clear display
#define LCD_HOME            1 //DB1: return to home position
#define LCD_ENTRY_MODE      2 //DB2: set entry mode
#define LCD_ENTRY_INC       1 //DB1: increment
#define LCD_ENTRY_SHIFT     0 //DB2: shift
#define LCD_ON_CTRL         3 //DB3: turn lcd/cursor on
#define LCD_ON_DISPLAY      2 //DB2: turn display on
#define LCD_ON_CURSOR       1 //DB1: turn cursor on
#define LCD_ON_BLINK        0 //DB0: blinking cursor
#define LCD_MOVE            4 //DB4: move cursor/display
#define LCD_MOVE_DISP       3 //DB3: move display (0-> move cursor)
#define LCD_MOVE_RIGHT      2 //DB2: move right (0-> left)
#define LCD_FUNCTION        5 //DB5: function set
#define LCD_FUNCTION_8BIT   4 //DB4: set 8BIT mode (0->4BIT mode)
#define LCD_FUNCTION_2LINES 3 //DB3: two lines (0->one line)
#define LCD_FUNCTION_10DOTS 2 //DB2: 5x10 font (0->5x7 font)
#define LCD_CGRAM           6 //DB6: set CG RAM address
#define LCD_DDRAM           7 //DB7: set DD RAM address

// reading:
#define LCD_BUSY        7  //DB7: LCD is busy
#define LCD_LINES       2  //visible lines
#define LCD_LINE_LENGTH 16 //line length (in characters)

// cursor position to DDRAM mapping
#define LCD_LINE0_DDRAMADDR 0x00
#define LCD_LINE1_DDRAMADDR 0x40
#define LCD_LINE2_DDRAMADDR 0x14
#define LCD_LINE3_DDRAMADDR 0x54


class Lcd {
public:
    void sendChar(uint8_t);                                 //forms data ready to send to 74HC164
    void sendCommand(uint8_t);                              //forms data ready to send to 74HC164
    void init(void);                                        //Initializes LCD
    void clr(void);                                         //Clears LCD
    void home(void);                                        //LCD cursor home
    void string(uint8_t*, uint8_t);                         //Outputs string to LCD
    void gotoXY(uint8_t, uint8_t);                          //Cursor to X Y position
    void copyStringToLcd(const uint8_t*, uint8_t, uint8_t); //copies flash string to LCD at x,y
    void definechar(const uint8_t *,uint8_t);               //write char to LCD CGRAM
    void shiftRight(uint8_t);                               //shift by n characters Right
    void shiftLeft(uint8_t);                                //shift by n characters Left
    void cursorOn(void);                                    //Underline cursor ON
    void cursorOnBlink(void);                               //Underline blinking cursor ON
    void cursorOff(void);                                   //Cursor OFF
    void blank(void);                                       //LCD blank but not cleared
    void visible(void);                                     //LCD visible
    void cursorLeft(uint8_t);                               //Shift cursor left by n
    void cursorRight(uint8_t);                              //shif cursor right by n
};
