//
// Created by clejacquet on 12/03/17.
//

#include "RequestHandler.h"

RequestHandler::Context::Context(std::chrono::system_clock::time_point start_time) :
    _start_time(start_time)
{

}

void RequestHandler::Context::onCancel() {
    notifyAll(std::make_pair(CANCELLED, std::string()));
}

void RequestHandler::Context::onResponse(std::string response) {
    notifyAll(std::make_pair(DONE, response));
}

std::chrono::milliseconds RequestHandler::Context::elapsedTime(std::chrono::system_clock::time_point now) const {
    return std::chrono::duration_cast<std::chrono::milliseconds>(now - _start_time);
}
