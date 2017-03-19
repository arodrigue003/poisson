//
// Created by clejacquet on 17/03/17.
//

#include "Fish.h"

Fish::Fish(const Transform &transform, std::string name, std::string way_model) :
    _transform(transform),
    _name(name),
    _way_model(way_model)
{

}

Transform Fish::getTransform() const {
    return _transform;
}

std::string Fish::getName() const {
    return _name;
}

std::string Fish::getWayModel() const {
    return _way_model;
}
