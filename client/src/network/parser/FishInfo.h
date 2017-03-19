//
// Created by clejacquet on 18/03/17.
//

#ifndef FREEPOISSON_CLIENT_FISHINFO_H
#define FREEPOISSON_CLIENT_FISHINFO_H

#include <string>

struct FishInfo {
    std::string name;
    unsigned int target_x;
    unsigned int target_y;
    unsigned int width;
    unsigned int height;
    unsigned int duration;
};


#endif //FREEPOISSON_CLIENT_FISHINFO_H
