cmake_minimum_required(VERSION 2.8)
project(freepoisson_client)

add_subdirectory(fonts)
add_subdirectory(textures)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -pthread -g -O0")

add_library(config
        src/config/ConfigHandler.cpp)
add_library(display
        src/display/DisplayHandler.cpp
        src/display/Input.cpp
        src/display/ScrollableOutput.cpp)
add_library(input
        src/input/InputHandler.cpp)
add_library(model
        src/model/ModelHandler.cpp)
add_library(network
        src/network/NetworkHandler.cpp
        src/network/request/RequestContext.cpp
        src/network/request/SimpleRequest.cpp
        src/network/request/AbstractRequest.h
        src/network/request/Request.h)

include_directories(src)

add_executable(sfmltest src/sfmltest.cpp)

add_executable(freepoisson_client src/main.cpp)
target_link_libraries(freepoisson_client config display input model network)
target_link_libraries(freepoisson_client sfml-graphics sfml-window sfml-network sfml-system)

target_link_libraries(sfmltest sfml-graphics sfml-window sfml-system)
