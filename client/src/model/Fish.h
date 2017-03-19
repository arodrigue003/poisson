//
// Created by clejacquet on 16/03/17.
//

#ifndef FREEPOISSON_CLIENT_FISH_H
#define FREEPOISSON_CLIENT_FISH_H

#include <string>
#include "Transform.h"


class Fish {
private:
    Transform _transform;
    std::string _name;
    std::string _way_model;

public:
    Fish(const Transform& transform, std::string name, std::string way_model);

    Transform getTransform() const;
    std::string getName() const;
    std::string getWayModel() const;
};

#endif //FREEPOISSON_CLIENT_FISH_H
