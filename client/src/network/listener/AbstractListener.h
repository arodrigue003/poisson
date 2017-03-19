//
// Created by clejacquet on 18/03/17.
//

#ifndef FREEPOISSON_CLIENT_ABSTRACTLISTENER_H
#define FREEPOISSON_CLIENT_ABSTRACTLISTENER_H

#include <string>
#include <queue>
#include <mutex>

#include <network/Context.h>
#include "Listener.h"


template<typename TRes>
class AbstractListener : public Listener<TRes>, public Observer<Message> {
private:
    enum Status {
        LISTENING,
        CANCELLED
    };

    using Response = typename Listener<TRes>::Response;

public:
    using ResponseType = TRes;

private:
    std::mutex _response_lock;
    std::queue<Response> _responses;
    Status _listener_status;

public:
    AbstractListener();

    virtual bool tryPollResponse(Response &response_out) override;
    virtual void notify(Message parameter) override;

    std::string getRequestMessage() const;

protected:
    virtual std::string encodeRequest() const = 0;
    virtual TRes decodeResponse(std::string response_msg) const = 0;
};

template<typename TRes>
AbstractListener<TRes>::AbstractListener() :
    _listener_status(Status::LISTENING)
{

}

template<typename TRes>
bool AbstractListener<TRes>::tryPollResponse(Response &response_out) {
    if (!_responses.empty()) {
        _response_lock.lock();
        response_out = _responses.front();
        _responses.pop();
        _response_lock.unlock();

        return true;
    }

    return false;
}

template<typename TRes>
void AbstractListener<TRes>::notify(Message parameter) {
    switch (parameter.first) {
        case MessageCode::RECEIVED: {
            Response response;
            response.data = decodeResponse(parameter.second);
            response.time = std::chrono::system_clock::now();

            _response_lock.lock();
            _responses.push(response);
            _response_lock.unlock();
        } break;

        case MessageCode::CANCELLED: {
            _listener_status = Status::CANCELLED;
        } break;

        default: {
            // ??
        }
    }
}

template<typename TRes>
std::string AbstractListener<TRes>::getRequestMessage() const {
    return encodeRequest();
}


#endif //FREEPOISSON_CLIENT_ABSTRACTLISTENER_H
