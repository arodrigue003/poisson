#ifndef FREEPOISSON_CLIENT_INPUTHANDLER_H
#define FREEPOISSON_CLIENT_INPUTHANDLER_H


class ModelHandler;
class NetworkHandler;

class InputHandler {
// TODO - Complete this class basis

private:
    ModelHandler* _model;
    NetworkHandler* _network;

public:
    InputHandler();
    ~InputHandler();

    void init(ModelHandler& model, NetworkHandler& network);
};


#endif //FREEPOISSON_CLIENT_INPUTHANDLER_H
