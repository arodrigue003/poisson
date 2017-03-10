cmake_minimum_required(VERSION 2.8)
project(freepoisson_client)

add_subdirectory(fonts)
add_subdirectory(textures)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -pthread -O2")

set(SOURCE_FILES
        src/main.cpp
        src/input/InputHandler.cpp
        src/input/InputHandler.h
        src/display/DisplayHandler.cpp
        src/display/DisplayHandler.h
        src/config/ConfigHandler.cpp
        src/config/ConfigHandler.h
        src/model/ModelHandler.cpp
        src/model/ModelHandler.h
        src/network/NetworkHandler.cpp
        src/network/NetworkHandler.h
        src/display/ScrollableOutput.cpp
        src/display/ScrollableOutput.hpp)

include_directories(src)

add_executable(freepoisson_client ${SOURCE_FILES})
add_executable(sfmltest src/sfmltest.cpp)

target_link_libraries(freepoisson_client sfml-graphics sfml-window sfml-network sfml-system)

target_link_libraries(sfmltest sfml-graphics sfml-window sfml-system)
