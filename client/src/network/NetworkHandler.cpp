#include <SFML/Network.hpp>
#include <iostream>

#include "NetworkHandler.h"
#include "model/ModelHandler.h"

NetworkHandler::NetworkHandler() :
    _active(true)
{

}

NetworkHandler::~NetworkHandler() {
    _active = false;
    _send_thread.join();
    _receive_thread.join();
}

void NetworkHandler::launch(std::string address, unsigned short port) {
    _request_connection = Ptr<RequestConnection>(new RequestConnection(address, port));
    _listener_connection = Ptr<ListenerConnection>(new ListenerConnection(address, port));

    _send_thread = std::thread(&NetworkHandler::_sendRoutine, this);
    _receive_thread = std::thread(&NetworkHandler::_receiveRoutine, this);
}

void NetworkHandler::_sendRoutine() {
    while (_active) {
        _request_connection->sendQueuedMessages();
        _listener_connection->sendQueuedMessages();

        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}

void NetworkHandler::_receiveRoutine() {
    while (_active) {
        _request_connection->collectMessages();
        _listener_connection->collectMessages();

        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}
