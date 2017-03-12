//
// Created by clejacquet on 11/03/17.
//

#ifndef FREEPOISSON_CLIENT_REQUEST_H
#define FREEPOISSON_CLIENT_REQUEST_H


template<typename TRes>
class Request {
public:
    virtual ~Request() {}
    virtual TRes getResponse() = 0;
};

#endif //FREEPOISSON_CLIENT_REQUEST_H
