cmake_minimum_required(VERSION 2.6)

project(navsys)
set(exe_name "navsys")

enable_testing()
include(../../flags.cmake)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

set(sources
    src/main.cc src/node.cc src/node.hh src/coordinate.cc src/coordinate.hh src/vertice.cc src/vertice.hh src/graph.cc src/graph.hh src/pathnode.cc src/pathnode.hh src/astar.cc src/astar.hh src/graph-input.cc src/graph-input.hh src/graph-factory.cc src/graph-factory.hh)


add_executable(${exe_name} ${sources})
