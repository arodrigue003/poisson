#include "ModelHandler.h"
#include "network/NetworkHandler.h"

ModelHandler::ModelHandler()
{

}

ModelHandler::~ModelHandler() {

}

void ModelHandler::registerCommand(std::string command) {
    _network->sendMessage(command);
}

void ModelHandler::init(NetworkHandler &network) {
    _network = &network;
}
