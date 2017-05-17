cmake_minimum_required(VERSION 2.6)

file(GLOB projects "modules/*/CMakeLists.txt")

if (MSVC)
    set(warnings
        "/W4")
    set(cxxflags
        "/O2"
        "/Ox"
        "/Ot"
        "/std:c++14")
else ()
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
        "-O3"
        ${warnings})

endif ()

string(REGEX REPLACE ";" " " cxxflags "${cxxflags}")
string(REGEX REPLACE ";" " " ldflags "${ldflags}")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${cxxflags}")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${ldflags}")
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_modules" ${CMAKE_MODULE_PATH})

foreach (project ${projects})
    string(REGEX REPLACE "[/\\]CMakeLists.txt$" "" sub_dir ${project})
    add_subdirectory(${sub_dir})
endforeach ()

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
