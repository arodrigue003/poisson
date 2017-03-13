//
// Created by clejacquet on 12/03/17.
//

#include "RequestContext.h"

RequestContext::RequestContext(std::chrono::system_clock::time_point start_time) :
    _start_time(start_time)
{

}

void RequestContext::onCancel() {
    notifyAll(std::make_pair(CANCELLED, std::string()));
}

void RequestContext::onResponse(std::string response) {
    notifyAll(std::make_pair(DONE, response));
}

std::chrono::milliseconds RequestContext::elapsedTime(std::chrono::system_clock::time_point now) const {
    return std::chrono::duration_cast<std::chrono::milliseconds>(now - _start_time);
}
