#ifndef FREEPOISSON_CLIENT_NETWORKHANDLER_H
#define FREEPOISSON_CLIENT_NETWORKHANDLER_H

#include <thread>
#include <atomic>
#include <list>

#include <network/request/RequestConnection.h>
#include <network/listener/ListenerConnection.h>


class NetworkHandler {
// Attributes
private:
    bool _active;
    Ptr<RequestConnection> _request_connection;
    Ptr<ListenerConnection> _listener_connection;
    std::thread _send_thread;
    std::thread _receive_thread;

// Methods
public:
    NetworkHandler();
    ~NetworkHandler();

    void launch(std::string address, unsigned short port);

    template<typename T>
    typename std::enable_if<std::is_base_of<AbstractRequest<typename T::ResponseType>, T>::value, Ptr<T>>::type
    send(Ptr<T> request);

    template<typename T>
    typename std::enable_if<std::is_base_of<AbstractListener<typename T::ResponseType>, T>::value, Ptr<T>>::type
    listen(Ptr<T> listener);

private:
    void _sendRoutine();
    void _receiveRoutine();
};

template<typename T>
typename std::enable_if<std::is_base_of<AbstractRequest<typename T::ResponseType>, T>::value, Ptr<T>>::type
NetworkHandler::send(Ptr<T> request) {
    return _request_connection->send(request);
}

template<typename T>
typename std::enable_if<std::is_base_of<AbstractListener<typename T::ResponseType>, T>::value, Ptr<T>>::type
NetworkHandler::listen(Ptr<T> listener) {
    return _listener_connection->listen(listener);
}

#endif //FREEPOISSON_CLIENT_NETWORKHANDLER_H
