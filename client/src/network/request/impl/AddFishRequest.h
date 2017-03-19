#ifndef FREEPOISSON_CLIENT_ADDFISHREQUEST_H
#define FREEPOISSON_CLIENT_ADDFISHREQUEST_H


#include <network/request/AbstractRequest.h>
#include <model/Fish.h>


class AddFishRequest : public AbstractRequest<bool> {
private:
    Fish _fish;

public:
    AddFishRequest(const Fish& fish);

protected:
    virtual std::string encodeRequest() const override;
    virtual bool decodeResponse(std::string response_msg) const override;
};


#endif //FREEPOISSON_CLIENT_ADDFISHREQUEST_H
