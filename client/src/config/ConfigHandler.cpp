#include "ConfigHandler.h"
#include "model/ModelHandler.h"

ConfigHandler::ConfigHandler(ModelHandler* model, NetworkHandler* network) :
        _model(model),
        _network(network)
{

}
