#include <iostream>

#include <network/NetworkHandler.h>
#include <network/request/SimpleRequest.h>

#include "ModelHandler.h"

ModelHandler::ModelHandler()
{

}

ModelHandler::~ModelHandler() {

}

void ModelHandler::registerCommand(std::string command) {
    std::cout << "\t>> " << command << std::endl;
    Ptr<SimpleRequest> request = _network->send(Ptr<SimpleRequest>(new SimpleRequest(command)));

    try {
        std::cout << "\t<< " << request->getResponse() << std::endl << std::endl;
    } catch (std::string err) {
        std::cerr << err << std::endl;
    }
}

void ModelHandler::init(NetworkHandler &network) {
    _network = &network;
}
