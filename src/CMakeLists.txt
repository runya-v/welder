include_directories(${LCD_DIR})

set(WELDER "welder")
set(SOURCE
    main.cpp
    )
add_executable(${WELDER} ${SOURCE})
add_dependencies(${WELDER} lcd)
target_link_libraries(${WELDER} lcd)

avr_create_hex(${WELDER})
avr_programm(${WELDER})
