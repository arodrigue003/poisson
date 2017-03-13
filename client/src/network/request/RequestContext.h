//
// Created by clejacquet on 14/03/17.
//

#ifndef FREEPOISSON_CLIENT_REQUESTCONTEXT_H
#define FREEPOISSON_CLIENT_REQUESTCONTEXT_H

#include <utils/observer/Observable.h>
#include <utils/memory/MemoryTypes.h>

#include "network/request/AbstractRequest.h"

class RequestContext : public Observable<RequestMessage> {
private:
    std::chrono::system_clock::time_point _start_time;

public:
    RequestContext(std::chrono::system_clock::time_point start_time);

    void onCancel();
    void onResponse(std::string response);
    std::chrono::milliseconds elapsedTime(std::chrono::system_clock::time_point now) const;
};

#endif //FREEPOISSON_CLIENT_REQUESTCONTEXT_H
