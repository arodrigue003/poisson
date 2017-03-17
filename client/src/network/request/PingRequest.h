//
// Created by clejacquet on 16/03/17.
//

#ifndef FREEPOISSON_CLIENT_PINGREQUEST_H
#define FREEPOISSON_CLIENT_PINGREQUEST_H

#include <network/AbstractRequest.h>

class PingRequest : public AbstractRequest<int> {
private:
    unsigned int _id;

public:
    PingRequest(unsigned int id);

protected:
    virtual std::string encodeRequest() const override;
    virtual int decodeResponse(std::string response_msg) const override;
};


#endif //FREEPOISSON_CLIENT_PINGREQUEST_H
