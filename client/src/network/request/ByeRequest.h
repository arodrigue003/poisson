//
// Created by clejacquet on 16/03/17.
//

#ifndef FREEPOISSON_CLIENT_BYEREQUEST_H
#define FREEPOISSON_CLIENT_BYEREQUEST_H

#include <network/AbstractRequest.h>

class ByeRequest : public AbstractRequest<int> {
protected:
    virtual std::string encodeRequest() const override;
    virtual int decodeResponse(std::string response_msg) const override;
};


#endif //FREEPOISSON_CLIENT_BYEREQUEST_H
