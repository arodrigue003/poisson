//
// Created by clejacquet on 15/03/17.
//

#include "HelloRequest.h"

#include <sstream>
#include <regex>


HelloRequest::HelloRequest(int id) :
    _id(id)
{

}

std::string HelloRequest::encodeRequest() const {
    std::ostringstream oss;

    if (_id != -1) {
        oss << "hello in as N" << _id;
    } else {
        oss << "hello";
    }

    return oss.str();
}

int HelloRequest::decodeResponse(std::string response_msg) const {
    std::regex base_regex("greeting N(0|[1-9][0-9]*)");
    std::smatch number_match;

    if (std::regex_match(response_msg, number_match, base_regex)) {
        if (number_match.size() == 2) {
            int id;
            std::istringstream iss(number_match[1].str());
            iss >> id;

            return id;
        }
    }

    return -1;
}
