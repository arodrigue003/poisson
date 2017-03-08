#ifndef FREEPOISSON_CLIENT_DISPLAYHANDLER_H
#define FREEPOISSON_CLIENT_DISPLAYHANDLER_H

#include <iostream>
#include <sstream>

class ModelHandler;

class DisplayHandler {
// TODO - Complete this class basis

private:
    ModelHandler* _model;
    bool _commandMode;
    std::string _input;

public:
    DisplayHandler(ModelHandler* model);
    void launch();
};


#endif //FREEPOISSON_CLIENT_DISPLAYHANDLER_H
