//
// Created by clejacquet on 16/03/17.
//

#include "Transform.h"

Transform::Transform(unsigned int dest_x, unsigned int dest_y, unsigned int width, unsigned int height) :
    _dest_x(dest_x),
    _dest_y(dest_y),
    _width(width),
    _height(height)
{

}

unsigned int Transform::getDestX() const {
    return _dest_x;
}

unsigned int Transform::getDestY() const {
    return _dest_y;
}

unsigned int Transform::getWidth() const {
    return _width;
}

unsigned int Transform::getHeight() const {
    return _height;
}

std::ostream &operator<<(std::ostream &stream, const Transform &transform) {
    stream << transform.getDestX() << "x" << transform.getDestY() << ","
           << transform.getWidth() << "x" << transform.getHeight();
    return stream;
}
