//
// Created by clejacquet on 18/03/17.
//

#include "ListenerConnection.h"

ListenerConnection::ListenerConnection(const std::string &address, unsigned short port) :
        Connection(address, port)
{

}

void ListenerConnection::onReceive(const std::string &message) {
    _listening_context->onResponse(message);
}
