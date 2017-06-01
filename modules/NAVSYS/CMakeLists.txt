cmake_minimum_required(VERSION 2.6)

project(navsys)
set(exe_client "navsys-client")
set(exe_server "navsys-server")

enable_testing()
include(../../flags.cmake)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/common)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

set(common_sources
        common/node.cc common/node.hh common/coordinate.cc common/coordinate.hh common/vertice.cc common/vertice.hh common/graph.cc common/graph.hh)

set(client_sources
	client/main.cc client/client.cc client/client.hh common/graph-factory.cc common/graph-factory.hh)

set(server_sources
	server/main.cc server/server.cc server/server.hh common/pathnode.cc common/pathnode.hh common/astar.cc common/astar.hh common/graph-input.cc common/graph-input.hh common/graph-factory.cc common/graph-factory.hh)

find_package(SFML 2 REQUIRED system window graphics network audio)

add_executable(${exe_client} ${common_sources} ${client_sources})
target_link_libraries(${exe_client} ${SFML_LIBRARIES} pthread)

add_executable(${exe_server} ${common_sources} ${server_sources})
target_link_libraries(${exe_server} ${SFML_LIBRARIES} pthread)
