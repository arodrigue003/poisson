//
// Created by clejacquet on 16/03/17.
//

#ifndef FREEPOISSON_CLIENT_TRANSFORM_H
#define FREEPOISSON_CLIENT_TRANSFORM_H

#include <iostream>

class Transform {
private:
    unsigned int _dest_x;
    unsigned int _dest_y;
    unsigned int _width;
    unsigned int _height;

public:
    Transform(unsigned int dest_x, unsigned int dest_y, unsigned int width, unsigned int height);

    unsigned int getDestX() const;
    unsigned int getDestY() const;
    unsigned int getWidth() const;
    unsigned int getHeight() const;
};

std::ostream& operator<<(std::ostream& stream, const Transform& transform);


#endif //FREEPOISSON_CLIENT_TRANSFORM_H
