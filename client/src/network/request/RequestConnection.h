//
// Created by clejacquet on 18/03/17.
//

#ifndef FREEPOISSON_CLIENT_REQUESTCONNECTION_H
#define FREEPOISSON_CLIENT_REQUESTCONNECTION_H

#include <network/connection/Connection.h>
#include <network/Context.h>
#include <network/request/AbstractRequest.h>


#include <unordered_map>
#include <mutex>


class RequestConnection : public Connection {
private:
    unsigned int _request_counter;
    unsigned int _response_counter;
    std::mutex _pending_request_write_lock;
    std::unordered_map<unsigned int, Context> _pending_requests;

public:
    RequestConnection(const std::string& address, unsigned short port);

    virtual void collectMessages() override;

    template<typename T>
    typename std::enable_if<std::is_base_of<AbstractRequest<typename T::ResponseType>, T>::value, Ptr<T>>::type
    send(Ptr<T> request);

protected:
    virtual void onReceive(const std::string &message) override;

private:
    void _checkNextRequest();
};


template<typename T>
typename std::enable_if<std::is_base_of<AbstractRequest<typename T::ResponseType>, T>::value, Ptr<T>>::type
RequestConnection::send(Ptr<T> request) {
    Context context(std::chrono::system_clock::now());
    context.addObserver(request);

    std::pair<unsigned int, Context> pair = std::make_pair(_request_counter++, context);

    _pending_request_write_lock.lock();
    _pending_requests.insert(pair);
    _pending_request_write_lock.unlock();

    sendMessage(request->getRequestMessage());
    return request;
}


#endif //FREEPOISSON_CLIENT_REQUESTCONNECTION_H
