#ifndef FREEPOISSON_CLIENT_NETWORKHANDLER_H
#define FREEPOISSON_CLIENT_NETWORKHANDLER_H

#include <string>
#include <thread>
#include <atomic>

#include <SFML/Network.hpp>
#include <concurrency/blockingconcurrentqueue.h>

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
    ModelHandler* _model;

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

    void init(ModelHandler& model);
    void launch(std::string address, unsigned short port);
    void sendMessage(std::string msg);

private:
    void _sendRoutine();
    void _receiveRoutine();
    void _tryConnect();
};


#endif //FREEPOISSON_CLIENT_NETWORKHANDLER_H
