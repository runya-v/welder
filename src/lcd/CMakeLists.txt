set(LCD_LIB "lcd" )
set(HEADER
    lcd.hpp
    )
set(SOURCE
    lcd.cpp
    )
add_library(${LCD_LIB} STATIC ${HEADER} ${SOURCE})
