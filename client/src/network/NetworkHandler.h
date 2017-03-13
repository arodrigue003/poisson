#ifndef FREEPOISSON_CLIENT_NETWORKHANDLER_H
#define FREEPOISSON_CLIENT_NETWORKHANDLER_H

#include <string>
#include <thread>
#include <atomic>

#include <SFML/Network.hpp>

#include <utils/memory/MemoryTypes.h>
#include <utils/concurrency/blockingconcurrentqueue.h>
#include <mutex>
#include <unordered_map>

#include "request/RequestContext.h"

using namespace moodycamel;

class ModelHandler;

class NetworkHandler {

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
    sf::TcpSocket _socket;
    std::string _address;
    unsigned short _port;

    std::thread _send_thread;
    std::thread _receive_thread;
    std::atomic<State> _state;
    BlockingConcurrentQueue<std::string> _send_queue;

    unsigned int _request_counter;
    unsigned int _response_counter;
    std::mutex _pending_request_write_lock;
    std::unordered_map<unsigned int, RequestContext> _pending_requests;

// Methods
public:
    NetworkHandler();
    ~NetworkHandler();

    void launch(std::string address, unsigned short port);

    template<typename T>
    typename std::enable_if<std::is_base_of<AbstractRequest<typename T::ResponseType>, T>::value, Ptr<T>>::type
    send(Ptr<T> request);

private:
    void _sendMessage(std::string message);
    void _sendRoutine();
    void _receiveRoutine();
    void _tryConnect();

    void _checkNextRequest();
    void _registerResponse(std::string response);

    template<typename TRes>
    void _registerRequest(Ptr<AbstractRequest<TRes>> request);
};

template<typename T>
typename std::enable_if<std::is_base_of<AbstractRequest<typename T::ResponseType>, T>::value, Ptr<T>>::type
NetworkHandler::send(Ptr<T> request) {
    _registerRequest(Ptr<AbstractRequest<typename T::ResponseType>>(request));
    return request;
}

template<typename TRes>
void NetworkHandler::_registerRequest(Ptr<AbstractRequest<TRes>> request) {
    RequestContext context(std::chrono::system_clock::now());
    context.addObserver(request);

    std::pair<unsigned int, RequestContext> pair = std::make_pair(_request_counter++, context);

    _pending_request_write_lock.lock();
    _pending_requests.insert(pair);
    _pending_request_write_lock.unlock();

    _sendMessage(request->getRequestMessage());
}

#endif //FREEPOISSON_CLIENT_NETWORKHANDLER_H
