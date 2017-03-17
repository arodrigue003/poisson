cmake_minimum_required(VERSION 2.8)
project(freepoisson_client)

enable_testing()

add_subdirectory(fonts)
add_subdirectory(textures)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -pthread -g -O0")

include_directories(src)
include_directories(tst)

add_library(config
        src/config/ConfigHandler.cpp)

add_library(display
        src/display/DisplayHandler.cpp
        src/display/Input.cpp
        src/display/ScrollableOutput.cpp)

add_library(input
        src/input/InputHandler.cpp)

add_library(model
        src/model/ModelHandler.cpp
        src/model/Poisson.cpp
        src/model/Fish.cpp
        src/model/Transform.cpp)

add_library(network
        src/network/NetworkHandler.cpp
        src/network/RequestContext.cpp
        src/network/request/SimpleRequest.cpp
        src/network/request/HelloRequest.cpp
        src/network/request/ByeRequest.cpp
        src/network/request/PingRequest.cpp
        src/network/AbstractRequest.h
        src/network/Request.h)



add_executable(freepoisson_client src/main.cpp
        src/utils/concurrency/blockingconcurrentqueue.h
        src/utils/concurrency/concurrentqueue.h
        src/utils/memory/MemoryTypes.h
        src/utils/observer/Observable.h
        src/utils/observer/Observer.h)

target_link_libraries(freepoisson_client config display input model network)
target_link_libraries(freepoisson_client sfml-graphics sfml-window sfml-network sfml-system)

add_executable(freepoisson_client_test
        tst/HelloRequestTest.cpp)

target_link_libraries(freepoisson_client_test network sfml-network)
add_test(freepoisson_client_test freepoisson_client_test)