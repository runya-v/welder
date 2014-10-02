set(BIN welding)
set(SOURCE
    main.cpp
    )
add_executable(${BIN} ${SOURCE})
add_dependencies(${BIN} lcd)
target_link_libraries(${BIN} lcd)

avr_create_hex(${BIN})
