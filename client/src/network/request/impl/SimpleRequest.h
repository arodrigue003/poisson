//
// Created by clejacquet on 12/03/17.
//

#ifndef FREEPOISSON_CLIENT_SIMPLEREQUEST_H
#define FREEPOISSON_CLIENT_SIMPLEREQUEST_H


#include <string>
#include <network/request/AbstractRequest.h>

class SimpleRequest : public AbstractRequest<std::string> {
private:
    std::string _request_msg;

public:
    SimpleRequest(std::string request_msg);

protected:
    std::string encodeRequest() const override;
    std::string decodeResponse(std::string response_msg) const override;
};


#endif //FREEPOISSON_CLIENT_SIMPLEREQUEST_H
