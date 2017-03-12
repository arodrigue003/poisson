//
// Created by clejacquet on 12/03/17.
//

#ifndef FREEPOISSON_CLIENT_ABSTRACTREQUEST_H
#define FREEPOISSON_CLIENT_ABSTRACTREQUEST_H

#include <thread>
#include "Request.h"
#include <utils/observer/Observer.h>
#include <iostream>

template<typename TRes>
class AbstractRequest : public Request<TRes>, public Observer<std::string> {
private:
    bool _is_received;
    TRes _response_msg;

public:
    AbstractRequest();

    TRes getResponse() override;
    void notify(std::string) override;

    std::string getRequestMessage();

    using ResponseType = TRes;

protected:
    virtual TRes decodeResponse(std::string response_msg) = 0;
    virtual std::string encodeRequest() = 0;
};


template<typename TRes>
AbstractRequest<TRes>::AbstractRequest() :
    _is_received(false)
{

}

template<typename TRes>
void AbstractRequest<TRes>::notify(std::string response) {
    _response_msg = decodeResponse(response);
    _is_received = true;
}

template<typename TRes>
TRes AbstractRequest<TRes>::getResponse() {
    while (!_is_received) {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }

    return _response_msg;
}

template<typename TRes>
std::string AbstractRequest<TRes>::getRequestMessage() {
    return encodeRequest();
}


#endif //FREEPOISSON_CLIENT_ABSTRACTREQUEST_H
