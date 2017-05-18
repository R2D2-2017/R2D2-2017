cmake_minimum_required (VERSION 2.8.11)
set(toolchain ../../toolchain) # Your path to kvasir_toolchain
set(CMAKE_TOOLCHAIN_FILE ${toolchain}/compilers/arm-none-eabi.cmake)
project (template-arduino CXX)

set(hwlib ../../libraries/hwlib)
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -specs=nosys.specs")
include(../../flags.cmake)

set(sources src/main.cc)

include_directories(
	${hwlib}/library
)

set(sources
    #${hwlib}/library/hwlib.cpp
    src/wrap-hwlib.cc
    src/main.cc
)

# Location of the flash tool if it's not in your path
#set(flash_program_path ~/bossac) # Your path to the flash tool

# The compiler that is used:
#include(${toolchain}/compilers/arm-none-eabi.cmake)

# The target chip that is compiled for:
include(${toolchain}/targets/arm32/cm3/atmel/sam3x/sam3x8e/sam3x8e.cmake)

# The flashscript used to flash the binary (optional):
include(${toolchain}/targets/arm32/cm3/atmel/sam3x/sam3x8e/flashscripts/arduino_due.cmake)
