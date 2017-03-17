#ifndef FREEPOISSON_CLIENT_DISPLAYHANDLER_H
#define FREEPOISSON_CLIENT_DISPLAYHANDLER_H

#include <iostream>
#include <sstream>

#include <SFML/Graphics.hpp>

class ModelHandler;

class DisplayHandler {
// TODO - Complete this class basis

private:
    ModelHandler *_model;
    bool _commandMode;

public:
    DisplayHandler();

    void init(ModelHandler &model);

    void launch();

};


#endif //FREEPOISSON_CLIENT_DISPLAYHANDLER_H
