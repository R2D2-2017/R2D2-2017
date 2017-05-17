cmake_minimum_required(VERSION 2.6)

project(template-pc)
set(exe_name "template-pc")

enable_testing()

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

set(sources
    src/main.cc)

add_executable(${exe_name} ${sources})
