#include <iostream>

#include "model/ModelHandler.h"
#include "display/DisplayHandler.h"
#include "network/NetworkHandler.h"
#include "input/InputHandler.h"
#include "config/ConfigHandler.h"

int main() {

    // Creation of handlers

    ModelHandler model;
    DisplayHandler display(&model);
    NetworkHandler network(&model);
    InputHandler input(&model, &network);
    ConfigHandler config(&model, &network);

    // Start of logic
    // TODO Implement global logic by calling handler primitives
    std::cout << "Handlers are fully initialized!" << std::endl;

    return 0;
}