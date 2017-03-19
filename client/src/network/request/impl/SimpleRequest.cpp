//
// Created by clejacquet on 12/03/17.
//

#include "SimpleRequest.h"

SimpleRequest::SimpleRequest(std::string request_msg) :
    _request_msg(request_msg)
{

}

std::string SimpleRequest::decodeResponse(std::string response_msg) const {
    return response_msg;
}

std::string SimpleRequest::encodeRequest() const {
    return _request_msg;
}
