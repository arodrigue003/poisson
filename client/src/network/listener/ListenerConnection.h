//
// Created by clejacquet on 18/03/17.
//

#ifndef FREEPOISSON_CLIENT_LISTENERCONNECTION_H
#define FREEPOISSON_CLIENT_LISTENERCONNECTION_H

#include <atomic>

#include <network/connection/Connection.h>
#include <network/listener/AbstractListener.h>
#include <utils/memory/MemoryTypes.h>


class ListenerConnection : public Connection {
private:
    std::atomic<bool> _context_guard;
    Ptr<Context> _listening_context;

public:
    ListenerConnection(const std::string& address, unsigned short port);

    template<typename T>
    typename std::enable_if<std::is_base_of<AbstractListener<typename T::ResponseType>, T>::value, Ptr<T>>::type
    listen(Ptr<T> listener);

protected:
    virtual void onReceive(const std::string &message) override;
};

template<typename T>
typename std::enable_if<std::is_base_of<AbstractListener<typename T::ResponseType>, T>::value, Ptr<T>>::type
ListenerConnection::listen(Ptr<T> listener) {
    bool false_ref = false;

    if (_context_guard.compare_exchange_strong(false_ref, true)) {
        _listening_context = Ptr<Context>(new Context(std::chrono::system_clock::now()));
        _listening_context->addObserver(listener);
        sendMessage(listener->getRequestMessage());
        return listener;
    }

    throw "Connection already listening. Abort the current one to start a new listening session";
};


#endif //FREEPOISSON_CLIENT_LISTENERCONNECTION_H
