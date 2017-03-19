//
// Created by clejacquet on 18/03/17.
//

#include <regex>
#include "GetFishesContinuouslyListener.h"

std::string GetFishesContinuouslyListener::encodeRequest() const {
    return "getFishesContinuously";
}

std::list<FishInfo> GetFishesContinuouslyListener::decodeResponse(std::string response_msg) const {
    return GetFishesParser::parse(response_msg);
}
