cmake_minimum_required(VERSION 2.6)

file(GLOB projects "modules/*/CMakeLists.txt")

foreach(project ${projects})
    string(REGEX REPLACE "[/\\]CMakeLists.txt$" "" sub_dir ${project})
    add_subdirectory(${sub_dir})
endforeach()

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
