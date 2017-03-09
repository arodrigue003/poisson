
#include <SFML/Network.hpp>
#include <iostream>

#include "NetworkHandler.h"
#include "model/ModelHandler.h"

NetworkHandler::NetworkHandler() {

}

NetworkHandler::~NetworkHandler() {
    _is_active = false;
    _send_thread.join();
    _receive_thread.join();
}

void NetworkHandler::sendMessage(std::string msg) {
    _send_queue.enqueue(msg);
}

void NetworkHandler::_send_routine() {
    std::string data;

    while (_is_active) {
        _send_queue.wait_dequeue(data);
        if (_socket.send(data.c_str(), data.size()) != sf::Socket::Done) {
            std::cerr << "Error while sending" << std::endl;
        }

        // for debugging purpose
        std::cout << "\t>> " << data << std::endl;
    }
}

void NetworkHandler::_receive_routine() {
    char buffer[100];
    std::size_t bytes_received;

    while (_is_active) {
        if (_socket.receive(buffer, 100, bytes_received) != sf::Socket::Done) {
            std::cerr << "Error while receiving" << std::endl;
        }

        std::cout << "\t<< " << buffer << std::endl;
    }
}

void NetworkHandler::init(ModelHandler &model) {
    _model = &model;
}

void NetworkHandler::launch(std::string address, unsigned short port) {
    _is_active = true;

    bool connectionSuccess = false;
    std::chrono::milliseconds timespan(10000);

    while (!connectionSuccess) {
        sf::Socket::Status status = _socket.connect(address, port);

        if (status != sf::Socket::Done) {
            std::cerr << "Error while connecting" << std::endl;
            std::cerr << "Trying again in 10 secondes" << std::endl;
        }
        else
            connectionSuccess = true;

        std::this_thread::sleep_for(timespan);
    }

    _send_thread = std::thread(&NetworkHandler::_send_routine, this);
    _receive_thread = std::thread(&NetworkHandler::_receive_routine, this);
}


