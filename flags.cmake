if(MSVC)
    set(warnings
        "/W4")
    set(cxxflags
        "/O2"
        "/Ox"
        "/Ot"
        "/std:c++14")
else()
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
endif()

string(REGEX REPLACE ";" " " cxxflags "${cxxflags}")
string(REGEX REPLACE ";" " " ldflags "${ldflags}")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${cxxflags}")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${ldflags}")
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_modules" ${CMAKE_MODULE_PATH})
