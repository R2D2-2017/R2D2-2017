cmake_minimum_required(VERSION 2.6)

project(mutest)
set(exe_name "mutest")

enable_testing()
include(../../flags.cmake)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

set(mustore ../../libraries/mustore)
add_subdirectory(${mustore} mustore)
include_directories(${mustore}/include)
link_libraries(mustore)


set(sources
    src/main.cc)

add_executable(${exe_name} ${sources})
