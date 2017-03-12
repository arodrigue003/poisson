//
// Created by clejacquet on 12/03/17.
//

#include "RequestHandler.h"

RequestHandler::Context::Context(std::chrono::system_clock::time_point start_time) :
    _start_time(start_time)
{

}

void RequestHandler::Context::onResponse(std::string response) {
    notifyAll(response);
}