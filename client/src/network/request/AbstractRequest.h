//
// Created by clejacquet on 12/03/17.
//

#ifndef FREEPOISSON_CLIENT_ABSTRACTREQUEST_H
#define FREEPOISSON_CLIENT_ABSTRACTREQUEST_H

#include <thread>
#include <iostream>

#include <network/Context.h>
#include <network/request/Request.h>

template<typename TRes>
class AbstractRequest : public Request<TRes>, public Observer<Message> {
private:
    enum Status {
        WAITING,
        DONE,
        CANCELLED
    };

public:
    using ResponseType = TRes;

private:
    Status _status;
    TRes _response_msg;

public:
    AbstractRequest();

    TRes getResponse() const override;
    virtual bool isResponseReceived() const override;
    void notify(Message message) override;

    std::string getRequestMessage() const;

protected:
    virtual std::string encodeRequest() const = 0;
    virtual TRes decodeResponse(std::string response_msg) const = 0;
};


template<typename TRes>
AbstractRequest<TRes>::AbstractRequest() :
    _status(Status::WAITING)
{

}

template<typename TRes>
void AbstractRequest<TRes>::notify(Message requestMessage) {
    switch (requestMessage.first) {
        case MessageCode::RECEIVED: {
            _response_msg = decodeResponse(requestMessage.second);
            _status = Status::DONE;
        } break;

        case MessageCode::CANCELLED: {
            _status = Status::CANCELLED;
        } break;

        default: {
            // ??
        }
    }
}

template<typename TRes>
TRes AbstractRequest<TRes>::getResponse() const {
    while (_status == Status::WAITING) {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }

    if (_status == Status::CANCELLED) {
        throw std::string("Request cancelled");
    }

    return _response_msg;
}

template<typename TRes>
std::string AbstractRequest<TRes>::getRequestMessage() const {
    return encodeRequest();
}

template<typename TRes>
bool AbstractRequest<TRes>::isResponseReceived() const {
    return _status == Status::DONE;
}


#endif //FREEPOISSON_CLIENT_ABSTRACTREQUEST_H
