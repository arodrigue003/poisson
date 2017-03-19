//
// Created by clejacquet on 17/03/17.
//

#include <iostream>

#include "Connection.h"

Connection::Connection(const std::string& address, unsigned short port) :
    _address(address),
    _port(port)
{
    _tryConnect();
    _socket.setBlocking(false);
}

void Connection::sendQueuedMessages() {
    std::string data;
    std::size_t bytes_sent;

    while (_send_queue.try_dequeue(data)) {
        sf::Socket::Status status = _socket.send(data.c_str(), data.size(), bytes_sent);

        if (status == sf::Socket::Error) {
            std::cerr << "Error while sending" << std::endl;
        } else if (status == sf::Socket::Disconnected) {
            std::cerr << "Server is disconnected, trying to reconnect" << std::endl;
            _tryConnect();
        } else if (bytes_sent < data.length()) {
            std::cerr << "Error while sending (partial data)" << std::endl;
        }
    }
}

void Connection::sendMessage(const std::string &message) {
    _send_queue.enqueue(message);
}

void Connection::collectMessages() {
    std::size_t bytes_received;
    sf::Socket::Status status = _socket.receive(_reception_buffer, 100, bytes_received);

    if (status == sf::Socket::Error && _state == Connection::ACTIVE) {
        std::cerr << "Error while receiving" << std::endl;
    } else if (bytes_received > 0) {
        _reception_buffer[bytes_received / sizeof(char)] = '\0';
        onReceive(_reception_buffer);
    }
}

void Connection::_tryConnect() {
    _state = Connection::INIT;
    State init_state_ref = Connection::INIT;

    if (_state.compare_exchange_strong(init_state_ref, Connection::CONNECTING)) {
        _socket.disconnect();

        std::cout << "Try connection..." << std::endl;

        while (true) {
            sf::Socket::Status status = _socket.connect(_address, _port);

            if (status == sf::Socket::Done) {
                _state = Connection::ACTIVE;
                break;
            }

            std::cerr << "Error while connecting" << std::endl;
            std::cerr << "Trying again in 5 seconds" << std::endl;
            std::this_thread::sleep_for(std::chrono::seconds(5));
        }

        std::cout << "Connected!" << std::endl;
    }
}
