cmake_minimum_required(VERSION 2.6.0)

message("\nConfigure project Welding...")

project(welding)

set(CMAKE_SYSTEM_NAME Generic)

set(CMAKE_C_COMPILER avr-gcc)
set(CMAKE_CXX_COMPILER avr-g++)

set(CSTANDARD "-std=gnu11")
set(CDEBUG "-gstabs")
set(CWARN "-Wall -Wstrict-prototypes")
set(CTUNING "-funsigned-char -funsigned-bitfields -fpack-struct -fshort-enums")
set(COPT "-Os")
set(CMCU "-mmcu=atmega16")
set(CDEFS "-DF_CPU=8000000UL")

set(CFLAGS "${CMCU} ${CDEBUG} ${CDEFS} ${CINCS} ${COPT} ${CWARN} ${CSTANDARD} ${CEXTRA}")
set(CXXFLAGS "${CMCU} ${CDEFS} ${CINCS} ${COPT}")

set(CMAKE_C_FLAGS  ${CFLAGS})
set(CMAKE_CXX_FLAGS ${CXXFLAGS})

set(ROOT_DIR   ${CMAKE_CURRENT_SOURCE_DIR})
set(BINARY_DIR ${CMAKE_CURRENT_BINARY_DIR})
set(SRC_DIR    ${ROOT_DIR}/src)
set(TEST_DIR   ${ROOT_DIR}/test)
set(LCD_DIR    ${SRC_DIR}/lcd)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${BINARY_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${BINARY_DIR}/lib)


# create avr hex
macro(avr_create_hex NAME_ELF)
    add_custom_command(
        TARGET ${NAME_ELF} POST_BUILD
        COMMAND avr-objcopy ARGS -O ihex -R.eeprom ${NAME_ELF} ${NAME_ELF}.hex
        DEPENDS ${NAME_ELF}
        WORKING_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}
        )
endmacro(avr_create_hex)

include_directories(${SRC_DIR})
add_subdirectory(${SRC_DIR})
add_subdirectory(${LCD_DIR})
