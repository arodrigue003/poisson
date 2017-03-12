#ifndef FREEPOISSON_CLIENT_NETWORKHANDLER_H
#define FREEPOISSON_CLIENT_NETWORKHANDLER_H

#include <string>
#include <thread>
#include <atomic>

#include <SFML/Network.hpp>
#include <utils/concurrency/blockingconcurrentqueue.h>
#include "RequestHandler.h"

using namespace moodycamel;

class ModelHandler;

class NetworkHandler {
// TODO - Complete this class basis

// Enums
private:
    enum State {
        INIT,
        ACTIVE,
        CONNECTING,
        KILLED
    };

// Attributes
private:
    RequestHandler _requestHandler;

    sf::TcpSocket _socket;
    std::string _address;
    unsigned short _port;

    std::thread _send_thread;
    std::thread _receive_thread;
    std::atomic<State> _state;
    BlockingConcurrentQueue<std::string> _send_queue;

// Methods
public:
    NetworkHandler();
    ~NetworkHandler();

    void launch(std::string address, unsigned short port);

    template<typename T>
    std::shared_ptr<T> send(T* request);

private:
    void _sendMessage(std::string message);
    void _sendRoutine();
    void _receiveRoutine();
    void _tryConnect();
};

template<typename T>
std::shared_ptr<T> NetworkHandler::send(T* request) {
    Ptr<T> ptr = Ptr<T>(request);
    _requestHandler.registerRequest(Ptr<AbstractRequest<typename T::ResponseType>>(ptr));
    _sendMessage(request->getRequestMessage());
    return ptr;
}

#endif //FREEPOISSON_CLIENT_NETWORKHANDLER_H
