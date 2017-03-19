//
// Created by clejacquet on 18/03/17.
//

#ifndef FREEPOISSON_CLIENT_SIMPLELISTENER_H
#define FREEPOISSON_CLIENT_SIMPLELISTENER_H

#include <network/listener/AbstractListener.h>

class SimpleListener : public AbstractListener<std::string> {
private:
    std::string _message;

public:
    SimpleListener(const std::string& message);

protected:
    virtual std::string encodeRequest() const override;
    virtual std::string decodeResponse(std::string response_msg) const override;
};


#endif //FREEPOISSON_CLIENT_SIMPLELISTENER_H
