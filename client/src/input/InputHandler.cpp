#include "InputHandler.h"
#include "model/ModelHandler.h"
#include "network/NetworkHandler.h"

InputHandler::InputHandler(ModelHandler* model, NetworkHandler* network) :
    _model(model),
    _network(network)
{

}
