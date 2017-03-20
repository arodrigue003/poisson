cmake_minimum_required(VERSION 2.8)
project(controller)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c99")

set(SOURCE_FILES
    aquarium.h
    aquarium.c
    client.h
    controller.c
    controller.h
    fish.h
    utils.h)

add_executable(controller ${SOURCE_FILES})
