//
// Created by clejacquet on 16/03/17.
//

#include "ByeRequest.h"

std::string ByeRequest::encodeRequest() const {
    return "log out";
}

int ByeRequest::decodeResponse(std::string response_msg) const {
    return 0;
}
