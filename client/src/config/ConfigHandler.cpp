#include "ConfigHandler.h"
#include "model/ModelHandler.h"

ConfigHandler::ConfigHandler() {

}

ConfigHandler::~ConfigHandler() {

}

void ConfigHandler::init(ModelHandler& model, NetworkHandler& network) {
    _model = &model;
    _network = &network;
}


