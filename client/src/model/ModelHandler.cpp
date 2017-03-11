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

void ModelHandler::registerRespond(std::string respond) {
    _respond_queue.enqueue(respond);
}

bool ModelHandler::getRespond(std::string &data) {
    return _respond_queue.try_dequeue(data);
}

void ModelHandler::clearRespond() {
    //TODO: not a yolo version of this

    std::string data;
    for (int i =0; i<20; i++) {
        _respond_queue.try_dequeue(data);
    }
}

void ModelHandler::init(NetworkHandler &network) {
    _network = &network;
}
