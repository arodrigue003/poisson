#ifndef FREEPOISSON_CLIENT_DISPLAYHANDLER_H
#define FREEPOISSON_CLIENT_DISPLAYHANDLER_H

#include <iostream>
#include <sstream>

#include <SFML/Graphics.hpp>

#include <network/NetworkHandler.h>

class ModelHandler;

class DisplayHandler {
// TODO - Complete this class basis

private:
    NetworkHandler *_network;
    bool _commandMode;

public:
    DisplayHandler();

    void init(NetworkHandler &model);

    void launch();

};


#endif //FREEPOISSON_CLIENT_DISPLAYHANDLER_H
