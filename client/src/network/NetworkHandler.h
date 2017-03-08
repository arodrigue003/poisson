#ifndef FREEPOISSON_CLIENT_NETWORKHANDLER_H
#define FREEPOISSON_CLIENT_NETWORKHANDLER_H

#include <string>
#include <thread>

class ModelHandler;

class NetworkHandler {
// TODO - Complete this class basis

// Attributes
private:
    ModelHandler* _model;
    std::thread _thread;


// Methods
public:
    NetworkHandler(ModelHandler* model);
    ~NetworkHandler();

private:
    void launch();
    void connect(std::string address, unsigned short port);
};


#endif //FREEPOISSON_CLIENT_NETWORKHANDLER_H
