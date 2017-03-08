#ifndef FREEPOISSON_CLIENT_DISPLAYHANDLER_H
#define FREEPOISSON_CLIENT_DISPLAYHANDLER_H


class ModelHandler;

class DisplayHandler {
// TODO - Complete this class basis

private:
    ModelHandler* _model;

public:
    DisplayHandler(ModelHandler* model);
    launch();
};


#endif //FREEPOISSON_CLIENT_DISPLAYHANDLER_H
