#ifndef FREEPOISSON_CLIENT_MODELHANDLER_H
#define FREEPOISSON_CLIENT_MODELHANDLER_H

#include <string>

class NetworkHandler;

class ModelHandler {
// TODO - Complete this class basis
private:
    NetworkHandler* _network;

public:
    ModelHandler();
    ~ModelHandler();

    void init(NetworkHandler& network);
    void registerCommand(std::string command);
};


#endif //FREEPOISSON_CLIENT_MODELHANDLER_H
