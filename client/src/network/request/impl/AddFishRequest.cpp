#include "AddFishRequest.h"
#include <sstream>

AddFishRequest::AddFishRequest(const Fish &fish) :
    _fish(fish)
{

}

std::string AddFishRequest::encodeRequest() const {
    std::ostringstream oss;
    oss << "addFish " << _fish.getName() << " at " << _fish.getTransform() << ", " << _fish.getWayModel();
    return oss.str();
}

bool AddFishRequest::decodeResponse(std::string response_msg) const {
    return response_msg == "OK";
}