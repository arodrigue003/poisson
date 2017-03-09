cmake_minimum_required(VERSION 2.8)
project(controller)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES
    aquarium.h
    client.h
    controller.c
    controller.h
    fish.h
    utils.h)

add_executable(controller ${SOURCE_FILES})
