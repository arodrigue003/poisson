//
// Created by clejacquet on 11/03/17.
//

#ifndef FREEPOISSON_CLIENT_REQUESTHANDLER_H
#define FREEPOISSON_CLIENT_REQUESTHANDLER_H

#include <map>
#include <chrono>

#include <utils/observer/Observable.h>
#include "AbstractRequest.h"

class NetworkHandler;

class RequestHandler {
private:
    class Context : public Observable<std::string> {
    private:
        std::chrono::system_clock::time_point _start_time;

    public:
        Context(std::chrono::system_clock::time_point start_time);

        void onResponse(std::string response);
    };

private:
    NetworkHandler* _network;
    unsigned int _request_counter;
    unsigned int _response_counter;
    std::map<unsigned int, Context> _pending_requests;

public:
    RequestHandler(NetworkHandler& network);

    template<typename TRes>
    void registerRequest(Ptr<AbstractRequest<TRes>> request);

    void registerResponse(std::string response);
};

template<typename TRes>
void RequestHandler::registerRequest(Ptr<AbstractRequest<TRes>> request) {
    Context context(std::chrono::system_clock::now());
    context.addObserver(request);
    _pending_requests.insert(std::make_pair(_request_counter++, context));
}


#endif //FREEPOISSON_CLIENT_REQUESTHANDLER_H
