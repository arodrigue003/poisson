//
// Created by clejacquet on 15/03/17.
//

#ifndef FREEPOISSON_CLIENT_HELLOREQUEST_H
#define FREEPOISSON_CLIENT_HELLOREQUEST_H


#include <network/AbstractRequest.h>

class HelloRequest : public AbstractRequest<int> {
private:
    int _id;

public:
    HelloRequest(int id = -1);

protected:
    virtual std::string encodeRequest() const override;
    virtual int decodeResponse(std::string response_msg) const override;
};


#endif //FREEPOISSON_CLIENT_HELLOREQUEST_H
