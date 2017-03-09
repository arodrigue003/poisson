#include <iostream>

#include "model/ModelHandler.h"
#include "display/DisplayHandler.h"
#include "network/NetworkHandler.h"
#include "input/InputHandler.h"
#include "config/ConfigHandler.h"

int main() {

    // Creation of handlers

    ModelHandler model;
    DisplayHandler display;
    NetworkHandler network;
    InputHandler input;
    ConfigHandler config;

    model.init(network);
    display.init(model);
    network.init(model);
    input.init(model, network);
    config.init(model, network);

    // Start of logic
    // TODO Implement global logic by calling handler primitives
    std::cout << "Handlers are fully initialized!" << std::endl;

    network.launch("127.0.0.1", 12345);
    display.launch();

    return 0;
}