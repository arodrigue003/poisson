cmake_minimum_required(VERSION 2.8)
project(freepoisson_client)

add_subdirectory(fonts)
add_subdirectory(textures)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -pthread -g -O0")

set(DISPLAY_FILES
        src/display/DisplayHandler.cpp
        src/display/DisplayHandler.h
        src/display/ScrollableOutput.cpp
        src/display/ScrollableOutput.hpp)

set(MODEL_FILES
        src/model/ModelHandler.cpp
        src/model/ModelHandler.h
        src/network/request/SimpleRequest.cpp
        src/network/request/SimpleRequest.h
        src/network/request/HelloRequest.h
        src/network/request/HelloRequest.cpp src/network/request/ByeRequest.cpp src/network/request/ByeRequest.h src/model/Fish.h src/model/Fish.cpp)

set(NETWORK_FILES
        src/network/NetworkHandler.cpp
        src/network/NetworkHandler.h
        src/network/Request.h
        src/network/AbstractRequest.h
        src/network/RequestContext.cpp
        src/network/RequestContext.h)

set(INPUT_FILES
        src/input/InputHandler.cpp
        src/input/InputHandler.h)

set(CONFIG_FILES
        src/config/ConfigHandler.cpp
        src/config/ConfigHandler.h)

set(UTILS_FILES
        src/utils/observer/Observable.h
        src/utils/observer/Observer.h
        src/utils/memory/MemoryTypes.h)

set(SOURCE_FILES
        src/main.cpp
        ${DISPLAY_FILES}
        ${MODEL_FILES}
        ${NETWORK_FILES}
        ${INPUT_FILES}
        ${CONFIG_FILES}
        ${UTILS_FILES} src/network/request/PingRequest.cpp src/network/request/PingRequest.h src/model/Transform.cpp src/model/Transform.h)

set(TEST_FILES
        tst/HelloRequestTest.cpp
        src/network/request/HelloRequest.cpp
        src/network/request/HelloRequest.h

        tst/fructose/fructose.h
        tst/fructose/double_compare.h
        tst/fructose/test_base.h
        tst/fructose/test_root.h src/network/request/ByeRequest.cpp src/network/request/ByeRequest.h)


add_executable(freepoisson_client ${SOURCE_FILES})
add_executable(freepoisson_client_test ${TEST_FILES})

add_executable(sfmltest src/sfmltest.cpp)

target_include_directories(freepoisson_client PRIVATE src)
target_include_directories(freepoisson_client_test PRIVATE src PRIVATE tst)

target_link_libraries(freepoisson_client sfml-graphics sfml-window sfml-network sfml-system)
target_link_libraries(sfmltest sfml-graphics sfml-window sfml-system)
