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

void RequestHandler::registerResponse(std::string response) {
    std::map<unsigned int, Context>::iterator it = _pending_requests.find(_response_counter);
    if (it != _pending_requests.end()) {
        it->second.onResponse(response);
        _pending_requests.erase(_response_counter);
    }
    _response_counter++;
}





