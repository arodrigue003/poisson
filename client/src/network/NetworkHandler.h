#ifndef FREEPOISSON_CLIENT_NETWORKHANDLER_H
#define FREEPOISSON_CLIENT_NETWORKHANDLER_H

#include <string>
#include <thread>

#include <SFML/Network.hpp>
#include <concurrency/blockingconcurrentqueue.h>

using namespace moodycamel;

class ModelHandler;

class NetworkHandler {
// TODO - Complete this class basis

// Attributes
private:
    ModelHandler* _model;
    sf::TcpSocket _socket;
    std::thread _send_thread;
    std::thread _receive_thread;
    bool _is_active;
    BlockingConcurrentQueue<std::string> _send_queue;

// Methods
public:
    NetworkHandler();
    ~NetworkHandler();

    void init(ModelHandler& model);
    void launch(std::string address, unsigned short port);
    void sendMessage(std::string msg);

private:
    void _send_routine();
    void _receive_routine();
};


#endif //FREEPOISSON_CLIENT_NETWORKHANDLER_H
