#include "InputHandler.h"
#include "model/ModelHandler.h"
#include "network/NetworkHandler.h"

InputHandler::InputHandler() {

}

InputHandler::~InputHandler() {

}

void InputHandler::init(ModelHandler& model, NetworkHandler& network) {
    _model = &model;
    _network = &network;
}
