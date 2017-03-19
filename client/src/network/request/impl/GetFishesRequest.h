//
// Created by clejacquet on 19/03/17.
//

#ifndef FREEPOISSON_CLIENT_GETFISHESREQUEST_H
#define FREEPOISSON_CLIENT_GETFISHESREQUEST_H


#include <network/request/AbstractRequest.h>
#include <network/parser/FishInfo.h>

class GetFishesRequest : public AbstractRequest<std::list<FishInfo>> {
protected:
    virtual std::string encodeRequest() const override;

    virtual std::list<FishInfo> decodeResponse(std::string response_msg) const override;
};


#endif //FREEPOISSON_CLIENT_GETFISHESREQUEST_H
