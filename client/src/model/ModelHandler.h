#ifndef FREEPOISSON_CLIENT_MODELHANDLER_H
#define FREEPOISSON_CLIENT_MODELHANDLER_H

#include <string>

#include <utils/concurrency/blockingconcurrentqueue.h>

using namespace moodycamel;

class NetworkHandler;

class ModelHandler {
private:
    NetworkHandler* _network;

public:
    ModelHandler();
    ~ModelHandler();

    void init(NetworkHandler& network);
    void registerCommand(std::string command);
};


#endif //FREEPOISSON_CLIENT_MODELHANDLER_H
