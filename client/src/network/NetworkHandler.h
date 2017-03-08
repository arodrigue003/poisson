#ifndef FREEPOISSON_CLIENT_NETWORKHANDLER_H
#define FREEPOISSON_CLIENT_NETWORKHANDLER_H

#include <string>

class ModelHandler;

class NetworkHandler {
// TODO - Complete this class basis

private:
    ModelHandler* _model;

public:
    NetworkHandler(ModelHandler* model);

    void connect(std::string address, unsigned short port);
};


#endif //FREEPOISSON_CLIENT_NETWORKHANDLER_H
