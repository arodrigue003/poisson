//
// Created by clejacquet on 18/03/17.
//

#ifndef FREEPOISSON_CLIENT_LISTENER_H
#define FREEPOISSON_CLIENT_LISTENER_H


#include <chrono>

template<typename TRes>
class Listener {
public:
    using TimePoint = std::chrono::system_clock::time_point;

    struct Response {
        TRes data;
        TimePoint time;
    };

public:
    virtual bool tryPollResponse(Response& response_out) = 0;
};


#endif //FREEPOISSON_CLIENT_LISTENER_H
