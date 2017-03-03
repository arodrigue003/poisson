#ifndef FREEPOISSON_CLIENT_CONFIGHANDLER_H
#define FREEPOISSON_CLIENT_CONFIGHANDLER_H


class ModelHandler;
class NetworkHandler;

class ConfigHandler {
// TODO - Complete this class basis

private:
    ModelHandler* _model;
    NetworkHandler* _network;

public:
    ConfigHandler(ModelHandler* model, NetworkHandler* network);
};


#endif //FREEPOISSON_CLIENT_CONFIGHANDLER_H
