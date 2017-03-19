//
// Created by clejacquet on 19/03/17.
//

#include <regex>
#include "GetFishesParser.h"

GetFishesParser::GetFishesParser() {

}

std::list<FishInfo> GetFishesParser::parse(std::string str) {
    std::regex base_regex("list( *\\[[a-zA-Z]+ at (0|[1-9][0-9]*)x(0|[1-9][0-9]*),(0|[1-9][0-9]*)x(0|[1-9][0-9]*),(0|[1-9][0-9]*)\\])*");
    std::smatch match;

    std::list<FishInfo> infos;

    if (std::regex_match(str, match, base_regex)) {
        std::regex item_regex("\\[([a-zA-Z]+) at (0|[1-9][0-9]*)x(0|[1-9][0-9]*),(0|[1-9][0-9]*)x(0|[1-9][0-9]*),(0|[1-9][0-9]*)\\]");

        while (std::regex_search(str, match, item_regex)) {
            FishInfo fishInfo;
            fishInfo.name = match[1].str();
            fishInfo.target_x = (unsigned int) atoi(match[2].str().c_str());
            fishInfo.target_y = (unsigned int) atoi(match[3].str().c_str());
            fishInfo.width = (unsigned int) atoi(match[4].str().c_str());
            fishInfo.height = (unsigned int) atoi(match[5].str().c_str());
            fishInfo.duration = (unsigned int) atoi(match[6].str().c_str());

            infos.push_back(fishInfo);

            str = match.suffix().str();
        }
    }

    return infos;
}
