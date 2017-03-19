//
// Created by clejacquet on 19/03/17.
//

#ifndef FREEPOISSON_CLIENT_GETFISHESPARSER_H
#define FREEPOISSON_CLIENT_GETFISHESPARSER_H

#include <list>

#include <network/parser/FishInfo.h>

class GetFishesParser {
private:
    GetFishesParser();

public:
    static std::list<FishInfo> parse(std::string str);
};


#endif //FREEPOISSON_CLIENT_GETFISHESPARSER_H
