cmake_minimum_required(VERSION 2.6)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/module-naam)
file(GLOB projects "modules/*/CMakeLists.txt"
foreach(project ${projects})
	#do something here
endforeach()
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
