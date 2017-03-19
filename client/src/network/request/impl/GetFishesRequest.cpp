//
// Created by clejacquet on 19/03/17.
//

#include <network/parser/GetFishesParser.h>
#include "GetFishesRequest.h"

std::string GetFishesRequest::encodeRequest() const {
    return "getFishes";
}

std::list<FishInfo> GetFishesRequest::decodeResponse(std::string response_msg) const {
    return GetFishesParser::parse(response_msg);
}
