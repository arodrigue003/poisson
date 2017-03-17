//
// Created by clejacquet on 16/03/17.
//

#include <sstream>
#include "PingRequest.h"

PingRequest::PingRequest(unsigned int id) :
    _id(id)
{

}

std::string PingRequest::encodeRequest() const {
    std::ostringstream oss;
    oss << "ping " << _id;
    return oss.str();
}

int PingRequest::decodeResponse(std::string response_msg) const {
    return 0;
}
