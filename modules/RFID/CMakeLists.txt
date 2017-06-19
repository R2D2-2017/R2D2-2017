cmake_minimum_required(VERSION 2.6)

project(template-pc)
set(exe_name "rfid")
include(../../flags.cmake)

enable_testing()

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

find_library(WIRINGPI_LIBRARIES NAMES wiringPi)
find_path(WIRINGPI_INCLUDE_DIRS NAMES wiringPi.h)
include_directories(${WIRINGPI_INCLUDE_DIRS})
find_package(mysqlcppconn)
include_directories(${mysqlcppconn_INCLUDE_DIRS})

set(sources
    src/main.cc
    src/mysql.cc
    src/mfrc522.cc
    src/encryption.cc
    src/led-controller.cc
    src/matrix-keypad.cc
    src/config-file-parser.cc src/databasemanager.cc src/databasemanager.hh)

add_executable(${exe_name} ${sources})
target_link_libraries(${exe_name} ${WIRINGPI_LIBRARIES} ${mysqlcppconn_LIBRARIES})

