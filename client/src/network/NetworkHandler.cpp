
#include <SFML/Network.hpp>
#include <iostream>

#include "NetworkHandler.h"
#include "model/ModelHandler.h"

NetworkHandler::NetworkHandler() :
    _requestHandler(*this)
{

}

NetworkHandler::~NetworkHandler() {
    _state = NetworkHandler::KILLED;
    _send_thread.join();
    _receive_thread.join();
}

void NetworkHandler::launch(std::string address, unsigned short port) {
    _address = address;
    _port = port;
    _tryConnect();

    _socket.setBlocking(false);

    _send_thread = std::thread(&NetworkHandler::_sendRoutine, this);
    _receive_thread = std::thread(&NetworkHandler::_receiveRoutine, this);
}

void NetworkHandler::_sendMessage(std::string msg) {
    _send_queue.enqueue(msg);
}

void NetworkHandler::_sendRoutine() {
    std::string data;
    std::size_t bytes_sent;
    std::chrono::milliseconds timespan(100);

    while (_state != NetworkHandler::KILLED) {
        while (_send_queue.try_dequeue(data)) {
            sf::Socket::Status status = _socket.send(data.c_str(), data.size(), bytes_sent);

            if (status == sf::Socket::Error) {
                std::cerr << "Error while sending" << std::endl;
            } else if (status == sf::Socket::Disconnected) {
                std::cerr << "Server is disconnected, trying to reconnect" << std::endl;
                _tryConnect();
                _send_queue.enqueue(data);
            } else if (bytes_sent < data.length()) {
                std::cerr << "Error while sending (partial data)" << std::endl;
            }
        }

        std::this_thread::sleep_for(timespan);
    }
}

void NetworkHandler::_receiveRoutine() {
    char buffer[100];
    std::size_t bytes_received;
    std::chrono::milliseconds timespan(100);

    while (_state != NetworkHandler::KILLED) {
        sf::Socket::Status status = _socket.receive(buffer, 100, bytes_received);

        if (status == sf::Socket::Error && _state == NetworkHandler::ACTIVE) {
            std::cerr << "Error while receiving" << std::endl;
        } else if (bytes_received > 0) {
            buffer[bytes_received / sizeof(char)] = '\0';
            _requestHandler.registerResponse(buffer);
        }

        std::this_thread::sleep_for(timespan);
    }
}

void NetworkHandler::_tryConnect() {
    _state = NetworkHandler::INIT;
    State init_state_ref = NetworkHandler::INIT;

    if (_state.compare_exchange_strong(init_state_ref, NetworkHandler::CONNECTING)) {
        _socket.disconnect();

        std::cout << "Try connection..." << std::endl;
        std::chrono::milliseconds timespan(10000);

        while (true) {
            sf::Socket::Status status = _socket.connect(_address, _port);

            if (status == sf::Socket::Done) {
                _state = NetworkHandler::ACTIVE;
                break;
            }

            std::cerr << "Error while connecting" << std::endl;
            std::cerr << "Trying again in 10 secondes" << std::endl;
            std::this_thread::sleep_for(timespan);
        }
    }
}




