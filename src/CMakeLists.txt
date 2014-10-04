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
#add_custom_target("prog")
#add_custom_command(
#    TARGET "prog"
#    COMMAND avrdude6 ARGS -C avrdude.conf -P /dev/ttyUSB0 -c UM232H -p m16 -b 115200 -U flash:w:${WELDER}.hex:a
#    DEPENDS ${WELDER}_hex
#    WORKING_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}
#    )
