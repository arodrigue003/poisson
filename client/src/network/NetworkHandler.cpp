#include <SFML/Network.hpp>
#include <iostream>

#include "NetworkHandler.h"
#include "model/ModelHandler.h"

NetworkHandler::NetworkHandler() :
    _request_counter(0),
    _response_counter(0)
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

    while (_state != NetworkHandler::KILLED) {
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

        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}

void NetworkHandler::_receiveRoutine() {
    char buffer[100];
    std::size_t bytes_received;

    while (_state != NetworkHandler::KILLED) {
        _checkNextRequest();

        sf::Socket::Status status = _socket.receive(buffer, 100, bytes_received);

        if (status == sf::Socket::Error && _state == NetworkHandler::ACTIVE) {
            std::cerr << "Error while receiving" << std::endl;
        } else if (bytes_received > 0) {
            buffer[bytes_received / sizeof(char)] = '\0';
            _registerResponse(buffer);
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}

void NetworkHandler::_tryConnect() {
    _state = NetworkHandler::INIT;
    State init_state_ref = NetworkHandler::INIT;

    if (_state.compare_exchange_strong(init_state_ref, NetworkHandler::CONNECTING)) {
        _socket.disconnect();

        std::cout << "Try connection..." << std::endl;

        while (true) {
            sf::Socket::Status status = _socket.connect(_address, _port);

            if (status == sf::Socket::Done) {
                _state = NetworkHandler::ACTIVE;
                break;
            }

            std::cerr << "Error while connecting" << std::endl;
            std::cerr << "Trying again in 5 seconds" << std::endl;
            std::this_thread::sleep_for(std::chrono::seconds(5));
        }

        std::cout << "Connected!" << std::endl;
    }
}

void NetworkHandler::_checkNextRequest() {
    std::chrono::system_clock::time_point now = std::chrono::system_clock::now();

    if (_response_counter == _request_counter) {
        return;
    }

    RequestContext next_context = _pending_requests.at(_response_counter);
    if (next_context.elapsedTime(now) > std::chrono::seconds(5)) {
        for (std::pair<unsigned int, RequestContext> pair : _pending_requests) {
            RequestContext context = pair.second;
            context.onCancel();
        }

        _pending_request_write_lock.lock();
        _pending_requests.clear();
        _pending_request_write_lock.unlock();

        _response_counter = _request_counter;
    }
}

void NetworkHandler::_registerResponse(std::string response) {
    std::unordered_map<unsigned int, RequestContext>::iterator it = _pending_requests.find(_response_counter);
    if (it != _pending_requests.end()) {
        it->second.onResponse(response);

        _pending_request_write_lock.lock();
        _pending_requests.erase(_response_counter);
        _pending_request_write_lock.unlock();
    }
    _response_counter++;
}
