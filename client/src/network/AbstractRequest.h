//
// Created by clejacquet on 12/03/17.
//

#ifndef FREEPOISSON_CLIENT_ABSTRACTREQUEST_H
#define FREEPOISSON_CLIENT_ABSTRACTREQUEST_H

#include <thread>
#include <iostream>

#include <utils/observer/Observer.h>

#include "Request.h"

enum RequestStatus {
    SENDING,
    DONE,
    CANCELLED
};

using RequestMessage = std::pair<RequestStatus, std::string>;

template<typename TRes>
class AbstractRequest : public Request<TRes>, public Observer<RequestMessage> {
private:
    RequestStatus _request_status;
    TRes _response_msg;

public:
    AbstractRequest();

    TRes getResponse() override;
    void notify(RequestMessage message) override;

    std::string getRequestMessage();

    using ResponseType = TRes;

protected:
    virtual TRes decodeResponse(std::string response_msg) = 0;
    virtual std::string encodeRequest() = 0;
};


template<typename TRes>
AbstractRequest<TRes>::AbstractRequest() :
    _request_status(SENDING)
{

}

template<typename TRes>
void AbstractRequest<TRes>::notify(RequestMessage requestMessage) {
    switch (requestMessage.first) {
        case DONE: {
            _response_msg = decodeResponse(requestMessage.second);
            _request_status = DONE;
        } break;

        case CANCELLED: {
            _request_status = CANCELLED;
        } break;

        default: {
            // ??
        }
    }
}

template<typename TRes>
TRes AbstractRequest<TRes>::getResponse() {
    while (_request_status == SENDING) {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }

    if (_request_status == CANCELLED) {
        throw std::string("Request cancelled");
    }

    return _response_msg;
}

template<typename TRes>
std::string AbstractRequest<TRes>::getRequestMessage() {
    return encodeRequest();
}


#endif //FREEPOISSON_CLIENT_ABSTRACTREQUEST_H
