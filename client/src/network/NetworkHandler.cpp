
#include <SFML/Network.hpp>
#include <iostream>

#include "NetworkHandler.h"
#include "model/ModelHandler.h"

NetworkHandler::NetworkHandler(ModelHandler *model) :
    _model(model)
{

}

void NetworkHandler::connect(std::string address, unsigned short port) {
    sf::TcpSocket socket;
    sf::Socket::Status status = socket.connect(address, port);

    if (status != sf::Socket::Done) {
        std::cerr << "Error while connection" << std::endl;
    }

    std::string data = "Hello World!";
    if (socket.send(data.c_str(), data.size()) != sf::Socket::Done) {
        std::cerr << "Error while sending" << std::endl;
    }

    std::cout << "Data sending succeeded" << std::endl;

    char buffer[100];
    std::size_t bytes_received;
    if (socket.receive(buffer, 100, bytes_received) != sf::Socket::Done) {
        std::cerr << "Error while receiving" << std::endl;
    }

    std::cout << "Received:" << std::endl
              << "\t> " << buffer << std::endl;
}
