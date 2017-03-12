//
// Created by clejacquet on 11/03/17.
//

#include "RequestHandler.h"
#include "NetworkHandler.h"

RequestHandler::RequestHandler(NetworkHandler& network) :
    _network(&network),
    _request_counter(0),
    _response_counter(0)
{

}

void RequestHandler::checkRequests() {
    std::chrono::system_clock::time_point now = std::chrono::system_clock::now();

    std::list<unsigned int> to_remove;

    for (std::pair<unsigned int, Context> pair : _pending_requests) {
        Context context = pair.second;

        if (context.elapsedTime(now) > std::chrono::seconds(5)) {
            context.onCancel();
            to_remove.push_back(pair.first);
        }
    }

    for (unsigned int request_id : to_remove) {
        _pending_requests.erase(request_id);
    }
}

void RequestHandler::registerResponse(std::string response) {
    std::map<unsigned int, Context>::iterator it = _pending_requests.find(_response_counter);
    if (it != _pending_requests.end()) {
        it->second.onResponse(response);
        _pending_requests.erase(_response_counter);
    }
    _response_counter++;
}





