#ifndef FREEPOISSON_CLIENT_NETWORKHANDLER_H
#define FREEPOISSON_CLIENT_NETWORKHANDLER_H

#include <string>

class DisplayHandler;

class NetworkHandler {
// TODO - Complete this class basis

private:
    DisplayHandler* _display;

public:
    NetworkHandler(DisplayHandler* display);

    void connect(std::string address, unsigned short port);
};


#endif //FREEPOISSON_CLIENT_NETWORKHANDLER_H
