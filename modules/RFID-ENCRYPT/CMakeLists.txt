cmake_minimum_required(VERSION 2.6)

project(rfid-encrypt)
set(exe_name "rfid-encrypt")

enable_testing()
include(../../flags.cmake)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

set(sources
    src/main.cc
    src/Encryption.hh
    src/Encryption.cc
	)

add_executable(${exe_name} ${sources})
