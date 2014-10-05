#define F_CPU 800000UL

#include <stdio.h>
#include <avr/io.h>
#include <avr/pgmspace.h>
#include <util/delay.h>  // Хотим использовать функции задержек

#include "lcd/lcd.hpp"


int main() {
    Lcd lcd;

    lcd.setCursor(0, 4);
    lcd.writeString("RABOTAET");
    lcd.setCursor(1, 3);
    lcd.writeString("BILYAT!!!");

    while(1)
    {}
}
