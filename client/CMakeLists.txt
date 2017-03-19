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
        src/display/ScrollableOutput.cpp src/network/parser/FishInfo.h)

add_library(input
        src/input/InputHandler.cpp)

add_library(model
        src/model/ModelHandler.cpp
        src/display/FishView.cpp
        src/model/Fish.cpp
        src/model/Transform.cpp)

add_library(network
        src/network/NetworkHandler.cpp
        src/network/Context.cpp
        src/network/request/impl/SimpleRequest.cpp
        src/network/request/impl/HelloRequest.cpp
        src/network/request/impl/ByeRequest.cpp
        src/network/request/impl/PingRequest.cpp
        src/network/request/AbstractRequest.h
        src/network/request/Request.h src/network/request/impl/AddFishRequest.cpp src/network/request/impl/AddFishRequest.h src/network/connection/Connection.cpp src/network/connection/Connection.h src/network/request/RequestConnection.cpp src/network/request/RequestConnection.h src/network/listener/ListenerConnection.cpp src/network/listener/ListenerConnection.h src/network/listener/Listener.h src/network/listener/AbstractListener.h src/network/Message.h src/network/listener/impl/SimpleListener.cpp src/network/listener/impl/SimpleListener.h src/network/listener/impl/GetFishesContinuouslyListener.cpp src/network/listener/impl/GetFishesContinuouslyListener.h src/network/parser/GetFishesParser.cpp src/network/parser/GetFishesParser.h src/network/request/impl/GetFishesRequest.cpp src/network/request/impl/GetFishesRequest.h)



add_executable(freepoisson_client src/main.cpp
        src/utils/concurrency/blockingconcurrentqueue.h
        src/utils/concurrency/concurrentqueue.h
        src/utils/memory/MemoryTypes.h
        src/utils/observer/Observable.h
        src/utils/observer/Observer.h)

target_link_libraries(freepoisson_client config display input model network)
target_link_libraries(freepoisson_client sfml-graphics sfml-window sfml-network sfml-system)

add_executable(freepoisson_client_test
        tst/GetFishesContinouslyListenerTest.cpp)

target_link_libraries(freepoisson_client_test network display sfml-window sfml-system sfml-network)
add_test(freepoisson_client_test freepoisson_client_test)