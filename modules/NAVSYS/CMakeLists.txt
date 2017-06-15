cmake_minimum_required(VERSION 2.6)

project(navsys)
set(exe_client "navsys-client")
set(exe_server "navsys-server")

enable_testing()
include(../../flags.cmake)


include_directories(${CMAKE_CURRENT_SOURCE_DIR}/common)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)
include_directories(${SFML_INCLUDE_DIR})

set(common_sources   
    common/node.cc
    common/coordinate.cc
    common/vertice.cc
    common/graph.cc
    common/graph-input.cc
    common/graph-factory.cc
    common/protocol.cc
    common/pathnode.cc
    common/mouse.cc)

set(client_sources
    client/main.cc
    client/client.cc
    client/graphicsgraph.cc
    client/graphicsnodes.cc
    client/graphicsvertices.cc
    client/window.cc
    client/gestures.cc
    client/button.cc)
  
set(server_sources
    server/main.cc
    server/server.cc
    server/astar.cc)

find_package(SFML 2 REQUIRED system window graphics network audio)

add_executable(${exe_client} ${common_sources} ${client_sources})
target_link_libraries(${exe_client} ${SFML_LIBRARIES} pthread)

add_executable(${exe_server} ${common_sources} ${server_sources})
target_link_libraries(${exe_server} ${SFML_LIBRARIES} pthread)
