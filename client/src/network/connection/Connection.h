//
// Created by clejacquet on 17/03/17.
//

#ifndef FREEPOISSON_CLIENT_CONNECTION_H
#define FREEPOISSON_CLIENT_CONNECTION_H

#include <SFML/Network.hpp>
#include <utils/concurrency/blockingconcurrentqueue.h>


using namespace moodycamel;

class Connection {
private:
    enum State {
        INIT,
        ACTIVE,
        CONNECTING
    };

private:
    sf::TcpSocket _socket;
    std::string _address;
    unsigned short _port;
    std::atomic<State> _state;

    char _reception_buffer[256];
    BlockingConcurrentQueue<std::string> _send_queue;

public:
    Connection(const std::string& address, unsigned short port);

    virtual void sendQueuedMessages();
    virtual void collectMessages();

protected:
    void sendMessage(const std::string& message);
    virtual void onReceive(const std::string& message) = 0;

private:
    void _tryConnect();
};


#endif //FREEPOISSON_CLIENT_CONNECTION_H
