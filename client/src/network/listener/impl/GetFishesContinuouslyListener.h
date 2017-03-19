//
// Created by clejacquet on 18/03/17.
//

#ifndef FREEPOISSON_CLIENT_GETFISHESCONTINUOUSLYLISTENER_H
#define FREEPOISSON_CLIENT_GETFISHESCONTINUOUSLYLISTENER_H

#include <network/listener/AbstractListener.h>
#include <network/parser/GetFishesParser.h>
#include <network/parser/FishInfo.h>


class GetFishesContinuouslyListener : public AbstractListener<std::list<FishInfo>> {
protected:
    virtual std::string encodeRequest() const override;
    virtual std::list<FishInfo> decodeResponse(std::string response_msg) const override;
};


#endif //FREEPOISSON_CLIENT_GETFISHESCONTINUOUSLYLISTENER_H
