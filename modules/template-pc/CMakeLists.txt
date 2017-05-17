cmake_minimum_required(VERSION 2.6)

project(template-pc)
set(exe_name "template-pc")

enable_testing()

set(warnings
    "-Wall"
    "-Wextra"
    "-pedantic-errors"
    "-Wfatal-errors"
    "-Wcast-align"
    "-Wmissing-declarations"
    "-Wredundant-decls"
    "-Wuninitialized"
    "-Wno-unused-parameter"
    "-Wno-missing-field-initializers")

set(cxxflags
    "-std=c++14"
    "-g3"
    "-ggdb"
    "-O2"
    ${warnings})

string(REGEX REPLACE ";" " " cxxflags "${cxxflags}")
string(REGEX REPLACE ";" " " ldflags "${ldflags}")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${cxxflags}")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${ldflags}")

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

set(sources
    src/main.cc)

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_modules" ${CMAKE_MODULE_PATH})
#find_package(Boost REQUIRED COMPONENTS system filesystem)

add_executable(${exe_name} ${sources})
#target_link_libraries(${EXE} ${Boost_LIBRARIES} pthread)
