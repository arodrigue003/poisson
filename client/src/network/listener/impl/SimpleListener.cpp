//
// Created by clejacquet on 18/03/17.
//

#include "SimpleListener.h"

SimpleListener::SimpleListener(const std::string &message) :
    _message(message)
{

}

std::string SimpleListener::encodeRequest() const {
    return _message;
}

std::string SimpleListener::decodeResponse(std::string response_msg) const {
    return response_msg;
}
