cmake_minimum_required(VERSION 2.6)

project(navsys)
set(exe_name "navsys")

enable_testing()
include(../../flags.cmake)




include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)
include_directories(${SFML_INCLUDE_DIR})
set(sources
    src/main.cc src/node.cc src/node.hh src/coordinate.cc src/coordinate.hh src/vertice.cc src/vertice.hh src/graph.cc src/graph.hh src/graphnodes.hpp src/graphnodes.cpp src/vertices.hpp src/vertices.cpp  )

find_package(SFML 2 REQUIRED graphics window system network audio)
add_executable(${exe_name} ${sources})
target_link_libraries(${exe_name} ${SFML_LIBRARIES} ${SFML_DEPENDENCIES} pthread)
