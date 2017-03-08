#include "NetworkHandler.h"
#include "display/DisplayHandler.h"
#include <SFML/Network.hpp>
#include <iostream>

NetworkHandler::NetworkHandler(DisplayHandler *display) :
    _display(display)
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
}
