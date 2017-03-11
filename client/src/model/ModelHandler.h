#ifndef FREEPOISSON_CLIENT_MODELHANDLER_H
#define FREEPOISSON_CLIENT_MODELHANDLER_H

#include <string>

#include <concurrency/blockingconcurrentqueue.h>
using namespace moodycamel;

class NetworkHandler;

class ModelHandler {
// TODO - Complete this class basis
private:
    NetworkHandler* _network;
    BlockingConcurrentQueue<std::string> _respond_queue;

public:
    ModelHandler();
    ~ModelHandler();

    void init(NetworkHandler& network);
    void registerCommand(std::string command);
    void registerRespond(std::string respond);
    bool getRespond(std::string &data);
    void clearRespond();
};


#endif //FREEPOISSON_CLIENT_MODELHANDLER_H
